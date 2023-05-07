#include "Texture.h"

#include <iostream>
#include "stb_image.h"

Texture::Texture()
{
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = nullptr;
}

Texture::Texture(char* filePath)
{
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = filePath;
}

Texture::~Texture()
{
    ClearTexture();
}

void Texture::LoadTexture()
{
    stbi_set_flip_vertically_on_load(true);
    unsigned char* texdata = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID); // we bind the texture here 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //S Axis // we want to repeat the texture to fill the mesh 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T Axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // we apply filters for min and mag as a linear 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0); // we unbind the texture 

    if (texdata)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texdata);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "ERROR - Could not load texture in given filepath: " + std::string(fileLocation) << std::endl;
    }
    //	glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(texdata);
}

void Texture::UseTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::ClearTexture()
{
    glDeleteTextures(1, &textureID);
    textureID = 0;
    width = 0;
    height = 0;
    bitDepth = 0;
    fileLocation = nullptr;
}
