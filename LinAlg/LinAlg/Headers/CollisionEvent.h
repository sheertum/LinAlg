#pragma once
#include "Figure.h"

class CollisionEvent {
public:
	CollisionEvent(Figure&, Figure&);
	Figure& figA;
	Figure& figB;
};