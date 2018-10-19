#pragma once


#include <string>
#include "../Dependencias/GLWE/include/GL/glew.h"

class Shape
{
public:
	Shape(const std::string& path);
	~Shape();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return width; }
	inline int GeHeight() const { return height; }

private:
	unsigned int RendererID;
	std::string path;
	unsigned char* localBuffer;
	int width, height, BPP;
};