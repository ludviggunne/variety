#pragma once

#include "vertex.h"

namespace gl {

	typedef unsigned int Index;
	
	template<typename T>
	class Buffer : private GLName {
	public:
		Buffer()
		{
			GLcall(glGenBuffers(1, &_id));
		}

		~Buffer()
		{
			GLcall(glDeleteBuffers(1, &_id));
		}

		void Bind() const
		{
			GLcall(glBindBuffer(_target, _id));
		}

		void Data(const T *data, size_t size) const 
		{
			GLcall(glBufferData(_target, size * sizeof(T), data, GL_STATIC_DRAW));
		}

	private:
		static const GLenum _target;
	};

	// Targets
	template<> const GLenum Buffer<Vertex>::_target = GL_ARRAY_BUFFER;
	template<> const GLenum Buffer<Index>::_target  = GL_ELEMENT_ARRAY_BUFFER;

}