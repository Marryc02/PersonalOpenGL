#pragma once

#include "../VisualObject.h"
#include "../FileLoader.h"
#include "../Enums.h"
#include "../CollisionComponent.h"

class Shader;

class Player : public VisualObject, public FileLoader, public CollisionComponent
{
public:
	Player();
	Player(Shader* shaderRef);

	void init(glm::mat4 matrixUniform) override;
	void draw() override;

	void OnCollision(VisualObject* other) override;
	bool CheckCollision(VisualObject* other) override;
	void SetCollisionTarget(VisualObject* other) override;
	void RemoveCollisionTarget(VisualObject* target) override;

	void ProcessKeyboard(Movement direction, float deltaTime);
	std::vector<VisualObject*> CollisionChecks;

	float pointsCollected = 0;

private:
	float MovementSpeed = 5.0f;
	Shader* ShaderRef;
};

