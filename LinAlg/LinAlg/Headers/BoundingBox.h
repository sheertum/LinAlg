#pragma once
#include "Matrix.h"

class BoundingBox : public Matrix {
public:
    BoundingBox(std::vector<double>);
    BoundingBox(Matrix);
    BoundingBox();
    void calculateBoundingBox(std::vector<double> data);
    void changeBounds(double& min, double& max, double value);
    void drawMatrix();
    void toggleVisibility();
    bool isInside(BoundingBox);
    Vector getMax();
    Vector getMin();

    double getWidth() const;
    double getHeight() const;
    double getLength() const;

    double getMaxX() const;
    double getMaxY() const;
    double getMaxZ() const;

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