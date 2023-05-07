#include "TriangleSurface.h"

TriangleSurface::TriangleSurface()
{	
	//							  X     Y    Z    R    G    B    U    V
	mVertices.push_back(Vertex{  0.5, -0.5, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 });
	mVertices.push_back(Vertex{ -0.5, -0.5, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0 });
	mVertices.push_back(Vertex{  0.0,  0.5, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0 });

	mIndices.push_back(0);
	mIndices.push_back(1);
	mIndices.push_back(2);
}

void TriangleSurface::init(glm::mat4 matrixUniform)
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

	// UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void TriangleSurface::draw()
{
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
