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

		bool ComileAndLink(const std::string &vsource, const std::string &fsource, std::stringstream &log) const;
		void Use() const;

		template<typename T>
		bool SetUniform(const char *name, const T &value) { return false; }

		template<typename T>
		bool SetUniform(const char *name, const T *arr, size_t size) { return false; }




		// (Vtodo): add more uniform setters 
		template<>
		bool SetUniform<glm::mat4>(const char *name, const glm::mat4 &value)
		{
			auto location = GetUniformLocation(name);

			if (location == -1)
				return false;

			GLcall(glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value)));

			return true;
		}

		template<>
		bool SetUniform<glm::vec4>(const char *name, const glm::vec4 &value)
		{
			auto location = GetUniformLocation(name);

			if (location == -1)
				return false;

			glUniform1fv(location, 4, glm::value_ptr(value));

			return true;
		}



	private:
		int GetUniformLocation(const char *name);

	private:
		std::map<const char *, GLint> _uniformLocations;

	};
}