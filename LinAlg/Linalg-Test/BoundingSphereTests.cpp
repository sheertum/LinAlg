#include "pch.h"

class BoundingSphereTest : public ::testing::Test {
protected:
	void SetUp() override {
		Vector p1{ {0,0,0} };
		Vector p2{ {0,200,0} };
		Vector p3{ {200,0,0} };

		Vector p4{ {300,300,0} };
		Vector p5{ {300,500,0} };
		Vector p6{ {500,300,0} };
	}

	Figure fig1;
	Figure fig2;
};