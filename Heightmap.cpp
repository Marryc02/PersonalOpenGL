#include "Heightmap.h"
#include "stb_image.h"

#include <iostream>

Heightmap::Heightmap()
{

}

Heightmap::Heightmap(Shader* shaderRef, const char* filePath)
{
	unsigned char* ImageData = stbi_load(filePath, &width, &height, &bitDepth, 1);

	ShaderRef = shaderRef;

	if (!ImageData)
	{
		std::cout << "NO HEIGHTMAP IMAGE FOUND" << std::endl;
		return;
	}

	int resolution = 48;
	int size = 48;

	float h = size / resolution; // Step size
	float hSize = size / 2;

	float yOffset = -16.0f;

	// Calculating indices
	for (int x = 0; x < resolution - 1; x++)
	{
		for (int z = 0; z < resolution - 1; z++)
		{
			int BottomLeftIndex = x + z * resolution;
			int BottomRightIndex = (x + 1) + z * resolution;
			int TopLeftIndex = x + (z + 1) * resolution;
			int TopRightIndex = (x + 1) + (z + 1) * resolution;

			mIndices.push_back(BottomLeftIndex);
			mIndices.push_back(BottomRightIndex);
			mIndices.push_back(TopLeftIndex);

			mIndices.push_back(TopLeftIndex);
			mIndices.push_back(BottomRightIndex);
			mIndices.push_back(TopRightIndex);
		}
	}

	float zp = 0.0f;
	float xp = 0.0f;
	const int shortestSide = std::min(width, height);
	const float pixelJump = (float)shortestSide / (float)resolution;
	int maxHeight = 35;


	// Calculating vertices
	for (int x = 0; x < resolution; x++)
	{
		for (int z = 0; z < resolution; z++)
		{
			glm::vec3 color = glm::vec3(0.0f, z / 128, 1.0f - z / 255);
			int index = ((int)(zp / height * (resolution - 1))) * width + (int)(xp / width * (resolution - 1));
			float height = ImageData[index * 1] / 255.f * maxHeight + yOffset;

			Vertex vertex(x * h - hSize, height, z * h - hSize, color[0], color[1], color[2], x / (float)resolution, z / (float)resolution);
			mVertices.push_back(vertex);

			zp += pixelJump;
		}

		xp += pixelJump;
		zp = 0.0f;
	}


	// Finding normals
	for (int i = 0; i < mIndices.size(); i += 3)
	{
		glm::vec3 v1 = mVertices[mIndices[i + 1]].pos - mVertices[mIndices[i]].pos;
		glm::vec3 v2 = mVertices[mIndices[i + 2]].pos - mVertices[mIndices[i]].pos;
		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		mVertices[mIndices[i]].normal += normal;
		mVertices[mIndices[i + 1]].normal += normal;
		mVertices[mIndices[i + 2]].normal += normal;
	}

	for (int i = 0; i < mVertices.size(); i++)
	{
		mVertices[i].normal = glm::normalize(mVertices[i].normal);
	}

	stbi_image_free(ImageData);
}

float Heightmap::HeightFromBaryc(const glm::vec2& playerPos)
{
	glm::vec3 v0, v1, v2;
	glm::vec3 baryc{ -1, -1, -1 };

	for (int i = 0; i < mIndices.size() / 3; i++)
	{

		int i1, i2, i3;
		i1 = mIndices[i * 3];
		i2 = mIndices[i * 3 + 1];
		i3 = mIndices[i * 3 + 2];

		v0 = { mVertices[i1].pos };
		v1 = { mVertices[i2].pos };
		v2 = { mVertices[i3].pos };

		baryc = CalcBarycentricCoords(glm::vec2(v0[0], v0[2]), glm::vec2(v1[0], v1[2]), glm::vec2(v2[0], v2[2]), playerPos);

		if (baryc[0] >= 0 && baryc[1] >= 0 && baryc[2] >= 0)
		{
			//std::cout << "Found at triangle number: " + std::to_string(i / 3) << std::endl;
			break;
		}
	}

	float height = v0[1] * baryc[0] + v1[1] * baryc[1] + v2[1] * baryc[2];
	
	return height;
}

glm::vec3 Heightmap::CalcBarycentricCoords(const glm::vec2& v0, const glm::vec2& v1, const glm::vec2& v2, const glm::vec2& playerPos)
{
	glm::vec2 v10 = v1 - v0;
	glm::vec2 v21 = v2 - v1;

	float area = glm::cross(glm::vec3(v10, 0.f), glm::vec3(v21, 0.0f))[2];


	glm::vec2 v0p = v0 - playerPos;
	glm::vec2 v1p = v1 - playerPos;
	glm::vec2 v2p = v2 - playerPos;

	float u = glm::cross(glm::vec3(v0p, 0.0f), glm::vec3(v1p, 0.0f))[2] / area;
	float v = glm::cross(glm::vec3(v1p, 0.0f), glm::vec3(v2p, 0.0f))[2] / area;
	float w = glm::cross(glm::vec3(v2p, 0.0f), glm::vec3(v0p, 0.0f))[2] / area;

	glm::vec3 tempBaryc = { u, v, w };

	return tempBaryc;
}

void Heightmap::init(glm::mat4 matrixUniform)
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

void Heightmap::draw()
{
	RenderIndex = ShaderRef->fillType;
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);

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
		std::cout << "ERROR - INVALID RENDER STYLE ON OBJECT TYPE: Heightmap" << std::endl;
		std::cout << "      - Render style: " << RenderIndex << std::endl;
		break;
	}
}