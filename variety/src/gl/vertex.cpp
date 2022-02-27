#include "vertex.h"

#define PushVertexAttribute(name)\
	layout.PushAttribute(VertexAttribute::FromType<decltype(Vertex:: name)>())

namespace gl {

	static VertexLayout GetLayout() {
		VertexLayout layout;

		PushVertexAttribute(position);
		PushVertexAttribute(normal);

		return layout;
	}

	const VertexLayout Vertex::layout = GetLayout();

}