#pragma once


#include <string>
#include "../Dependencias/GLWE/include/GL/glew.h"

class Shape
{
public:
	Shape(const std::string& path);
	Shape(Shape&& s);
	~Shape();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

private:
	unsigned int RendererID;
};
