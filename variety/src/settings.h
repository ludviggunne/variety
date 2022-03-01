#pragma once

#include "glm/glm.hpp"

namespace Settings {

	// Camera
	extern const float CameraInitXRotation;
	extern const float CameraInitYRotation;
	extern const float CameraInitDistance;
	extern const glm::vec3 CameraInitCenter;

	extern const float CameraRotateSpeed;
	extern const float CameraZoomSpeed;

	extern const float CameraYRotClampAngle;

	// Algorithm
	extern const float DualInitXMin;
	extern const float DualInitYMin;
	extern const float DualInitZMin;

	extern const float DualInitXMax;
	extern const float DualInitYMax;
	extern const float DualInitZMax;

	extern const float DualInitStepSize;

	extern const char *DualDefaultEquation;
};