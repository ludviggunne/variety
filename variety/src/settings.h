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
	extern const float CameraPanSpeed;

	extern const float CameraYRotClampAngle;

	// Algorithm
	extern const float DualInitXMin;
	extern const float DualInitYMin;
	extern const float DualInitZMin;

	extern const float DualInitXMax;
	extern const float DualInitYMax;
	extern const float DualInitZMax;

	extern const int DualInitResolution;

	extern const char *DualDefaultEquation;

	// Window
	extern const int WindowInitWidth;
	extern const int WindowInitHeight;

	// Perspective
	extern const float PerspectiveFOV;


	// Theme
	extern const glm::vec3 BackgroundColor;
	extern const glm::vec3 SurfaceColor;
	extern const glm::vec3 LightColor;
	extern const glm::vec3 GraphColor;
	extern const glm::vec3 AmbientColor;
	extern const float     AmbientStrength;
};