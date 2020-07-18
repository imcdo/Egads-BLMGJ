#include "sprite.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

LoadSpriteData Sprite::TextureFromFile(std::string filename, bool gamma) {
    LoadSpriteData result;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi__vertically_flip_on_load_global = true;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data) {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else {
        std::cout << "Texture failed to load at path: " << filename << std::endl;
        stbi_image_free(data);
    }

    result.height = height;
    result.width = width;
    result.textureID = textureID;

    return result;
}

Sprite::Sprite(std::string path, SpriteType sType, unsigned int pixelsPerInch) :
    _loadData(TextureFromFile(path, false)), 
    height(_loadData.height), width(_loadData.width), 
    textureID(_loadData.textureID), spriteType(sType),
    ppi(pixelsPerInch)
{
}

Sprite& Sprite::operator= (const Sprite& s) {
    _loadData = s._loadData;
    height = s.height;
    width = s.width;
    textureID = s.textureID;

    return *this;
}
