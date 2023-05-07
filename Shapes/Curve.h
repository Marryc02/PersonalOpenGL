#pragma once

#include "../VisualObject.h"
#include "../FileLoader.h"

class Curve : public VisualObject, public FileLoader
{
public:
	Curve();
	Curve(Shader* shader, std::string filepath);

	glm::vec3 GetVertexPosition(int index);
	int GetCurveVerticesSize();

	virtual void init(glm::mat4 matrixUniform) override;
	virtual void draw() override;

	Shader* ShaderRef;

	std::string FilePath;
};

