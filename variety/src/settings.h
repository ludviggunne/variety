#pragma once

#include "glm/glm.hpp"

namespace Settings {

// Initial parameters
	// Camera
	extern const float CameraInitXRotation;
	extern const float CameraInitYRotation;
	extern const float CameraInitDistance;
	extern const glm::vec3 CameraInitCenter;

	extern const float CameraRotateSpeed;
	extern const float CameraZoomSpeed;

	extern const float CameraYRotClampAngle;
};