#pragma once

#include "../VisualObject.h"
#include "../FileLoader.h"

class Shader;

class Sphere : public VisualObject, public FileLoader
{
public:
	Sphere();
	Sphere(Shader* shaderRef, int n = 0);
	void CreateSphere(int n = 0);

	void init(glm::mat4 matrixUniform) override;
	void draw() override;

private:
	int recursions;
	int indices;
	
	void MakeTriangle(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3);
	void Subdivide(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, int n);
	void SphereUnitBall();

	Shader* ShaderRef;
};

