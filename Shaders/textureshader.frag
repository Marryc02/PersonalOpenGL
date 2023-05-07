#version 330 core

out vec4 FragColor;
in vec4 vertexColor;
in vec2 UVCoords;

uniform sampler2D theTexture;

void main()
{
	FragColor = texture(theTexture,UVCoords) * vec4(1.0f);
	//FragColor = vertexColor;
}