#include "misc.h"

namespace gl {

	void PushTriangle(std::vector<Vertex> &vertices, 
		const glm::vec3 &v1, const glm::vec3 &v2, const glm::vec3 &v3)
	{
		auto normal = glm::cross(v2 - v1, v3 - v1);

		vertices.push_back(Vertex{ v1, normal });
		vertices.push_back(Vertex{ v2, normal });
		vertices.push_back(Vertex{ v3, normal });
	}

}