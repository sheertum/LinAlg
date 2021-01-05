#include "FigureLoader.h"

#include <fstream>
#include <sstream>
#include <iostream>

//v = vertex
//vt = texture coordinates
//vn = normal vectors (for light)
//f = face (v1/v2/v3)
//	v1 = vertex index

#define END std::string::npos

std::vector<Triangle> FigureLoader::load(const char* fileName, int maxCoordinate, int minCoordinate, double scale)
{
	double objMin = -4;
	double objMax = 4 + abs(objMin);
	double factor = maxCoordinate / objMax;

	std::vector<Vector> vectors;
	std::vector<Vector> normals;
	std::vector<Triangle> triangles;

	std::ifstream in(fileName, std::ios::in);
	std::string line;

	while (std::getline(in, line))
	{
		if (line.substr(0, 2) == "v ") {
			Vector vector = ((handleVertex(line) * factor)* scale);
			vectors.push_back(vector);
		}
		else if (line.substr(0, 3) == "vn ") {
			Vector normal = handleVertex(line);
			normals.push_back(normal);
		}
		else if (line.substr(0, 2) == "f ") {
			handleTriangle(line, vectors, normals, triangles);
		}
	}

	return triangles;
}

Vector FigureLoader::handleVertex(const std::string& line)
{
	std::istringstream iss(line.substr(2));
	std::vector<double> vector;
	double value;

	while (iss) {
		iss >> value;
		vector.push_back(value);
		if (vector.size() == 3)
		{
			break;
		}
	}

	return Vector{ vector };
}

void FigureLoader::handleTriangle(const std::string& line, const std::vector<Vector>& vectors, const std::vector<Vector>& normals, std::vector<Triangle>& triangles)
{
	std::string data = line.substr(2);
	std::vector<Vector> vectorIndices;
	std::vector<Vector> normalIndices;

	vectorIndices.reserve(4);
	normalIndices.reserve(4);

	auto index = data.find("/");
	bool slash = true;

	if (index == std::string::npos)
	{
		slash = false;
		index = data.find(" ");
	}

	while (index != END && data.size() > 0)
	{
		vectorIndices.push_back(vectors[fileterIndex(data, index)-1]);

		//normalIndices.push_back(normals[fileterIndex(data, findNth(data," ", 1), findNth(data, "/", 2) - 1)]);

		auto cutIndex = data.find(" ");
		if (cutIndex != END)
		{
			data = data.substr(cutIndex + 1);
		}
		else {
			break;
		}

		index = (slash) ? data.find("/") : data.find(" ");
	}

	triangles.push_back(Triangle{ vectorIndices[0], vectorIndices[1], vectorIndices[2], Vector{{0,0,-1}} });//  normalIndices[0]});
	if (vectorIndices.size() < 3)
	{
		//triangles.push_back(Triangle{ vectorIndices[1], vectorIndices[2], vectorIndices[3], Vector{{0,0,-1}} });
	}
}

size_t FigureLoader::findNth(const std::string& line, const std::string& lookFor, size_t nth)
{
	size_t  pos = 0;
	int     cnt = 0;

	while (cnt != nth)
	{
		pos += 1;
		pos = line.find(lookFor, pos);
		if (pos == std::string::npos)
			return std::string::npos;
		cnt++;
	}

	return pos;
}

size_t FigureLoader::fileterIndex(const std::string& line, size_t last, size_t first)
{
	std::string value{ line.substr(first, last-first) };
	size_t vectorIndex = std::stoi(value);

	//std::cout << vectorIndex << "\n";
	return vectorIndex;
}
