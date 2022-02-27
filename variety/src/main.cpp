
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

		while (!glfwWindowShouldClose(window)) {

			GLcall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
			GLcall(glClear(GL_COLOR_BUFFER_BIT));

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
}