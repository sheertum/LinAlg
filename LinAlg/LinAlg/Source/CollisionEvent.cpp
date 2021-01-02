#include "CollisionEvent.h"

CollisionEvent::CollisionEvent(std::unique_ptr<Figure>& A, std::unique_ptr<Figure>& B) : figA{ A }, figB{ B } {}
