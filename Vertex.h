#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

class Vertex
{
public:

	Vertex();
	Vertex(float x, float y, float z, float r, float g, float b, float s, float t);
	Vertex(float x, float y, float z, float r, float g, float b);
	Vertex(float x, float y, float z, float s, float t);

	glm::vec3 pos;
	glm::vec3 rgb;
	glm::vec2 st;
	glm::vec3 normal;

	int TotalTriangles{ 1 };
	
	std::vector<glm::vec3> ConnectedNormals;

	void AddNormal(glm::vec3 newNormal);

};

