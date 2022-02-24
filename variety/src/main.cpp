
#include <iostream>
#include <fstream>

#include "gl/gl.h"
#include "GLFW/glfw3.h"

#include "gl/program.h"
#include "gl/vertex_array.h"

int main() {

	glfwInit();
	GLFWwindow *window = glfwCreateWindow(800, 800, "Test", NULL, NULL);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwSwapInterval(1);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// GL objects scope
	{
		using namespace gl;

		// Render data
		const Vertex vertices[4] = {
			Vertex{glm::vec3(-.5f, -.5f, 0.0f)},
			Vertex{glm::vec3(0.5f, -.5f, 0.0f)},
			Vertex{glm::vec3(-.5f, 0.5f, 0.0f)},
			Vertex{glm::vec3(0.5f, 0.5f, 0.0f)}
		};

		const Index indices[6] = {
			0, 1, 2,
			1, 2, 3
		};

		// Vertex array setup
		VertexArray va;
		va.VertexData(vertices, 4);
		va.IndexData(indices, 6);

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

		auto
			vs = vss.str(),
			fs = fss.str();

		std::stringstream log;
		if (!program.ComileAndLink(vs.c_str(), fs.c_str(), log)) {
			std::cout << log.str();
			__debugbreak();
		}


		while (!glfwWindowShouldClose(window)) {

			GLcall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLcall(glClear(GL_COLOR_BUFFER_BIT));

			program.Use();

			va.Bind();
			va.VertexData(vertices, 4);
			va.IndexData(indices, 6);

			va.Draw(GL_TRIANGLES);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
}