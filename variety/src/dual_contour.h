#pragma once

#include "settings.h"
#include "gl/vertex.h"

#include "exprtk/exprtk.hpp"

class DualContour {
public:
	enum class State { Standby, Compute, Present };

public:
	DualContour();
	~DualContour();

	bool Compute(const std::string &equation);

	std::vector<gl::Vertex> const *GetVertices();
	State GetState() const { return _state; }
	float GetProgress() const { return _progress; }

private:
	void ICompute(const exprtk::expression<float> &expr, 
		float &var_x, float &var_y, float &var_z);

public:
	union {
		struct {
			float xMin, yMin, zMin;
		};
		float min[3];
	};
	union {
		struct {
			float xMax, yMax, zMax;
		};
		float max[3];
	};
	int resolution;

private:
	float _progress;
	State _state;
	std::vector<gl::Vertex> *_vertices;

	// EXPRTK
	float _varX;
	float _varY;
	float _varZ;
	exprtk::symbol_table<float> _symbolTable;
};