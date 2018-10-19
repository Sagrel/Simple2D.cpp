#pragma once


#include "../Dependencias/GLWE/include/GL/glew.h"
#include "../Dependencias/GLFW/include/GLFW/glfw3.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"


class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

private:
};

void APIENTRY GLerrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);