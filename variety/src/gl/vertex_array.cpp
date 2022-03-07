#include "vertex_array.h"

namespace gl {

	VertexArray::VertexArray()
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

		// Vtodo: Current implementation makes no use of index buffer member. Consider removing it.
		GLcall(glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(_vertexBuffer.Size())));
	}

	void VertexArray::VertexData(const Vertex *data, size_t size)
	{
		_vertexBuffer.Bind();
		_vertexBuffer.Data(data, size);
	}

	void VertexArray::IndexData(const Index *data, size_t size)
	{
		_indexBuffer.Bind();
		_indexBuffer.Data(data, size);
	}

}