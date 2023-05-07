#include "CurveMovementComponent.h"
#include "Shapes/Curve.h"


void CurveMovementComponent::GetCurveVertex(Curve* curveToFollow)
{
	for (int i = 0; i < curveToFollow->GetCurveVerticesSize() - 1; i++)
	{
		vPositions.push_back(curveToFollow->GetVertexPosition(i));
	}
}
