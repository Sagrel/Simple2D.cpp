#pragma once
#include <vector>

#include "../Dependencias/GLWE/include/GL/glew.h"


struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() : stride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		Elementos.push_back({ GL_FLOAT, count, GL_FALSE });
		stride += sizeof(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		Elementos.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		stride += sizeof(GL_UNSIGNED_INT) * count;
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return Elementos; }

	inline unsigned int GetStride() const { return stride; }

private:
	std::vector<VertexBufferElement> Elementos;
	unsigned int stride;
};

