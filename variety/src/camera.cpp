#include "camera.h"

glm::mat4 Camera::GetProjection() const
{
	const glm::vec3 up(0.0f, 1.0f, 0.0f);

	return glm::lookAt(GetPosition(), _center, up);
}

glm::vec3 Camera::GetPosition() const
{
	glm::vec3 position(0.0f, 0.0f, _distance);
	position = glm::rotate(position, _yRotation, glm::vec3(1.0f, 0.0f, 0.0f));
	position = glm::rotate(position, _xRotation, glm::vec3(0.0f, 1.0f, 0.0f));

	return position;
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
		_xRotation = xRotOffset - Settings::CameraRotateSpeed * (mousePos.x - mouseOffset.x);
		_yRotation = yRotOffset - Settings::CameraRotateSpeed * (mousePos.y - mouseOffset.y);
		break;

	case Action::Pan:

		break;
	}
}

void Camera::OnScroll(double offset)
{
	_distance -= offset * Settings::CameraZoomSpeed;
	if (_distance < 0)
		_distance += Settings::CameraZoomSpeed;
}
