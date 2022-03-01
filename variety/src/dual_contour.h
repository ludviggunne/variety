#pragma once

#include "settings.h"
#include "gl/vertex.h"

class DualContour {
public:
	enum class State { Standby, Compute, Present };

public:
	DualContour();
	~DualContour();

	bool Compute(const std::string &equation);

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