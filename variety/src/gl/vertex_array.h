#pragma once

#include "buffer.h"

namespace gl {

	class VertexArray : private GLName {
	public:
		VertexArray();

		void Bind() const;
		void Draw(GLenum primitive_type) const;
		void VertexData(const Vertex *data, size_t size) const;
		void IndexData(const Index *data, size_t size);

	private:
		Buffer<Vertex> _vertexBuffer;
		Buffer<Index>  _indexBuffer;

		size_t _indexSize;
	};

}