
#include <iostream>
#include <fstream>

#include "gl/gl.h"
#include "GLFW/glfw3.h"
#include "glm/ext.hpp"

#include "gl/program.h"
#include "gl/vertex_array.h"
#include "gl/vertex.h"
#include "camera.h"
#include "dual_contour.h"

#include "gl/misc.h"

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
		
		// Vertex array
		VertexArray va;

		float t = (1.0f + sqrtf(5.0f)) / 2.0f;

		glm::vec3 positions[] = {
			glm::vec3{-1,  t,  0},
			glm::vec3{ 1,  t,  0},
			glm::vec3{-1, -t,  0},
			glm::vec3{ 1, -t,  0},
			glm::vec3{ 0, -1,  t},
			glm::vec3{ 0,  1,  t},
			glm::vec3{ 0, -1, -t},
			glm::vec3{ 0,  1, -t},
			glm::vec3{ t,  0, -1},
			glm::vec3{ t,  0,  1},
			glm::vec3{-t,  0, -1},
			glm::vec3{-t,  0,  1}
		};

		std::vector<Vertex> verts;
		auto addtri = [&verts, &positions](int i, int j, int k) {
			PushTriangle(verts,
				glm::normalize(positions[i]),
				glm::normalize(positions[j]),
				glm::normalize(positions[k]));
		};

		addtri(0, 11, 5);
		addtri(0, 5, 1);
		addtri(0, 1, 7);
		addtri(0, 7, 10);
		addtri(0, 10, 11);
		addtri(1, 5, 9);
		addtri(5, 11, 4);
		addtri(11, 10, 2);
		addtri(10, 7, 6);
		addtri(7, 1, 8);
		addtri(3, 9, 4);
		addtri(3, 4, 2);
		addtri(3, 2, 6);
		addtri(3, 6, 8);
		addtri(3, 8, 9);
		addtri(4, 9, 5);
		addtri(2, 4, 11);
		addtri(6, 2, 10);
		addtri(8, 6, 7);
		addtri(9, 8, 1);

		va.VertexData(&verts[0], verts.size());

		auto subdivide = [&verts, &va]() {
			std::vector<Vertex> new_verts;
			for (int i = 0; i < verts.size(); i += 3) {
				auto p0 = glm::normalize(verts[i + 0].position);
				auto p1 = glm::normalize(verts[i + 1].position);
				auto p2 = glm::normalize(verts[i + 2].position);

				auto m0 = glm::normalize(p0 + p1);
				auto m1 = glm::normalize(p1 + p2);
				auto m2 = glm::normalize(p2 + p0);

				PushTriangle(new_verts, p0, m0, m2);
				PushTriangle(new_verts, p1, m1, m0);
				PushTriangle(new_verts, p2, m2, m1);

				PushTriangle(new_verts, m0, m1, m2);
			}
			verts = new_verts;
			va.VertexData(&verts[0], verts.size());
		};

		GLcall(glEnable(GL_DEPTH_TEST));
		GLcall(glViewport(0, 0, 800, 800));

		bool mousePressed = false;
		bool spacePressed = false;
		while (!glfwWindowShouldClose(window)) {

			GLcall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLcall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

			program.Use();
			ASSERT(program.SetUniform("uView", camera.GetProjection()));
			ASSERT(program.SetUniform("uLightPos", camera.GetPosition()));
			//ASSERT(program.SetUniform("uLightPos", glm::vec3(10.0f, 2.0f, 5.0f)));

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

			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
				if (!spacePressed) {
					spacePressed = true;
					subdivide();
				}
			}
			else spacePressed = false;

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
}