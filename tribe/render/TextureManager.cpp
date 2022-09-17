#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureManager::TextureManager(const std::string_view directory)
    : m_Directory(directory)
{

}

Texture* TextureManager::LoadTexture(const std::string_view path)
{
    auto& texture = m_Textures[path];
    if (texture) 
        return texture;

    // make the texture in openGL
    glGenTextures(1, &texture->data);
    glBindTexture(GL_TEXTURE_2D, texture->data);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load raw image data
    unsigned char *rawData = stbi_load("logo.png", &texture->width, &texture->height, 
        &texture->nrChannels, 0);
    if (!rawData) 
        throw "Failed to load texture";

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 
        texture->width, texture->height, 
        0, GL_RGB, 
        GL_UNSIGNED_BYTE, rawData
    );

    // cleanup the raw image data
    stbi_image_free(rawData);

    return texture;
}