#pragma once



#include <iostream>
#include <string>

#include "Renderer\Renderer.h"
#include "Renderer\IndexBuffer.h"
#include "Renderer\VertexBuffer.h"
#include "Renderer\VertexArray.h"
#include "Renderer\Shader.h"
#include "Renderer\Texture.h"


#include "vendor\glm\glm.hpp"
#include "vendor\glm\gtc\matrix_transform.hpp"


void SetColor(int r, int g, int b);
void DrawCircle(int x, int y, int r);
void DrawRect(int x, int y, int w);
void DrawRect(int x, int y, int w, int h);
void DrawLine(int x1, int y1, int x2, int y2, int w);
void DrawShape(int i, int x, int y, float w, float h, float r);
void DrawShape(int i, int x, int y, float w, float h);
void DrawShape(int i, int x, int y, float w);
void ReSize(GLFWwindow* v, int w, int h);
bool MouseButtonDown(int i);
bool MouseButtonUp(int i);
bool MouseButton(int i);
int MouseX();
int MouseY();
void Clear();
int Width();
int Height();

bool Buttom(int x, int y, int r);
bool Buttom(int x, int y, int w, int h);