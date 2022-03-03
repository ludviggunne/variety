#include "dual_contour.h"

#include <thread>

DualContour::DualContour() :
	xMin(Settings::DualInitXMin),
	yMin(Settings::DualInitYMin),
	zMin(Settings::DualInitZMin),

	xMax(Settings::DualInitXMax),
	yMax(Settings::DualInitYMax),
	zMax(Settings::DualInitZMax),

	stepSize(Settings::DualInitStepSize),
	_progress(0.0f),
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
	_progress = 0.0f;

	// Copy parameters
	auto _xMin = xMin;
	auto _yMin = yMin;
	auto _zMin = zMin;

	auto _xMax = xMax;
	auto _yMax = yMax;
	auto _zMax = zMax;

	auto _stepSize = stepSize;

	// Reset vertices
	if (_vertices)
		_vertices->clear();
	else
		_vertices = new std::vector<gl::Vertex>;

	// test ------------------------------------------------
	
	for (_varX = _xMin; _varX < _xMax; _varX += _stepSize) {

		_progress = (_varX - _xMin) / (_xMax - _xMin);

		for (_varY = _yMin; _varY < _yMax; _varY += _stepSize) {
			for (_varZ = _zMin; _varZ < _zMax; _varZ += _stepSize) {
				if (expr.value() < 0)
				{
					glm::vec3 normal(0.0f, 0.0f, 1.0f);
					_vertices->push_back(gl::Vertex{
						glm::vec3(_varX, _varY, _varZ),
						normal
					});
					_vertices->push_back(gl::Vertex{
						glm::vec3(_varX + stepSize, _varY, _varZ),
						normal
					});
					_vertices->push_back(gl::Vertex{
						glm::vec3(_varX, _varY + _stepSize, _varZ),
						normal
					});
				}
			}
		}
	}
	
	// test ------------------------------------------------

	// Finish
	_state = State::Present;
}
