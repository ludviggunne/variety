#include "settings.h"

namespace Settings {

	// Camera
	const float CameraInitXRotation  = 15.0f;
	const float CameraInitYRotation  = 15.0f;
	const float CameraInitDistance   = 5.0f;
	const glm::vec3 CameraInitCenter = glm::vec3(0.0f, 0.0f, 0.0f);

	const float CameraRotateSpeed = 0.5f;
	const float CameraZoomSpeed   = 1.0f;

	const float CameraYRotClampAngle = 70.0f;

	// Algorithm
	const float DualInitXMin = -1.0f;
	const float DualInitYMin = -1.0f;
	const float DualInitZMin = -1.0f;

	const float DualInitXMax = 1.0f;
	const float DualInitYMax = 1.0f;
	const float DualInitZMax = 1.0f;

	const float DualInitStepSize = .01f;

	const char *DualDefaultEquation = "x*x + y*y = z";

	// Window
	const int WindowInitWidth = 800;
	const int WindowInitHeight = 800;


	// Perspective
	const float PerspectiveFOV = 45.0f;


	// Theme
	const glm::vec3 BackgroundColor = glm::vec3(0.1f, 0.1f, 0.1f);
	const glm::vec3 LightColor = glm::vec3(1.0f, 1.0f, 0.8f);
	const glm::vec3 GraphColor = glm::vec3(1.0f, 1.0f, 1.0f);
	const glm::vec3 AmbientColor = glm::vec3(0.7f, 0.7f, 1.0f);
	const float     AmbientStrength = 0.1f;
}
