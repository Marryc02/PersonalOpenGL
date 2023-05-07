#include "FileLoader.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Vertex& v)
{
	os << std::fixed;
	os << "(" << v.pos[0] << ", " << v.pos[1] << ", " << v.pos[2] << ") ";
	os << "(" << v.rgb[0] << ", " << v.rgb[1] << ", " << v.rgb[2] << ") ";
	os << "(" << v.st[0] << ", " << v.st[1] << ") ";
	return os;
}

std::istream& operator>>(std::istream& is, Vertex& v)
{
	char dum, dum2, dum3, dum4;
	is >> dum >> v.pos[0] >> dum2 >> v.pos[1] >> dum3 >> v.pos[2] >> dum4;
	is >> dum >> v.rgb[0] >> dum2 >> v.rgb[1] >> dum3 >> v.rgb[2] >> dum4;
	is >> dum >> v.st[0] >> dum2 >> v.st[1] >> dum3;
	return is;
}

void FileLoader::ReadFile(std::string filePath, std::vector<Vertex>& mVerticesRef)
{
    std::ifstream inn;
    inn.open(filePath.c_str());

    if (inn.is_open())
    {
        int n;
        Vertex vertex;
        inn >> n;
        mVerticesRef.reserve(n);
        for (int i = 0; i < n; i++)
        {
            inn >> vertex;
            mVerticesRef.push_back(vertex);
        }
        inn.close();
    }
    else
    {
        std::cout << "Error reading file: \"" << filePath << "\"" << std::endl;
    }
}

void FileLoader::WriteFile(std::string filePath, std::vector<Vertex>& mVerticesRef)
{
    std::ofstream ut;
    ut.open(filePath.c_str());

    if (ut.is_open())
    {
        auto n = mVerticesRef.size();
        Vertex vertex;
        ut << n << std::endl;
        for (auto it = mVerticesRef.begin(); it != mVerticesRef.end(); it++)
        {
            ut << *it << std::endl;
        }

        ut.close();
    }
    else
    {
        std::cout << "Error reading file: \"" << filePath << "\"" << std::endl;
    }
}

void FileLoader::ReadFileIndices(std::string filePath, std::vector<unsigned int>& mIndicesRef)
{
    std::ifstream inn;
    inn.open(filePath.c_str());

    if (inn.is_open())
    {
        int n;
        unsigned int index;
        inn >> n;
        mIndicesRef.reserve(n);
        for (int i = 0; i < n; i++)
        {
            inn >> index;
            mIndicesRef.push_back(index);
        }

        inn.close();
    }
    else
    {
        std::cout << "Error reading file: \"" << filePath  << "\"" << std::endl;
    }
}

void FileLoader::WriteFileIndices(std::string filePath, std::vector<unsigned int>& mIndicesRef)
{
    std::ofstream ut;
    ut.open(filePath);

    if (ut.is_open())
    {
        auto n = mIndicesRef.size();
        ut << n << std::endl;

        for (auto it = mIndicesRef.begin(); it != mIndicesRef.end(); it++)
        {
            ut << *it << std::endl;
        }

    }
    else
    {
        std::cout << "Error reading file: \"" << filePath << "\"" << std::endl;
    }
}
