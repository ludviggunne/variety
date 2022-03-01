
#include <iostream>
#include <fstream>

#include "gl/gl.h"
#include "GLFW/glfw3.h"
#include "glm/ext.hpp"

#include "gl/program.h"
#include "gl/vertex_array.h"
#include "gl/vertex.h"
#include "camera.h"

#define ASSERT(x) if(!(x)) __debugbreak();

Camera camera;
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
	camera.OnScroll(yoffset);
}

int main() {

	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow *window = glfwCreateWindow(800, 800, "Test", NULL, NULL);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwSetScrollCallback(window, scrollCallback);

	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};

	// GL objects scope
	{
		using namespace gl;

		// Program setup
		Program program;

		// Load shader source files
		std::ifstream vsource("shaders/shader.vert.glsl");
		if (!vsource) std::cout << "Couldn't open vertex shader source file.\n";

		std::ifstream fsource("shaders/shader.frag.glsl");
		if (!fsource) std::cout << "Couldn't open fragment shader source file.\n";

		std::stringstream vss, fss;
		std::string line;
		
		while (std::getline(vsource, line)) vss << line << '\n';
		while (std::getline(fsource, line)) fss << line << '\n';

		std::stringstream log;
		if (!program.CompileAndLink(vss.str(), fss.str(), log)) {
			std::cout << log.str();
			__debugbreak();
		}

		ASSERT(program.SetUniform("uProj", glm::perspective(45.0f, 1.0f, .1f, 100.0f)));
		//program.SetUniform("uProj", glm::mat4(1.0f));
		
		// Vertex array
		VertexArray va;

		const unsigned int nVert = sizeof(vertices) / sizeof(Vertex);
		auto vertex_ptr = (Vertex *)vertices;
		va.VertexData(vertex_ptr, nVert);

		Index indices[nVert];
		for (int i = 0; i < nVert; i++)
			indices[i] = i;
		va.IndexData(indices, nVert);


		// Camera

		GLcall(glEnable(GL_DEPTH_TEST));
		GLcall(glViewport(0, 0, 800, 800));

		bool mousePressed = false;
		while (!glfwWindowShouldClose(window)) {

			GLcall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLcall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			program.Use();
			ASSERT(program.SetUniform("uView", camera.GetProjection()));
			ASSERT(program.SetUniform("uLightPos", camera.GetPosition()));

			va.Bind();
			va.Draw(GL_TRIANGLES);

			// Handle input
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {

				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);
				glm::vec2 mousePos(static_cast<float>(xpos), static_cast<float>(ypos));


				if (!mousePressed)
				{
					mousePressed = true;
					camera.OnMousePress(mousePos, true, Camera::Action::Rotation);
				}
				else {
					camera.OnMousePress(mousePos, false, Camera::Action::Rotation);
				}
			}
			else {
				mousePressed = false;
			}

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
}