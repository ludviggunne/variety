#include "gl.h"

void GLClearError()
{
	while (glGetError()) {}
}

bool GLLogError(const char *file, int line, const char *func)
{
	bool _break = false;
	while (GLint error = glGetError()) {
		std::cout << "OpenGL error 0x" << std::hex << error << std::dec << ":\n"
			"\tFile: " << file << "\n"
			"\tFunction: " << func << "\n"
			"\tLine: " << line << "\n";

		_break = true;
	}

	return _break;
}