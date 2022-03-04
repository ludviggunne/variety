#include "settings.h"

namespace Settings {

	// Camera
	const float CameraInitXRotation  = 15.0f;
	const float CameraInitYRotation  = 15.0f;
	const float CameraInitDistance   = 5.0f;
	const glm::vec3 CameraInitCenter = glm::vec3(0.0f, 0.0f, 0.0f);

	const float CameraRotateSpeed = 0.5f;
	const float CameraZoomSpeed   = 1.0f;
	extern const float CameraPanSpeed = 0.002f;

	const float CameraYRotClampAngle = 70.0f;

	// Mesh builder
	const float BuilderInitXMin = -2.0f;
	const float BuilderInitYMin = -2.0f;
	const float BuilderInitZMin = -2.0f;

	const float BuilderInitXMax = 2.0f;
	const float BuilderInitYMax = 2.0f;
	const float BuilderInitZMax = 2.0f;

	const int BuilderInitResolution = 128;

	const char *BuilderDefaultEquation = "x*y/z=x*z/y+y*z";

	// Window
	const int WindowInitWidth = 800;
	const int WindowInitHeight = 800;


	// Perspective
	const float PerspectiveFOV = 45.0f;


	// Theme
	const glm::vec3 BackgroundColor = glm::vec3(0.1f, 0.1f, 0.1f);
	const glm::vec3 SurfaceColor    = glm::vec3(0.8f, 0.8f, 0.8f);
	const glm::vec3 LightColor      = glm::vec3(1.0f, 1.0f, 0.6f);
	const glm::vec3 GraphColor      = glm::vec3(1.0f, 1.0f, 1.0f);
	const glm::vec3 AmbientColor    = glm::vec3(0.2f, 0.2f, 1.0f);
	const float     AmbientStrength = 0.2f;
}
