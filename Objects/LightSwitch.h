#pragma once

#include "../VisualObject.h"
#include "../FileLoader.h"
#include "../CollisionComponent.h"
#include <GLFW/glfw3.h>


class Shader;

class LightSwitch : public VisualObject, public FileLoader, public CollisionComponent
{
public:
	LightSwitch();
	LightSwitch(Shader* shaderRef);
	~LightSwitch();

	void lightSwitchResetCounter();

	void init(glm::mat4 matrixUniform) override;
	void draw() override;

	bool bSwitchHasBeenFlipped = false;
	bool bCanFlipSwitchAgain = true;
	float switchCounter;

private:
	Shader* ShaderRef;
};