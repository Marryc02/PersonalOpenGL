#pragma once

#include <vector>
#include "Vertex.h"
#include "PositionComponent.h"
#include <fstream>
#include "shaderClass.h"
#include "Enums.h"
#include <iostream>

class VisualObject : public PositionComponent
{
public:
	VisualObject();
	~VisualObject();

	virtual void init(glm::mat4 matrixUniform) = 0;
	virtual void draw() = 0;

	std::vector<Vertex> mVertices;
	std::vector<unsigned int> mIndices;

	float HitRadius = 1.0f;
	bool WillBeDeleted = false;

	glm::vec3 FindVectorNormal(Vertex p1, Vertex p2, Vertex p3)
	{
		glm::vec3 p12 = p2.pos - p1.pos;
		glm::vec3 p13 = p3.pos - p1.pos;
		glm::vec3 n = glm::cross(p12, p13);

		return n;
	}

	float FindLowestY();

protected:
	unsigned int mVAO{ 0 };
	unsigned int mVBO{ 0 };
	unsigned int mEBO{ 0 };

	FillType RenderIndex;

};