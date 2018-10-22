#pragma once

#include <string>
#include <unordered_map>


#include "../vendor/glm/glm.hpp"

struct ShaderSource
{
	std::string vertexSource;
	std::string fragmentSource;
};


class Shader
{
public:
	Shader() = default;
	Shader(const std::string& path);
	~Shader();

	void Bind() const;
	void Unbind() const;

	Shader& operator=(Shader&& s);

	void SetUniform1i(const std::string& name, int x);
	void SetUniform4f(const std::string& name, float x, float y, float z, float w);
	void SetUniformMat4f(const std::string& name, glm::mat4& mat);

private:
	unsigned int RendererID = 0;
	std::unordered_map<std::string, int> localizaciones;
	bool copiando = false;

	int GetUniformLocation(const std::string& name);
	unsigned int crearShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int compilarShader(const std::string& source, unsigned int tipo);
	ShaderSource parseShader(const std::string& path);
};

