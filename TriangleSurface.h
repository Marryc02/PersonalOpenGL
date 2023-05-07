#pragma once

#include "VisualObject.h"

class Shader;

class TriangleSurface : public VisualObject
{
public:

	TriangleSurface(Shader* shaderRef);
	void init(glm::mat4 matrixUniform) override;
	void draw() override;
private:
	Shader* ShaderRef;
};

