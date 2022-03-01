#pragma once

#include "settings.h"
#include "gl/vertex.h"

class DualContour {
public:
	enum class State { Standby, Compute, Present };

public:
	DualContour() :
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
	}
	~DualContour();

	void Compute(const std::string &equation);

	const std::vector<gl::Vertex> *GetVertices();
	State GetState() const { return _state; }
	float GetProgress() const { return _progress; }

private:
	void ICompute(const std::string &equation);

public:
	float xMin;
	float yMin;
	float zMin;

	float xMax;
	float yMax;
	float zMax;

	float stepSize;

private:
	float _progress;
	State _state;
	std::vector<gl::Vertex> *_vertices;
};