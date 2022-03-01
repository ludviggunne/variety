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
	_symbolTable.add_variable("x", _varX);
	_symbolTable.add_variable("y", _varY);
	_symbolTable.add_variable("z", _varZ);
}

DualContour::~DualContour()
{
	if (_vertices)
		delete _vertices;
}

bool DualContour::Compute(const std::string &equation)
{
	std::thread(&ICompute, this, equation).detach();
}

const std::vector<gl::Vertex> *DualContour::GetVertices()
{
	if (_state == State::Present) {
		_state = State::Standby;
		return _vertices;
	}

	return nullptr;
}

void DualContour::ICompute(const std::string &equation)
{
	_state = State::Compute;

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

	// DO SOME MAGIC

	// Finish
	_state = State::Compute;
}
