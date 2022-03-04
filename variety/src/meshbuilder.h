#pragma once

#include "settings.h"
#include "gl/vertex.h"

#include "exprtk/exprtk.hpp"

class MeshBuilder {
public:
	enum class State { Standby, Compute, Present };

public:
	MeshBuilder();
	~MeshBuilder();

	bool Compute(const std::string &equation);

	std::vector<gl::Vertex> const *GetVertices();
	State GetState() const { return _state; }
	float GetProgress() const { return _progress; }
	const char *GetProgressString() const { return _progressStr; }
	void Cancel() { if (_state == State::Compute) _cancel = true; }

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
	const char *_progressStr;
	State _state;
	std::vector<gl::Vertex> *_vertices;

	bool _cancel;

	// EXPRTK
	float _varX;
	float _varY;
	float _varZ;
	exprtk::symbol_table<float> _symbolTable;

private:
	// Progress strings
	static const char *_psNone;
	static const char *_psSampling;
	static const char *_psBuilding;
};