#include "Circle.h"

Circle::Circle()
{

}

Circle::Circle(Shader* shaderRef)
{
	ShaderRef = shaderRef;
	ReadFile("Shapes/CircleVertices.txt", mVertices);
	ReadFileIndices("Shapes/CircleIndices.txt", mIndices);

	// CODE USED TO CALCULATE CIRCLE VERTICES AND INDICES

	//mVertices.push_back(Vertex{ 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f });
	//for (unsigned int i = 0; i < 14; i++)
	//{
	//	double angle = 30 * i * 3.14 / 180;
	//	float x = cos(angle);
	//	float y = sin(angle);

	//	mVertices.push_back(Vertex{ x, y, 0.0f, 1.0f, 1.0f, 1.0f });
	//}

	//for (unsigned int i = 0; i < 15; i++)
	//{
	//	mIndices.push_back(i);
	//}
	//WriteFile("Shapes/CircleVertices.txt", mVertices);
	//WriteFileIndices("Shapes/CircleIndices.txt", mIndices);
}

void Circle::init(glm::mat4 matrixUniform)
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

void Circle::draw()
{
	//glBindVertexArray(mVAO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	//glDrawElements(GL_TRIANGLE_FAN, mIndices.size(), GL_UNSIGNED_INT, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	RenderIndex = ShaderRef->fillType;
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	ShaderRef->SetMat4("mMatrix", mMatrix);

	switch (FillType(RenderIndex))
	{
	case FULL:
		glDrawElements(GL_TRIANGLE_FAN, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		break;
	case WIREFRAME:
		glDrawElements(GL_LINE_STRIP, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		break;
	case POINTS:
		glDrawElements(GL_POINTS, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		break;
	default:
		std::cout << "ERROR - INVALID RENDER STYLE ON OBJECT TYPE: Circle" << std::endl;
		std::cout << "      - Render style: " << RenderIndex << std::endl;
		break;
	}
}

