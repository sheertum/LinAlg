#pragma once

#include "Vector.h"

class Camera {
public:
	void pointAt(const Vector& position, const Vector& target, const Vector& up);
};