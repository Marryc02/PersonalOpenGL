#pragma once

//#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Enums.h"

class PositionComponent {
public:
	// Keyboard

	glm::vec3 position;
	glm::vec3 right;	// local x
	glm::vec3 up;		// local y 
	glm::vec3 front;	// local z
	const glm::vec3 worldRight = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 worldFront = glm::vec3(0.0f, 0.0f, 1.0f);

	float yaw;
	float pitch;
	float roll;

	float LowestY{};

	glm::vec3 rotation;
	glm::vec3 scale;

	// Should these be protected?
	glm::mat4 mMatrix{}; // position i guess
	//glm::mat4 rotation = glm::mat4(1.0f);

	PositionComponent();

	// Realtime movement
	void translateLocal(Movement direction);
	void translateLocal(glm::vec3 offset, float deltaTime);
	void translate(Movement direction, float deltaTime);
	void translate(float inX, float inY, float inZ, float deltaTime);

	// Set position
	void setPosition(glm::vec3 offset);
	void setPosition(float x, float y, float z);
	//void setX(float x);
	void setY(float y);

	// set rotation
	void setRotation(float angle, glm::vec3 axis);

	// set scale
	void setScale(glm::vec3 scaleIncrease);

	float moveSpeed{};
	bool useLocal{ true };

	// Gets
	glm::mat4 getTranslateMatrix() {
		/*	matrix = glm::mat4(1.0f);
			matrix = glm::translate(matrix, position);
			matrix = glm::scale(matrix, scale);
			return matrix;*/
		return glm::lookAt(position, position + worldFront, worldUp);
	}

	void setPositionMatrix(glm::vec3 position) {
		mMatrix = glm::mat4(1.0f);
		mMatrix = glm::translate(mMatrix, position);
	}

	void updateWorldVectors() {

		//worldRight = glm::normalize
	}

	void updateLocalVectors() {
		glm::vec3 newFront;

		newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		newFront.y = sin(glm::radians(pitch));
		newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

		front = glm::normalize(newFront);

		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));
	}

protected:

	//glm::mat4 matrix;
	//glm::mat4 position;
	//glm::mat4 rotation;
};