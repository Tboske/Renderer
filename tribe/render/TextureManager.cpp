#include "TextureManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TextureManager::TextureManager(const std::string_view directory)
    : m_Directory(directory)
{

}

Texture* TextureManager::LoadTexture(std::string_view path)
{

    return nullptr;
}