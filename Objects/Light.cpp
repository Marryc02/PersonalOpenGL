#include "Light.h"

#include <iostream>

Light::Light()
{
	DrawMesh(0.0f);
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	direction = glm::vec3(0.0f, -1.0f, 0.0f); // pointing downwards

	ambientIntensity = 0.3f;
	diffuseIntensity = 0.8f;
}

Light::Light(GLfloat r, GLfloat g, GLfloat b, GLfloat intensity, Shader* shaderRef)
{
	ShaderRef = shaderRef;
	DrawMesh(0.0f);
	color = glm::vec3(r, g, b);
	ambientIntensity = intensity;
}

Light::Light(GLfloat r, GLfloat g, GLfloat b, GLfloat intensity, GLfloat dIntensity, Shader* shaderRef)
{
	ShaderRef = shaderRef;
	DrawMesh(0.0f);
	color = glm::vec3(r, g, b);
	ambientIntensity = intensity;
	diffuseIntensity = dIntensity;
}

void Light::DrawMesh(float scale)
{
	ReadFile("Shapes/CubeVertices.txt", mVertices);
	ReadFileIndices("Shapes/CubeIndices.txt", mIndices);

	for (int i = 0; i < mVertices.size(); i++)
	{
		mVertices[i].rgb = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	for (int i = 0; i <= mVertices.size() - 2; i += 3)
	{
		glm::vec3 norm = VisualObject::FindVectorNormal(mVertices[i], mVertices[i + 1], mVertices[i + 2]);
		mVertices[i].normal = norm;
		mVertices[i + 1].normal = norm;
		mVertices[i + 2].normal = norm;
	}

}

void Light::UseLight(GLuint LightIntensityLocation, GLfloat LightColorLocation)
{
	glUniform3f(LightColorLocation, color[0], color[1], color[2]);
	glUniform1f(LightIntensityLocation, ambientIntensity);
}

void Light::UseLight(GLuint LightIntensityLocation, GLfloat LightColorLocation, GLfloat DiffuseIntensityLocation, GLint LightPositionLocation)
{
	glUniform3f(LightColorLocation, color[0], color[1], color[2]);
	glUniform1f(LightIntensityLocation, ambientIntensity);
	glUniform1f(DiffuseIntensityLocation, diffuseIntensity);

	glUniform3f(LightPositionLocation, lightPos[0], lightPos[1], lightPos[2]);
}

void Light::SetLightPosition(glm::vec3 newPos)
{
	position = newPos;
	lightPos = newPos;
	mMatrix = glm::mat4(1.0f);
	mMatrix = glm::translate(mMatrix, position);
}

void Light::init(glm::mat4 matrixUniform)
{
	mMatrix = matrixUniform;

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mIndices.size(), mIndices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertices.size(), mVertices.data(), GL_STATIC_DRAW);

	// XYZ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	// RGB
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Light::draw()
{
	RenderIndex = ShaderRef->fillType;
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	ShaderRef->SetMat4("mMatrix", mMatrix);

	switch (FillType(RenderIndex))
	{
	case FULL:
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		break;
	case WIREFRAME:
		glDrawElements(GL_LINES, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		break;
	case POINTS:
		glDrawElements(GL_POINTS, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		break;
	default:
		std::cout << "ERROR - INVALID RENDER STYLE ON OBJECT TYPE: Player" << std::endl;
		std::cout << "      - Render style: " << RenderIndex << std::endl;
		break;
	}
}
