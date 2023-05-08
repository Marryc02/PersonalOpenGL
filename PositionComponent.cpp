#include "positionComponent.h"

PositionComponent::PositionComponent() {

	mMatrix = glm::mat4(1.0f);
	mMatrix = glm::translate(mMatrix, glm::vec3(0.0f));
	mMatrix = glm::rotate(mMatrix, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	mMatrix = glm::scale(mMatrix, glm::vec3(1.0f));

	updateWorldVectors();
	updateLocalVectors();
}

void PositionComponent::translateLocal(Movement direction) {

	// X
	if (direction == RIGHT) {
		//position = glm::translate(position, right * moveSpeed);
		position += right;
		//matrix = glm::translate(matrix, position);
	}
	if (direction == LEFT) {
		//position = glm::translate(position, -right * moveSpeed);
		position -= right;
		//matrix = glm::translate(matrix, position);
	}
	// Y
	if (direction == UPWARD) {
		//position = glm::translate(position, up * moveSpeed);
		position += up;
		//matrix = glm::translate(matrix, position);
	}
	if (direction == DOWNWARD) {
		//position = glm::translate(position, -up * moveSpeed);
		position -= up;
		//matrix = glm::translate(matrix, position);
	}
	// Z
	if (direction == FORWARD) {
		//position = glm::translate(position, front * moveSpeed);
		position += front;
		//matrix = glm::translate(matrix, position);
	}
	if (direction == BACKWARD) {
		//position = glm::translate(position, -front * moveSpeed);
		position -= front;
		//matrix = glm::translate(matrix, position);
	}
}

void PositionComponent::translateLocal(glm::vec3 offset, float deltaTime) {
	//position = glm::translate(position, offset);
}

void PositionComponent::translate(Movement direction, float deltaTime) {
	// X
	if (direction == RIGHT) {
		//position = glm::translate(position, right * moveSpeed);
		position += worldRight * deltaTime;
		//matrix = glm::translate(matrix, position);
	}
	if (direction == LEFT) {
		//position = glm::translate(position, -right * moveSpeed);
		position -= worldRight * deltaTime;
		//matrix = glm::translate(matrix, position);
	}
	// Y
	if (direction == UPWARD) {
		//position = glm::translate(position, up * moveSpeed);
		position -= worldUp * deltaTime;
		//matrix = glm::translate(matrix, position);
	}
	if (direction == DOWNWARD) {
		//position = glm::translate(position, -up * moveSpeed);
		position += worldUp * deltaTime;
		//matrix = glm::translate(matrix, position);
	}
	// Z
	if (direction == FORWARD) {
		//position = glm::translate(position, front * moveSpeed);
		position += worldFront * deltaTime;
		//matrix = glm::translate(matrix, position);
	}
	if (direction == BACKWARD) {
		//position = glm::translate(position, -front * moveSpeed);
		position -= worldFront * deltaTime;
	}
	setPositionMatrix(position);
}

void PositionComponent::translate(float inX, float inY, float inZ, float deltaTime) {
	position += glm::vec3(inX, inY, inZ);
	setPositionMatrix(position);
}

void PositionComponent::setPosition(glm::vec3 offset) {
	position = offset;
	setPositionMatrix(position);
}

void PositionComponent::setPosition(float x, float y, float z) {
	position = glm::vec3(x, y, z);
	setPositionMatrix(position);
}

void PositionComponent::setRotation(float angle, glm::vec3 axis)
{
	glm::vec3 PreviousPos = position;

	mMatrix = glm::mat4(1.0f);
	mMatrix = glm::translate(mMatrix, PreviousPos);

	mMatrix = glm::rotate(mMatrix, glm::radians(angle), axis);
	mMatrix = glm::translate(mMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
}

void PositionComponent::setScale(glm::vec3 scaleIncrease)
{
	mMatrix = glm::scale(mMatrix, glm::vec3(scaleIncrease));
}

void PositionComponent::setY(float y) {
	position.y = y;
	setPositionMatrix(position);
}