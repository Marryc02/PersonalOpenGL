#pragma once

#include "../VisualObject.h"
#include "../FileLoader.h"

class Shader;

class Circle : public VisualObject, public FileLoader
{
public:
	Circle();
	Circle(Shader* shaderRef);

	void init(glm::mat4 matrixUniform) override;
	void draw() override;

private:
	Shader* ShaderRef;
};

