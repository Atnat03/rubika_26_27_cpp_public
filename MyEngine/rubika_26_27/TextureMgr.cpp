#include "TextureMgr.h"
#include <SFML/Graphics.hpp>
#include <string.h>

TextureData::TextureData()
{

}

TextureData::~TextureData()
{

}

bool TextureMgr::LoadTexture(const std::filesystem::path& path)
{
    auto textureData = std::make_unique<TextureData>();

    if (!textureData->Texture.loadFromFile(path.string()))
    {
        return false;
    }

    textureData->Name = path.stem().string();

    TextureList.push_back(std::move(textureData));

    return true;
}

const TextureData& TextureMgr::GetTextureData(
    const std::string& name) const
{
    for (const auto& textureData : TextureList)
    {
        if (textureData->Name == name)
        {
            return *textureData;
        }
    }

    return DefaultTextureData;
}