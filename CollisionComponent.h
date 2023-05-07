#pragma once

#include <vector>
#include <glm/glm.hpp>

class VisualObject;

class CollisionComponent
{
public:
	virtual void OnCollision(VisualObject* other);
	virtual bool CheckCollision(VisualObject* other);
	virtual void SetCollisionTarget(VisualObject* other);
	virtual void RemoveCollisionTarget(VisualObject* target);

	float FindDistance(glm::vec3 origin, glm::vec3 destination);
};
