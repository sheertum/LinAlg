#include "FigureLoader.h"

#include <fstream>
#include <sstream>

//v = vertex
//vt = texture coordinates
//vn = normal vectors (for light)
//f = face (v1/v2/v3)
//	v1 = vertex index

#define END std::string::npos

Figure FigureLoader::load(const char* fileName, int maxCoordinate, int minCoordinate, double scale)
{
	double objMin = -4.0;
	double objMax = 11.0 + abs(objMin);
	double factor = maxCoordinate / objMax;

	std::vector<Vector> vectors;
	std::vector<Triangle> triangles;

	std::ifstream in(fileName, std::ios::in);
	std::string line;

	while (std::getline(in, line))
	{
		if (line.substr(0, 2) == "v ") {
			Vector vector = ((handleVertex(line) * factor)* scale) + 500;
			vectors.push_back(vector);
		}
		else if (line.substr(0, 2) == "f ") {
			handleTriangle(line, vectors, triangles);
		}
	}

	return Figure{ triangles };
}

Vector FigureLoader::handleVertex(const std::string& line)
{
	std::istringstream iss(line.substr(2));
	std::vector<double> vector;
	double value;

	while (iss) {
		iss >> value;
		vector.push_back(value);
	}

	return Vector{ vector };
}

void FigureLoader::handleTriangle(const std::string& line, const std::vector<Vector>& vectors, std::vector<Triangle>& triangles)
{
	std::string data = line.substr(2);
	std::vector<Vector> result;
	result.reserve(3);

	auto index = data.find("/");
	index = (index == END) ? data.find(" ") : index;

	while (index != END && data.size() > 0)
	{
		std::string value{ data.substr(0, index) };
		size_t vectorIndex = std::stoi(value);
		result.push_back(vectors[vectorIndex-1]);

		auto cutIndex = data.find(" ");
		if (cutIndex != END)
		{
			data = data.substr(cutIndex + 1);
		}
		else {
			break;
		}

		data.find("/");
		index = (index == END) ? data.find(" ") : index;
	}

	triangles.push_back({ result[0], result[1], result[2] });
}
