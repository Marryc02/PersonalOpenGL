#include "Cube.h"
#include "Curve.h"
#include <iostream>
Cube::Cube()
{

}

Cube::Cube(Shader* shaderRef)
{
	ShaderRef = shaderRef;
	ReadFile("Shapes/CubeVertices.txt", mVertices);
	ReadFileIndices("Shapes/CubeIndices.txt", mIndices);

	for (int i = 0; i < mIndices.size(); i += 3)
	{
		glm::vec3 norm = VisualObject::FindVectorNormal(mVertices[mIndices[i]], mVertices[mIndices[i + 1]], mVertices[mIndices[i + 2]]);
		mVertices[mIndices[i]].normal += glm::normalize(norm);
		mVertices[mIndices[i + 1]].normal += glm::normalize(norm);
		mVertices[mIndices[i + 2]].normal += glm::normalize(norm);
	}
}

Cube::Cube(Curve* curveToFollow, Shader* shaderRef)
{
	ShaderRef = shaderRef;
	ReadFile("Shapes/CubeVertices.txt", mVertices);
	ReadFileIndices("Shapes/CubeIndices.txt", mIndices);

	for (int i = 0; i < mIndices.size(); i += 3)
	{
		glm::vec3 norm = VisualObject::FindVectorNormal(mVertices[mIndices[i]], mVertices[mIndices[i + 1]], mVertices[mIndices[i + 2]]);
		mVertices[mIndices[i]].normal += glm::normalize(norm);
		mVertices[mIndices[i + 1]].normal += glm::normalize(norm);
		mVertices[mIndices[i + 2]].normal += glm::normalize(norm);
	}

	GetCurveVertex(curveToFollow);
	VertAmount = vPositions.size();
}

Cube::~Cube()
{

}

void Cube::FollowCurve(float deltaTime)
{

	glm::vec3 trans;

	if (NodeIndex < VertAmount && GoingBack)
	{
		glm::vec3 temp = vPositions[NodeIndex];

		trans = temp - position;

		

		translate(trans[0], trans[1], trans[2], deltaTime);

		if (position == vPositions[NodeIndex]);
		{
			NodeIndex++;
		}

		if (NodeIndex >= VertAmount - 1)
		{
			GoingBack = false;
		}
	}
	else if (NodeIndex >= 0 && !GoingBack)
	{
		glm::vec3 temp = vPositions[NodeIndex];

		trans = temp - position;
		

		translate(trans[0], trans[1], trans[2], deltaTime);

		if (position == vPositions[NodeIndex]);
		{
			NodeIndex--;
		}
		if (NodeIndex <= 0)
		{
			NodeIndex = 0;
			GoingBack = true;
		}
	}
}

void Cube::init(glm::mat4 matrixUniform)
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

	// NORMALS
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Cube::draw()
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
		std::cout << "ERROR - INVALID RENDER STYLE ON OBJECT TYPE: Cube" << std::endl;
		std::cout << "      - Render style: " << RenderIndex << std::endl;
		break;
	}
}
