#version 330 core

layout (location = 0) in vec4 positionIn;
layout (location = 1) in vec4 colorIn;

uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;

out vec4 objectColor;

void main()
{
	gl_Position = pMatrix * vMatrix * mMatrix * positionIn;
	objectColor = colorIn;
}