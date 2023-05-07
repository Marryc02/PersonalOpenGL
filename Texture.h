#pragma once

#include <glad/glad.h>

class Texture
{
public:
	Texture();
	Texture(char* filePath);
	~Texture();

	void LoadTexture();
	void UseTexture();
	void ClearTexture();

private:
	GLuint textureID;
	int width, height, bitDepth;
	char* fileLocation;

};

