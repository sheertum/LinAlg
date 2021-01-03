#include "Bullet.h"
#include "UnitaryMatrix.h"
#include "TranslateMatrix.h"

Bullet::Bullet(const std::vector<Triangle>& triangles, World* world, Vector startPosition, Matrix axis, double velocityFactor) : Figure{ triangles, velocityFactor }, _world{world}
{
	//TODO: figue loader gebruiken om de triangles in te laden die bij het juiste figuur horen
	Vector direction{{axis(2,0),axis(2,1),axis(2,2)}};
	allignWithOriginator(direction);
	setAtOriginatorPosition(startPosition);
	
}

void Bullet::allignWithOriginator(Vector direction){
	double x = direction.coordinates[0];
    double y = direction.coordinates[1];
    double z = direction.coordinates[2];
    if (x == 0 && z == 0 && y == 0) {
        throw "CantRotateAroundPoint";
    }
	
    if (x == 0 && y == 0) {
		if(z<0){
			Matrix result = TranslateMatrix(0,0,-1);
			for(auto& triangle : _triangles){
				triangle.itirativeMultiply(result);
			}
			_axis.itirativeMultiply(result);
			return;
		} else {
			return;
		}
        
    }

	double x2z2 = sqrt(x*x+z*z);
    double x2y2z2 = sqrt(x*x+y*y+z*z);

    Matrix M1 = UnitaryMatrix(4);
    M1(0, 0) = z / x2z2;
    M1(2, 2) = z / x2z2;
    M1(0, 2) = -1*x / x2z2;
    M1(2, 0) = x / x2z2;

    Matrix M2 = UnitaryMatrix(4);
    M2(0, 0) = x2z2 / x2y2z2;
    M2(1, 1) = x2z2 / x2y2z2;
    M2(0, 1) = -1*y / x2y2z2;
    M2(1, 0) = y / x2y2z2;

	Matrix result = M2 * M1;
    
	for(auto& triangle : _triangles){
		triangle.itirativeMultiply(result);
	}
	_axis.itirativeMultiply(result);
}

void Bullet::setAtOriginatorPosition(Vector position){
	_axis.translate(position);
	_center = _center + position;
	for(auto& triangle : _triangles){
		triangle.translate(position);
	}
}
