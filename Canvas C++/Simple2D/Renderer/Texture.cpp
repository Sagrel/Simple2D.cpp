#include "Texture.h"

#include "../vendor/stb_image/stb_image.h"



Shape::Shape(const std::string& path) : RendererID(0), path(path), localBuffer(nullptr), width(0), height(0), BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	localBuffer = stbi_load(path.c_str(), &width, &height, &BPP, 4);

	glGenTextures(1, &RendererID);
	glBindTexture(GL_TEXTURE_2D, RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (localBuffer)
		stbi_image_free(localBuffer);
	
}

Shape::~Shape()
{
	glDeleteTextures(1, &RendererID);
}

void Shape::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, RendererID);
}

void Shape::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
