#pragma once

#include "../VisualObject.h"
#include "../FileLoader.h"
#include "../CollisionComponent.h"

class Shader;

class Pickup : public VisualObject, public FileLoader, public CollisionComponent
{
public:
	Pickup();
	Pickup(Shader* shaderRef);

	void init(glm::mat4 matrixUniform) override;
	void draw() override;

protected:
	Shader* ShaderRef;
};

