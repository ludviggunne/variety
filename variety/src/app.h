#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "dual_contour.h"
#include "gl/program.h"
#include "gl/vertex_array.h"
#include "camera.h"

#define EQBUFSIZE 64

class Application {

public:
	Application();
	~Application();

	void Run();

private:
	// setup
	bool WindowInit();
	bool GLInit();
	bool ImguiInit();

	// frame
	void ImguiWindow();

private:
	// callbacks
	static void ResizeCallback(GLFWwindow *window, int width, int height);
	static void ScrollCallback(GLFWwindow *window, double xoffset, double yoffset);

private:
	bool _running;

	glm::vec3 _backgroundColor;

	GLFWwindow *_window;
	int _width, _height;

	DualContour _dualContour;

	gl::VertexArray *_vertexArray;
	gl::Program *_program;
	Camera _camera;

	char _equationBuffer[EQBUFSIZE];

	
};