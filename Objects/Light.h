#pragma once

#include "../VisualObject.h"
#include "../FileLoader.h"

class Shader;

class Light : public VisualObject, public FileLoader
{
public:

	Light();
	// Ambient lighting
	Light(GLfloat r, GLfloat g, GLfloat b, GLfloat intensity, Shader* shaderRef);
	// Ambient & Diffuse lighting
	Light(GLfloat r, GLfloat g, GLfloat b, GLfloat intensity, GLfloat dIntensity, Shader* shaderRef);


	void DrawMesh(float scale);

	// Use only ambient light
	void UseLightAmb(GLuint LightIntensityLocation, GLfloat LightColorLocation, GLfloat DiffuseIntensityLocation
		, GLfloat SpecularStrengthLocation);
	// Use both ambient and diffuse light
	void UseLightDif(GLuint LightIntensityLocation, GLfloat LightColorLocation, GLfloat DiffuseIntensityLocation,
		GLint LightPositionLocation);


	void SetLightPosition(glm::vec3 newPos);


	void init(glm::mat4 matrixUniform);
	void draw();

	glm::vec3 lightPos;

private:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
	glm::vec3 direction;

	Shader* ShaderRef;
};

