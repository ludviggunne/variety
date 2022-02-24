#include "vertex_array.h"

namespace gl {

	VertexArray::VertexArray() : _indexSize(0)
	{
		GLcall(glGenVertexArrays(1, &_id));
		GLcall(glBindVertexArray(_id));

		_vertexBuffer.Bind();
		_indexBuffer.Bind();
		Vertex::layout.Enable();

		GLcall(glBindVertexArray(0));
	}

	void VertexArray::Bind() const
	{
		GLcall(glBindVertexArray(_id));
	}

	void VertexArray::Draw(GLenum primitive_type) const
	{
		Bind();
		GLcall(glDrawElements(primitive_type, _indexSize, GL_UNSIGNED_INT, 0));
	}

	void VertexArray::VertexData(const Vertex *data, size_t size) const
	{
		_vertexBuffer.Bind();
		_vertexBuffer.Data(data, size);
	}

	void VertexArray::IndexData(const Index *data, size_t size)
	{
		_indexBuffer.Bind();
		_indexBuffer.Data(data, size);

		_indexSize = size;
	}

}