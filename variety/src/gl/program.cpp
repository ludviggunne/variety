#include "program.h"

namespace gl {

	Program::Program()
	{
		GLcall(_id = glCreateProgram());
	}

	Program::~Program()
	{
		GLcall(glDeleteProgram(_id));
	}

	bool Program::CompileAndLink(const std::string &vsource, const std::string &fsource, std::stringstream &log) const
	{
		// Create shaders and submit sources
		GLuint vshader, fshader;

		GLcall(vshader = glCreateShader(GL_VERTEX_SHADER));
		GLcall(fshader = glCreateShader(GL_FRAGMENT_SHADER));

		const char *vsource_ptr, *fsource_ptr;

		vsource_ptr = vsource.c_str();
		fsource_ptr = fsource.c_str();

		GLcall(glShaderSource(vshader, 1, &vsource_ptr, NULL));
		GLcall(glShaderSource(fshader, 1, &fsource_ptr, NULL));

		// Compile shaders
		bool success = true;
		int status;
		char _log[512];

		// Vertex shader
		GLcall(glCompileShader(vshader));
		GLcall(glGetShaderiv(vshader, GL_COMPILE_STATUS, &status));

		if (!status) {
			GLcall(glGetShaderInfoLog(vshader, 512, 0, _log));
			log << "Failed to compile vertex shader: " << _log << '\n';
			success = false;
		}

		// Fragment shader
		GLcall(glCompileShader(fshader));
		GLcall(glGetShaderiv(fshader, GL_COMPILE_STATUS, &status));

		if (!status) {
			GLcall(glGetShaderInfoLog(fshader, 512, 0, _log));
			log << "Failed to compile fragment shader: " << _log << '\n';
			success = false;
		}

		// Attach to and link program
		GLcall(glAttachShader(_id, vshader));
		GLcall(glAttachShader(_id, fshader));
		GLcall(glLinkProgram(_id));

		GLcall(glGetProgramiv(_id, GL_LINK_STATUS, &status));

		if (!status) {
			GLcall(glGetProgramInfoLog(_id, 512, 0, _log));
			log << "Failed to link shader program: " << _log << '\n';
			success = false;
		}


		// Cleanup
		GLcall(glDeleteShader(vshader));
		GLcall(glDeleteShader(fshader));

		return success;
	}

	void Program::Use() const
	{
		GLcall(glUseProgram(_id));
	}

	int Program::GetUniformLocation(const char *name)
	{
		auto it = _uniformLocations.find(name);

		if (it == _uniformLocations.end())
		{
			GLint location;
			GLcall(location = glGetUniformLocation(_id, name));

			if (location > -1)
				_uniformLocations[name] = location;

			return location;
		}

		return _uniformLocations[name];
	}

}