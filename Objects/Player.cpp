#include "Player.h"
#include "../Objects/Pickup.h"
#include <iostream>


Player::Player()
{
	ReadFile("Shapes/CubeVertices.txt", mVertices);
	ReadFileIndices("Shapes/CubeIndices.txt", mIndices);

	for (int i = 0; i <= mVertices.size() - 2; i += 3)
	{
		glm::vec3 norm = VisualObject::FindVectorNormal(mVertices[i], mVertices[i + 1], mVertices[i + 2]);
		mVertices[i].normal = norm;
		mVertices[i + 1].normal = norm;
		mVertices[i + 2].normal = norm;
	}

	LowestY = FindLowestY();
}

Player::Player(Shader* shaderRef)
{
	ShaderRef = shaderRef;
	ReadFile("Shapes/CubeVertices.txt", mVertices);
	ReadFileIndices("Shapes/CubeIndices.txt", mIndices);

	for (int i = 0; i <= mVertices.size() - 2; i += 3)
	{
		glm::vec3 norm = VisualObject::FindVectorNormal(mVertices[i], mVertices[i + 1], mVertices[i + 2]);
		mVertices[i].normal = norm;
		mVertices[i + 1].normal = norm;
		mVertices[i + 2].normal = norm;
	}

	LowestY = FindLowestY();

}

void Player::init(glm::mat4 matrixUniform)
{
	mMatrix = matrixUniform;

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);

	glGenBuffers(1, &mEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mIndices.size(), mIndices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertices.size(), mVertices.data(), GL_STATIC_DRAW);

	// XYZ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	// RGB
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	// UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 6));
	glEnableVertexAttribArray(2);

	// NORMALS
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float) * 8));
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Player::draw()
{
	RenderIndex = ShaderRef->fillType;
	glBindVertexArray(mVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	ShaderRef->SetMat4("mMatrix", mMatrix);

	switch (FillType(RenderIndex))
	{
	case FULL:
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		break;
	case WIREFRAME:
		glDrawElements(GL_LINES, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		break;
	case POINTS:
		glDrawElements(GL_POINTS, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		break;
	default:
		std::cout << "ERROR - INVALID RENDER STYLE ON OBJECT TYPE: Player" << std::endl;
		std::cout << "      - Render style: " << RenderIndex << std::endl;
		break;
	}
}

void Player::OnCollision(VisualObject* other)
{
	if (dynamic_cast<Pickup*>(other))
	{
		std::cout << "Player has collided!" << std::endl;
		RemoveCollisionTarget(other);
	}
}

bool Player::CheckCollision(VisualObject* other)
{
	//std::cout << "player's collision checks: " << CollisionChecks.size() << std::endl;
	for (int i = 0; i < CollisionChecks.size(); i++)
	{
		float dist = FindDistance(this->position, other->position);
		if (dist < (this->HitRadius + other->HitRadius))
		{
			OnCollision(other);
			return true;
		}
	}
	return false;
}

void Player::SetCollisionTarget(VisualObject* other)
{
	CollisionChecks.push_back(other);
}

void Player::RemoveCollisionTarget(VisualObject* target)
{
	for (int i = 0; i < CollisionChecks.size(); i++)
	{
		if (CollisionChecks[i] == target)
		{
			// Switches the element the player has collided with with the element in the back of the "CollisionChecks"-vector
			std::swap(CollisionChecks[i], CollisionChecks[CollisionChecks.size() - 1]);
			// Removes the element in the back of the "CollisionChecks"-vector
			CollisionChecks.pop_back();
			
			target->WillBeDeleted = true;
		}
	}
}

void Player::ProcessKeyboard(Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD) 
	{
		position[2] -= velocity;
	}
	if (direction == BACKWARD)
	{
		position[2] += velocity;
	}
	if (direction == LEFT)
	{
		position[0] -= velocity;
	}
	if (direction == RIGHT)
	{
		position[0] += velocity;
	}

	mMatrix = glm::mat4(1.0f);
	glm::translate(mMatrix, position);
}
