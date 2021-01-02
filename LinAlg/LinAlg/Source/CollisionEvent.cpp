#include "CollisionEvent.h"

CollisionEvent::CollisionEvent(std::shared_ptr<Figure>& A, std::shared_ptr<Figure>& B) : figA{ A }, figB{ B } {}
