#include "Shader.h"
#include "Renderer.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>


Shader::Shader(const std::string& path)
{
	ShaderSource shaders = parseShader(path);
	RendererID = crearShader(shaders.vertexSource, shaders.fragmentSource);
	std::cout << RendererID << std::endl;
}


Shader& Shader::operator=(Shader&& s)
{
	RendererID = s.RendererID;
	localizaciones = s.localizaciones;
	s.copiando = true;
	return *this;
}

Shader::~Shader()
{
	if(!copiando)
	glDeleteProgram(RendererID);
}

void Shader::Bind() const
{
	glUseProgram(RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int x)
{
	glUniform1i(GetUniformLocation(name), x);
}

void Shader::SetUniform4f(const std::string& name, float x, float y, float z, float w)
{
	glUniform4f(GetUniformLocation(name), x, y, z, w);
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4& mat)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (localizaciones.find(name) != localizaciones.end())
		return localizaciones[name];

	int loc = glGetUniformLocation(RendererID, name.c_str());
	if (loc == -1)
		std::cout << "Uniform: " << name << " no existe" << std::endl;
	else
		localizaciones[name] = loc;
	return loc;
	
}

unsigned int Shader::crearShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int programa = glCreateProgram();
	unsigned int vs = compilarShader(vertexShader, GL_VERTEX_SHADER);
	unsigned int fs = compilarShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(programa, vs);
	glAttachShader(programa, fs);
	glLinkProgram(programa);
	glValidateProgram(programa);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return programa;
}

unsigned int Shader::compilarShader(const std::string& source, unsigned int tipo)
{
	unsigned int id = glCreateShader(tipo);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int resultado;
	glGetShaderiv(id, GL_COMPILE_STATUS, &resultado);
	if (resultado == GL_FALSE)
	{
		int longitud;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &longitud);
		char* mensaje = (char*)alloca(longitud * sizeof(char));
		glGetShaderInfoLog(id, longitud, &longitud, mensaje);
		std::cout << "Fallo al compilar shader:   " << mensaje << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

ShaderSource Shader::parseShader(const std::string& path)
{
	std::ifstream stream(path);

	enum class ShaderType
	{
		VERTEX = 0, FRAGMENT = 1
	};
	std::string linea;
	std::stringstream ss[2];
	ShaderType tipo;

	while (getline(stream, linea))
	{
		if (linea.find("#shader") != std::string::npos)
		{
			if (linea.find("vertex") != std::string::npos)
				tipo = ShaderType::VERTEX;

			else
				tipo = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)tipo] << linea << "\n";
		}
	}

	return { ss[0].str(), ss[1].str() };
}



