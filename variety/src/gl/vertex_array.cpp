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
		//GLcall(glDrawElements(primitive_type, _indexSize, GL_UNSIGNED_INT, 0));

		// Changing to this call makes the index buffer component of the vertex array obsolete
		// But this is the way to go as i will be creating mesh triangle by triangle, and vertices wont be reused
		// as it would be too complicated within the dual contour algorithm
		GLcall(glDrawArrays(GL_TRIANGLES, 0, _vertexBuffer.Size()));
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