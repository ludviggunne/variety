#pragma once

#include <vector>

#include "gl.h"

namespace gl {

	struct VertexAttribute {

		VertexAttribute(int count, GLenum type) : Count(count), Type(type) {}

		int Count;
		GLenum Type;

		int TypeSize() const {
			switch (Type) {

				case(GL_FLOAT): return sizeof(float);
				case(GL_INT):   return sizeof(int);
			}
		}
	};

	class VertexLayout {
	public:
		VertexLayout() : _stride(0) {}

		void PushAttribute(const VertexAttribute &attr);
		void Enable() const;

	private:
		std::vector<VertexAttribute> _attributes;
		int _stride;
	};

}
