#pragma once

#include "VisualObject.h"
#include "shaderClass.h"

class Shader;

class Heightmap : public VisualObject
{
public:
	Heightmap();
	Heightmap(Shader* shaderRef, const char* filePath);

	void init(glm::mat4 matrixUniform) override;
	void draw() override;

	float HeightFromBaryc(const glm::vec2& playerPos);
	glm::vec3 CalcBarycentricCoords(const glm::vec2& v0, const glm::vec2& v1,
			const glm::vec2& v2, const glm::vec2& playerPos);

private:
	GLuint texID;
	int width, height, bitDepth;

	Shader* ShaderRef;
};

