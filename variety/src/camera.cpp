#include "camera.h"

glm::mat4 Camera::GetProjection() const
{
	const glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 position = _center + glm::vec3(
		_distance * glm::cos(_xRotation) * glm::cos(_yRotation),
		_distance * glm::sin(_xRotation),
		_distance * glm::cos(_xRotation) * glm::sin(_yRotation)
	);

	return glm::lookAt(position, _center, up);
}

void Camera::OnMousePress(const glm::vec2 mousePos, bool instance, Action action)
{
	static glm::vec2 mouseOffset(0, 0);
	static float xRotOffset = 0.0f;
	static float yRotOffset = 0.0f;
	static Action static_action = Action::Rotation;

	if (instance) {
		mouseOffset = mousePos;
		xRotOffset  = _xRotation;
		yRotOffset  = _yRotation;

		static_action = action;
	}

	switch (static_action) {
	case Action::Rotation:
		_xRotation = xRotOffset + Settings::CameraRotateSpeed * (mousePos.x - mouseOffset.x);
		_yRotation = yRotOffset + Settings::CameraRotateSpeed * (mousePos.y - mouseOffset.y);
		break;

	case Action::Pan:

		break;
	}
}

void Camera::OnScroll(double offset)
{
	_distance += offset * Settings::CameraZoomSpeed;
	if (_distance < 0)
		_distance -= Settings::CameraZoomSpeed;
}
