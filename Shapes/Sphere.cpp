#include "Sphere.h"

Sphere::Sphere()
{

}

Sphere::Sphere(Shader* shaderRef, int n)
{
	ShaderRef = shaderRef;
	CreateSphere(n);
}

void Sphere::CreateSphere(int n) /* : recursions(n), indices(0), VisualObject() */
{
	recursions = n;
	indices = 0;
	mVertices.reserve(3 * 8 * pow(4, recursions));
	SphereUnitBall();
}

void Sphere::init(glm::mat4 matrixUniform)
{
	mMatrix = matrixUniform;

	//Vertex Array Object - VAO
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	//Vertex Buffer Object to hold vertices - VBO
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);

	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), mVertices.data(), GL_STATIC_DRAW);

	// 1rst attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// 2nd attribute buffer : colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	glBindVertexArray(0);
}

void Sphere::draw()
{
	glBindVertexArray(mVAO);
	ShaderRef->SetMat4("mMatrix", mMatrix);

	RenderIndex = ShaderRef->fillType;

	switch (FillType(RenderIndex))
	{
	case FULL:
		glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
		break;
	case WIREFRAME:
		glDrawArrays(GL_LINES, 0, mVertices.size());
		break;
	case POINTS:
		glDrawArrays(GL_POINT, 0, mVertices.size());
		break;
	default:
		std::cout << "ERROR - INVALID RENDER STYLE ON OBJECT TYPE: Sphere" << std::endl;
		std::cout << "      - Render style: " << RenderIndex << std::endl;
		break;
	}
}


void Sphere::MakeTriangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3)
{
	Vertex v{ v1.x, v1.y, v1.z, v1.x, v1.y, v1.z };
	mVertices.push_back(v);
	v = Vertex{ v2.x, v2.y, v2.z, v2.x, v2.y, v2.z };
	mVertices.push_back(v);
	v = Vertex{ v3.x, v3.y, v3.z, v3.x, v3.y, v3.z };
	mVertices.push_back(v);
}

void Sphere::Subdivide(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, int n)
{
	if (n > 0)
	{
		glm::vec3 v1 = glm::normalize(a + b);
		glm::vec3 v2 = glm::normalize(a + c);
		glm::vec3 v3 = glm::normalize(c + b);

		Subdivide(a, v1, v2, n - 1);
		Subdivide(c, v2, v3, n - 1);
		Subdivide(b, v3, v1, n - 1);
		Subdivide(v3, v2, v1, n - 1);
	}
	else
	{
		MakeTriangle(a, b, c);
	}
}

void Sphere::SphereUnitBall()
{
	glm::vec3 v0{ glm::vec3(0.0f,  0.0f,  1.0f) };
	glm::vec3 v1{ glm::vec3(1.0f,  0.0f,  0.0f) };
	glm::vec3 v2{ glm::vec3(0.0f,  1.0f,  0.0f) };
	glm::vec3 v3{ glm::vec3(-1.0f,  0.0f,  0.0f)};
	glm::vec3 v4{ glm::vec3(0.0f, -1.0f,  0.0f) };
	glm::vec3 v5{ glm::vec3(0.0f,  0.0f, -1.0f) };

	Subdivide(v0, v1, v2, recursions);
	Subdivide(v0, v2, v3, recursions);
	Subdivide(v0, v3, v4, recursions);
	Subdivide(v0, v4, v1, recursions);
	Subdivide(v5, v2, v1, recursions);
	Subdivide(v5, v3, v2, recursions);
	Subdivide(v5, v4, v3, recursions);
	Subdivide(v5, v1, v4, recursions);
}


