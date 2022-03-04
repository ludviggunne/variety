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

	// Mesh builder
	extern const float BuilderInitXMin;
	extern const float BuilderInitYMin;
	extern const float BuilderInitZMin;

	extern const float BuilderInitXMax;
	extern const float BuilderInitYMax;
	extern const float BuilderInitZMax;

	extern const int BuilderInitResolution;

	extern const char *BuilderDefaultEquation;

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