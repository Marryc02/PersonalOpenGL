#include "Vertex.h"

Vertex::Vertex()
{
	pos = glm::vec3(0.0f, 0.0f, 0.0f);
	rgb = glm::vec3(1.0f, 1.0f, 1.0f);
	normal = glm::vec3(0.0f, 0.0f, 0.0f);
	st = glm::vec2(0.0f, 0.0f);
}

Vertex::Vertex(float x, float y, float z, float r, float g, float b, float s, float t)
{
	pos = glm::vec3(x, y, z);
	rgb = glm::vec3(r, g, b);
	st = glm::vec2(s, t);
	normal = glm::vec3(0.0f);
}

Vertex::Vertex(float x, float y, float z, float r, float g, float b)
{
	pos = glm::vec3(x, y, z);
	rgb = glm::vec3(r, g, b);
	st = glm::vec2(0.0f, 1.0f);
	normal = glm::vec3(0.0f);
}

Vertex::Vertex(float x, float y, float z, float s, float t)
{
	pos = glm::vec3(x, y, z);
	rgb = glm::vec3(1.0f, 1.0f, 1.0f);
	st = glm::vec2(s, t);
	normal = glm::vec3(0.0f);
}

void Vertex::AddNormal(glm::vec3 newNormal)
{
	ConnectedNormals.push_back(newNormal);
	normal = glm::vec3(0.0f);

	for (int i = 0; i < ConnectedNormals.size(); i++)
	{
		normal += ConnectedNormals[i];
	}

	normal /= TotalTriangles;
}
