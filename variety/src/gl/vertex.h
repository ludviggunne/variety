#pragma once

#include "attributes.h"
#include "glm/glm.hpp"

namespace gl {

	struct Vertex {
		glm::vec3 position;
		glm::vec3 normal;

		static const VertexLayout layout;
	};
}