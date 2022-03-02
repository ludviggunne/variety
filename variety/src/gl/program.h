#pragma once

#include <sstream>
#include <map>

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "gl.h"

namespace gl {

	class Program : private GLName
	{
	public:
		Program();
		~Program();

		bool CompileAndLink(const std::string &vsource, const std::string &fsource, std::stringstream &log) const;
		void Use() const;

		template<typename T>
		bool SetUniform(const char *name, const T &value) { return false; }

		template<typename T>
		bool SetUniform(const char *name, const T *arr, size_t size) { return false; }




		// (Vtodo): add more uniform setters
		// (Vtodo): change name parameter to int location, add public getlocation method
		template<>
		bool SetUniform<float>(const char *name, const float &value)
		{
			this->Use();
			int location = GetUniformLocation(name);

			if (location == -1)
				return false;

			GLcall(glUniform1f(location, value));

			return true;
		}
		
		template<>
		bool SetUniform<glm::mat4>(const char *name, const glm::mat4 &value)
		{
			this->Use();
			int location = GetUniformLocation(name);

			if (location == -1)
				return false;

			GLcall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));

			return true;
		}

		template<>
		bool SetUniform<glm::vec4>(const char *name, const glm::vec4 &value)
		{
			this->Use();
			int location = GetUniformLocation(name);

			if (location == -1)
				return false;

			GLcall(glUniform4f(location, value.r, value.g, value.b, value.a));

			return true;
		}

		template<>
		bool SetUniform<glm::vec3>(const char *name, const glm::vec3 &value)
		{
			this->Use();
			int location = GetUniformLocation(name);

			if (location == -1)
				return false;

			GLcall(glUniform3f(location, value.x, value.y, value.z));

			return true;
		}

		template<>
		bool SetUniform<glm::vec2>(const char *name, const glm::vec2 &value)
		{
			this->Use();
			int location = GetUniformLocation(name);

			if (location == -1)
				return false;

			GLcall(glUniform2f(location, value.x, value.y));
			return true;
		}



	private:
		int GetUniformLocation(const char *name);

	private:
		std::map<const char *, GLint> _uniformLocations;

	};
}