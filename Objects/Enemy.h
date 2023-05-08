#pragma once

#include "../VisualObject.h"
#include "../FileLoader.h"
#include "../CollisionComponent.h"

class Shader;

class Enemy : public VisualObject, public FileLoader, public CollisionComponent
{
public:
    Enemy();
    Enemy(Shader* shaderRef);

    void init(glm::mat4 matrixUniform) override;
    void draw() override;

    void OnCollision(VisualObject* other) override;
    bool CheckCollision(VisualObject* other) override;
    void SetCollisionTarget(VisualObject* other) override;
    void RemoveCollisionTarget(VisualObject* target) override;

    std::vector<VisualObject*> CollisionChecks;

    bool WillResetGame = false;

private:
    Shader* ShaderRef;
};
