#include "Pyramid.h"

Pyramid::Pyramid()
{

}

Pyramid::Pyramid(Shader* shaderRef)
{
	ShaderRef = shaderRef;
	// Front face
	mVertices.push_back(Vertex{ -0.5, -0.5,  0.5, 1.0, 0.0, 1.0, 0.20, 0.15 }); // Bottom left   0
	mVertices.push_back(Vertex{  0.5, -0.5,  0.5, 1.0, 0.0, 1.0, 0.80, 0.15 }); // Bottom right  1
	mVertices.push_back(Vertex{  0.0,  0.5,  0.0, 0.0, 0.0, 1.0, 0.50, 1.00 }); // Top			 2

	// Right face
	mVertices.push_back(Vertex{  0.5, -0.5, -0.5, 0.7, 1.0, 1.0, 0.00, 0.00 }); // Bottom right  3

	// Back face
	mVertices.push_back(Vertex{ -0.5, -0.5, -0.5, 0.0, 1.0, 0.5, 0.00, 0.00 }); // Bottom right	 4

	// Left face
	// Uses vertices of other faces to construct itself

	// Bottom square
	// Uses vertices of other faces to construct itself

	mIndices = {
		0, 1, 2, // Front side
		1, 3, 2, // Right side
		3, 4, 2, // Back side
		4, 0, 2, // Left side
		0, 1, 4, // Front bottom triangle
		1, 3, 4  // Back bottom triangle
	};

	mMatrix = glm::mat4(1.0f);
}

Pyramid::~Pyramid()
{

}

void Pyramid::init(glm::mat4 matrixUniform)
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

void Pyramid::draw()
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
		std::cout << "ERROR - INVALID RENDER STYLE ON OBJECT TYPE: Player" << std::endl;
		std::cout << "      - Render style: " << RenderIndex << std::endl;
		break;
	}
}
