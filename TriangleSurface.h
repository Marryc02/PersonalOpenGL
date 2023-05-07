#pragma once

#include "VisualObject.h"

class TriangleSurface : public VisualObject
{
public:

	TriangleSurface();
	void init(glm::mat4 matrixUniform) override;
	void draw() override;

};

