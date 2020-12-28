#include "FigureLoader.h"

#include <fstream>
#include <sstream>

//v = vertex
//vt = texture coordinates
//vn = normal vectors (for light)
//f = face (v1/v2/v3)
//	v1 = vertex index

#define END std::string::npos

Figure FigureLoader::load(const char* fileName)
{
	std::vector<Vector> vectors;
	std::vector<Triangle> triangles;

	std::ifstream in(fileName, std::ios::in);
	std::string line;

	while (std::getline(in, line))
	{
		if (line.substr(0, 2) == "v ") {
			handleVertex(line, vectors);
		}
		else if (line.substr(0, 2) == "f ") {
			handleTriangle(line, vectors, triangles);
		}
	}

	return Figure{ triangles };
}

void FigureLoader::handleVertex(const std::string& line, std::vector<Vector>& vectors)
{
	std::istringstream iss(line.substr(2));
	std::vector<double> vector;
	double value;

	while (iss) {
		iss >> value;
		vector.push_back(value);
	}

	vectors.push_back(Vector{ vector });
}

void FigureLoader::handleTriangle(const std::string& line, const std::vector<Vector>& vectors, std::vector<Triangle>& triangles)
{
	std::string data = line.substr(2);
	std::vector<Vector> result;
	result.reserve(3);

	auto index = data.find("/");
	index = (index == END) ? data.find(" ") : index;

	while (index != END)
	{
		result.push_back(vectors[std::stoi(data.substr(0, index))]);

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
