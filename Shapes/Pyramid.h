#pragma once

#include "../VisualObject.h"

class Shader;

class Pyramid : public VisualObject
{
public:
	Pyramid();
	Pyramid(Shader* shaderRef);
	~Pyramid();

	void init(glm::mat4 matrixUniform) override;
	void draw() override;

private:
	Shader* ShaderRef;
};

