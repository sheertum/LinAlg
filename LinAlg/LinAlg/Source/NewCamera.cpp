#include "NewCamera.h"

void Camera::pointAt(const Vector& position, const Vector& target, const Vector& up)
{
	Vector newForward = target - position;
	newForward.normalise();

	Vector a = newForward * (up.toMatrix())
}
