#include "dual_contour.h"

#include <thread>

#include "gl/misc.h"

const char *DualContour::_psNone = "";
const char *DualContour::_psSampling = "Sampling";
const char *DualContour::_psBuilding = "Building";

DualContour::DualContour() :
	xMin(Settings::DualInitXMin),
	yMin(Settings::DualInitYMin),
	zMin(Settings::DualInitZMin),

	xMax(Settings::DualInitXMax),
	yMax(Settings::DualInitYMax),
	zMax(Settings::DualInitZMax),

	resolution(Settings::DualInitResolution),
	_progress(0.0f),
	_progressStr(_psNone),
	_state(State::Standby),
	_vertices(nullptr)
{
	// Names switched because so z is up
	_symbolTable.add_variable("x", _varX);
	_symbolTable.add_variable("z", _varY);
	_symbolTable.add_variable("y", _varZ);
}

DualContour::~DualContour()
{
	if (_vertices)
		delete _vertices;
}

bool DualContour::Compute(const std::string &equation)
{
	// Setup expression
	exprtk::expression<float> expression;
	expression.register_symbol_table(_symbolTable);

	// Convert equation to form f(x, y, z) = 0
	std::string func_str;

	auto equal_sign_it = equation.find('=');
	if (equal_sign_it == equation.size())
		return false; // No equal sign

	func_str += equation.substr(0, equal_sign_it);
	func_str += "-(";
	func_str += equation.substr(equal_sign_it + 1, std::string::npos);
	func_str += ")";

	// Compile and return status on fail
	if (!exprtk::parser<float>().compile(func_str, expression))
		return false;

	// Dispatch computation
	std::thread(&DualContour::ICompute, this, expression, 
		std::ref(_varX), std::ref(_varY), std::ref(_varZ)).detach();

	return true;
}

std::vector<gl::Vertex> const *DualContour::GetVertices()
{
	if (_state == State::Present && !_vertices->empty()) {
		_state = State::Standby;
		return _vertices;
	}

	return nullptr;
}

void DualContour::ICompute(const exprtk::expression<float> &expr, 
	float &var_x, float &var_y, float &var_z)
{
	_state = State::Compute;

	// Lock parameters
	auto _xMin = xMin;
	auto _yMin = yMin;
	auto _zMin = zMin;

	auto _xMax = xMax;
	auto _yMax = yMax;
	auto _zMax = zMax;

	auto xRes = resolution;

	// Reset vertices
	if (_vertices)
		_vertices->clear();
	else
		_vertices = new std::vector<gl::Vertex>;

	// Find sample box y and z dimensions
	auto stepSize = (_xMax - _xMin) / xRes;
	auto yRes = static_cast<int> ((_yMax - _yMin) / stepSize);
	auto zRes = static_cast<int> ((_zMax - _zMin) / stepSize);

	auto *samples = new float[xRes * yRes * zRes];

	// Sample function
	_progress = 0.0f;
	_progressStr = _psSampling;
	int i, j, k;
	for (        i = 0, _varX = _xMin; i < xRes; i++, _varX += stepSize) {
		_progress = i / static_cast<float>(xRes);
		for (    j = 0, _varY = _yMin; j < yRes; j++, _varY += stepSize)
			for (k = 0, _varZ = _zMin; k < zRes; k++, _varZ += stepSize)
				samples[i + xRes * (j + yRes * k)] = expr.value();
	}

	// Add faces
	// Start one step ahead since we are considering edges
	_progress = 0.0f;
	_progressStr = _psBuilding;
	float x, y, z;
	for (        i = 1, x = _xMin + stepSize; i < xRes; i++, x += stepSize) {
		_progress = i / static_cast<float>(xRes);
		for (    j = 1, y = _yMin + stepSize; j < yRes; j++, y += stepSize)
			for (k = 1, z = _zMin + stepSize; k < zRes; k++, z += stepSize) {

				bool test0, test1;
				glm::vec3 normal;
				gl::Vertex v0, v1, v2, v3;

				auto halfStep = stepSize / 2.0f;
			
				// Horizontal edge
				normal = glm::vec3(1.0f, 0.0f, 0.0f);
				test0 = samples[(i - 1) + xRes * (j + yRes * k)] > 0;
				test1 = samples[ i      + xRes * (j + yRes * k)] > 0;

				if (test0 ^ test1) {
					if (test0) normal *= -1.0f;

					// Find vertices
					v0 = gl::Vertex{
						glm::vec3(
							x - halfStep,
							y - halfStep,
							z - halfStep
						),
						normal };

					v1 = gl::Vertex{
						glm::vec3(
							x - halfStep,
							y + halfStep,
							z - halfStep
						),
						normal };

					v2 = gl::Vertex{
						glm::vec3(
							x - halfStep,
							y - halfStep,
							z + halfStep
						),
						normal };

					v3 = gl::Vertex{
						glm::vec3(
							x - halfStep,
							y + halfStep,
							z + halfStep
						),
						normal };

					_vertices->push_back(v0);
					_vertices->push_back(v1);
					_vertices->push_back(v2);

					_vertices->push_back(v1);
					_vertices->push_back(v2);
					_vertices->push_back(v3);
				}

				// Vertical edge
				normal = glm::vec3(0.0f, 1.0f, 0.0f);
				test0 = samples[i + xRes * ((j - 1) + yRes * k)] > 0;
				test1 = samples[i + xRes * ( j      + yRes * k)] > 0;

				if (test0 ^ test1) {
					if (test0) normal *= -1.0f;

					// Find vertices
					v0 = gl::Vertex{
						glm::vec3(
							x - halfStep,
							y - halfStep,
							z - halfStep
						),
						normal };

					v1 = gl::Vertex{
						glm::vec3(
							x + halfStep,
							y - halfStep,
							z - halfStep
						),
						normal };

					v2 = gl::Vertex{
						glm::vec3(
							x - halfStep,
							y - halfStep,
							z + halfStep
						),
						normal };

					v3 = gl::Vertex{
						glm::vec3(
							x + halfStep,
							y - halfStep,
							z + halfStep
						),
						normal };

					_vertices->push_back(v0);
					_vertices->push_back(v1);
					_vertices->push_back(v2);

					_vertices->push_back(v1);
					_vertices->push_back(v2);
					_vertices->push_back(v3);
				}

				// Forward edge
				normal = glm::vec3(0.0f, 0.0f, 1.0f);
				test0 = samples[i + xRes * (j + yRes * (k - 1))] > 0;
				test1 = samples[i + xRes * (j + yRes *  k     )] > 0;

				if (test0 ^ test1) {
					if (test0) normal *= -1.0f;

					// Find vertices
					v0 = gl::Vertex{
						glm::vec3(
							x - halfStep,
							y - halfStep,
							z - halfStep
						),
						normal };

					v1 = gl::Vertex{
						glm::vec3(
							x + halfStep,
							y - halfStep,
							z - halfStep
						),
						normal };

					v2 = gl::Vertex{
						glm::vec3(
							x - halfStep,
							y + halfStep,
							z - halfStep
						),
						normal };

					v3 = gl::Vertex{
						glm::vec3(
							x + halfStep,
							y + halfStep,
							z - halfStep
						),
						normal };

					_vertices->push_back(v0);
					_vertices->push_back(v1);
					_vertices->push_back(v2);

					_vertices->push_back(v1);
					_vertices->push_back(v2);
					_vertices->push_back(v3);
				}
			}
	}

	// Finish
	_state = State::Present;
}
