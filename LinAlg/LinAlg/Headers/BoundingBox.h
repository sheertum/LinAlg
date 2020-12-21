#pragma once
#include "Matrix.h"

class BoundingBox : public Matrix {
public:
    BoundingBox(std::vector<double>);
    BoundingBox();
    void calculateBoundingBox(std::vector<double> data);
    void changeBounds(double& min, double& max, double value);
    void drawMatrix();
    void toggleVisibility();
    bool isInside(BoundingBox);
    Vector getMax();
    Vector getMin();
private:
    void checkBoundingLimits(std::vector<double> data);
private:
    bool _isVisible;
	double _maxX;
	double _maxY;
	double _maxZ;
	double _minX;
	double _minY;
	double _minZ;
};