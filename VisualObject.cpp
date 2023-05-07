#include "VisualObject.h"
#include <iostream>

VisualObject::VisualObject()
{
}

VisualObject::~VisualObject()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mEBO);
}

// Finds the vertex with the lowest Y-Value
float VisualObject::FindLowestY()
{
	int index = 0;
	for (int i = 0; i < mVertices.size(); i++)
	{
		if (mVertices[index].pos[1] < mVertices[i].pos[1])
		{
			index = i;
		}
	}
	return mVertices[index].pos[1];
}
