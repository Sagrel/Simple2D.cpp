#shader vertex

#version 430 core

layout(location = 0) in vec4 pos;
layout(location = 1) in vec2 texPos;

out vec2 TexPos;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * pos;
	TexPos = texPos;
};


/*----------------------------------------------------------------*/

#shader fragment

#version 430 core

layout(location = 0) out vec4 col;

in vec2 TexPos;

uniform vec4 color;
uniform sampler2D Texture; 

void main()
{
	vec4 texColor = texture(Texture, TexPos) * color; // El color afecta
	
	//vec4 texColor = texture(Texture, TexPos); // El color no afecta
	col = texColor;
	//col = color;
};