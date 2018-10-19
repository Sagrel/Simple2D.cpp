#include "VertexArray.h"



VertexArray::VertexArray()
{

	glGenVertexArrays(1, &RendererID);
}


VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vd, const VertexBufferLayout& layout)
{
	Bind();
	vd.Bind();

	const auto& elementos = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elementos.size(); i++)
	{
		const auto& elemento = elementos[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, elemento.count, elemento.type, elemento.normalized, layout.GetStride(), (const void*)offset);
		offset += elemento.count * 4;
	}


}
