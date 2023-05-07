#pragma once

#include <vector>
#include <glm/glm.hpp>

class Curve;

class CurveMovementComponent
{
public:

	void GetCurveVertex(Curve* curveToFollow);

protected:
	std::vector<glm::vec3> vPositions;
};

