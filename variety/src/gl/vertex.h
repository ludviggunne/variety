#pragma once

#include "attributes.h"
#include "glm/glm.hpp"

namespace gl {

	struct Vertex {
		glm::vec3 position;

		static const VertexLayout layout;
	};
}