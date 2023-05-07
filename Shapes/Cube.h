#pragma once

#include "../VisualObject.h"
#include "../FileLoader.h"
#include "../CurveMovementComponent.h"
#include "../CollisionComponent.h"

class Curve;
class Shader;

class Cube : public VisualObject, public FileLoader, public CurveMovementComponent, public CollisionComponent
{
public:
	Cube();
	Cube(Shader* shaderRef);
	Cube(Curve* curveToFollow, Shader* shaderRef);
	~Cube();


	void FollowCurve(float deltaTime);

	void init(glm::mat4 matrixUniform) override;
	void draw() override;

private:
	int NodeIndex, VertAmount;
	bool GoingBack = false;
	Shader* ShaderRef;
};

