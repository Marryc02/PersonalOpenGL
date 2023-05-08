#pragma once

#include "../VisualObject.h"
#include "../FileLoader.h"
#include "../CollisionComponent.h"


class Shader;

class LightSwitch : public VisualObject, public FileLoader, public CollisionComponent
{
public:
	LightSwitch();
	LightSwitch(Shader* shaderRef);
	~LightSwitch();


	void init(glm::mat4 matrixUniform) override;
	void draw() override;

private:
	Shader* ShaderRef;
};