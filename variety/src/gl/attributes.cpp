#include "attributes.h"

namespace gl {

	void VertexLayout::PushAttribute(const VertexAttribute &attr)
	{
		_attributes.push_back(attr);
		_stride += attr.TypeSize() * attr.Count;
	}

	void VertexLayout::Enable() const
	{
		int index  = 0;
		int offset = 0;
		
		for (auto &attr : _attributes) {

			GLcall(glVertexAttribPointer(index, attr.Count, attr.Type, GL_FALSE, _stride, (const void *)offset));
			GLcall(glEnableVertexAttribArray(index));

			offset += attr.TypeSize() * attr.Count;
			index++;
		}
	}

}