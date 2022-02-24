#include "vertex.h"

namespace gl {

	static VertexLayout GetLayout() {
		VertexLayout layout;

		layout.PushAttribute(VertexAttribute(3, GL_FLOAT));

		return layout;
	}

	const VertexLayout Vertex::layout = GetLayout();

}