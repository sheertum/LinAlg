#include "BoundingBox.h"
BoundingBox::BoundingBox() : Matrix{ 8,3 }, _isVisible{false}, _maxX{0}, _maxY {0}, _maxZ {0}, _minX {0}, _minY {0} ,_minZ {0} {}

BoundingBox::BoundingBox(std::vector<double> data) : Matrix{ 8,3 }, _isVisible{false}, _maxX{0}, _maxY {0}, _maxZ {0}, _minX {0}, _minY {0} ,_minZ {0} {
    checkBoundingLimits(data);
    calculateBoundingBox(data);
}

BoundingBox::BoundingBox(Matrix data) : Matrix{ 8,3 }, _isVisible{false}, _maxX{0}, _maxY {0}, _maxZ {0}, _minX {0}, _minY {0} ,_minZ {0} {
    checkBoundingLimits(data.getData());
    calculateBoundingBox(data.getData());
}

void BoundingBox::calculateBoundingBox(std::vector<double> data){
    checkBoundingLimits(data);
    
	double maxX = data[0];
	double maxY = data[1];
	double maxZ = data[2];
	double minX = data[0];
	double minY = data[1];
	double minZ = data[2];

	for(int i = 1; i < (data.size()/3); i++){
		double x = data[0+3*i];
		changeBounds(minX, maxX, x);

		double y = data[1+3*i];
		changeBounds(minY, maxY, y);

		double z = data[2+3*i];
		changeBounds(minZ, maxZ, z);
	}
    
    _maxX = maxX;
	_maxY = maxY;
	_maxZ = maxZ;
	_minX = minX;
	_minY = minY;
	_minZ = minZ;
}

void BoundingBox::toggleVisibility(){
    if(_isVisible){
        _isVisible = false;
        return;
    } else {
        _isVisible = true;
    }
}

void BoundingBox::drawMatrix(){
    std::vector<double> matrixData{};
    Vector p1{ {_minX, _minY, _minZ} };
    Vector p2{ {_minX, _maxY, _minZ} };
    Vector p3{ {_minX, _maxY, _maxZ} };
    Vector p4{ {_minX, _minY, _maxZ} };

    Vector p5{ {_maxX, _minY, _minZ} };
    Vector p6{ {_maxX, _maxY, _minZ} };
    Vector p7{ {_maxX, _maxY, _maxZ} };
    Vector p8{ {_maxX, _minY, _maxZ} };

    std::vector<Vector> vectors {p1,p2,p3,p4,p5,p6,p7,p8};

    int columnIndex = 0;
	for (const auto& vector : vectors)
	{
		int rowIndex = 0;
		for (int i : vector.coordinates) {
			this->operator()(columnIndex, rowIndex++) = i;
		}

		columnIndex++;
	}
}

void BoundingBox::changeBounds(double& min, double& max, double value){
	if(value > max){
		max = value;
	}
	if(value < min){
		min = value;
	}
}

void BoundingBox::checkBoundingLimits(std::vector<double> data){
    if(data.size() < 6){
        throw "NoBoundingBoxForLines";
    }

    if(data.size() > 9){
        throw "OutOfBounds";
    }
}

bool BoundingBox::isInside(BoundingBox target){
	Vector targetMax = target.getMax();
	Vector targetMin = target.getMin();
	bool xOverlap = false;
	bool yOverlap = false;
	bool zOverlap = false;

	double targetMaxX = targetMax[0];
	double targetMinX = targetMin[0];
	if((_minX <= targetMaxX && _maxX  >= targetMaxX) || (_minX <= targetMinX && _maxX  >= targetMinX)){
		xOverlap = true;
	}

	double targetMaxY = targetMax[1];
	double targetMinY = targetMin[1];

	if((_minY <= targetMaxY && _maxY  >= targetMaxY) || (_minY <= targetMinY && _maxY  >= targetMinY)){
		yOverlap = true;
	}

	double targetMaxZ = targetMax[2];
	double targetMinZ = targetMin[2];
	if((_minZ <= targetMaxZ && _maxZ  >= targetMaxZ) || (_minZ <= targetMinZ && _maxZ  >= targetMinZ)){
		zOverlap = true;
	}

	if(xOverlap && yOverlap && zOverlap){
		return true;
	}
	return false;
}

Vector BoundingBox::getMax(){
	return Vector{{_maxX, _maxY, _maxZ}};
}

Vector BoundingBox::getMin(){
	return Vector{{_minX, _minY, _minZ}};
}
