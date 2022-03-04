#pragma once

#include "glm/ext.hpp"

#include "settings.h"

class Camera {
public:
	enum class Action { Rotation, Pan };
	Camera() : 
		_center(   Settings::CameraInitCenter),
		_xRotation(Settings::CameraInitXRotation), 
		_yRotation(Settings::CameraInitYRotation),
		_distance( Settings::CameraInitDistance)
	{
	}

	glm::mat4 GetProjection() const;
	glm::vec3 GetPosition() const;

	void OnMousePress(const glm::vec2 mousePos, bool instance, Action action);
	void OnScroll(double offset);
	void ResetCenter() { _center = Settings::CameraInitCenter; }


private:
	glm::vec3 _center;
	float _xRotation;
	float _yRotation;
	float _distance;
};