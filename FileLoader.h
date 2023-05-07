#pragma once

#include "Vertex.h"
#include <fstream>
#include <vector>

class FileLoader
{
public:

	void ReadFile(std::string filePath, std::vector<Vertex>& mVerticesRef);
	void WriteFile(std::string filePath, std::vector<Vertex>& mVerticesRef);

	void ReadFileIndices(std::string filePath, std::vector<unsigned int>& mIndicesRef);
	void WriteFileIndices(std::string filePath, std::vector<unsigned int>& mIndicesRef);
	

	friend std::ostream& operator<< (std::ostream&, const Vertex&);

	friend std::istream& operator>> (std::istream&, Vertex&);
};

