#version 330 core

layout (location = 0) in vec4 positionIn;
layout (location = 1) in vec4 colorIn;
layout (location = 2) in vec2 vertexUV;

uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;

out vec4 vertexColor;
out vec2 UVCoords;

void main()
{
	gl_Position = pMatrix * vMatrix * mMatrix * positionIn;
	vertexColor = colorIn;
	UVCoords = vertexUV;
}