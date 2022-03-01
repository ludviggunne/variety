#include "dual_contour.h"

#include <thread>

DualContour::~DualContour()
{
	if (_vertices)
		delete _vertices;
}

void DualContour::Compute(const std::string &equation)
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
