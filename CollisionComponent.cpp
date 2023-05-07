#include "CollisionComponent.h"

void CollisionComponent::OnCollision(VisualObject* other)
{

}

bool CollisionComponent::CheckCollision(VisualObject* other)
{
	return true;
}

void CollisionComponent::SetCollisionTarget(VisualObject* other)
{

}

void CollisionComponent::RemoveCollisionTarget(VisualObject* target)
{
}

float CollisionComponent::FindDistance(glm::vec3 origin, glm::vec3 destination)
{
	float dist = sqrt(pow(destination[0] - origin[0], 2) +
					  pow(destination[1] - origin[1], 2) +
					  pow(destination[2] - origin[2], 2));
	return dist;
}
