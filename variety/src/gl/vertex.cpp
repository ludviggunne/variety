#include "vertex.h"

namespace gl {

	static VertexLayout GetLayout() {
		VertexLayout layout;

		layout.PushAttribute(VertexAttribute(3, GL_FLOAT)); // position
		layout.PushAttribute(VertexAttribute(3, GL_FLOAT)); // normal

		return layout;
	}

	const VertexLayout Vertex::layout = GetLayout();

}