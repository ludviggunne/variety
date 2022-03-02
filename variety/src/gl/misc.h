#pragma once

#include <vector>

#include "gl.h"
#include "vertex.h"

namespace gl {
	
	void PushTriangle(std::vector<Vertex> &,
		const glm::vec3 &, const glm::vec3 &, const glm::vec3 &);

}