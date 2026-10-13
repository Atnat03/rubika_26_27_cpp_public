#include "TextureMgr.h"
#include <SFML/Graphics.hpp>
#include <string.h>

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <rapidxml/rapidxml_print.hpp>

#include <Logger.h>

using namespace rapidxml;
using namespace std;

TextureData::TextureData()
{
}

TextureData::~TextureData()
{

}

bool TextureMgr::LoadTexture(const std::filesystem::path& path)
{
    TextureData textureData = TextureData();

    if (!textureData.Texture.loadFromFile(path.string()))
    {
		Logger::Error("Failed to load texture: " + path.string());
        return false;
    }

    std::string key = path.stem().string();

    TextureList.emplace(key, textureData);

    LoadXml(path);

    return true;
}

void TextureMgr::LoadXml(const std::filesystem::path& path)
{
	std::filesystem::path xmlPath = path;
	xmlPath.replace_extension(".xml");

    std::ifstream file(xmlPath, std::ios::binary);

    if (!file)
    {
        Logger::Error("Failed to open XML file: " + xmlPath.string());
		return;
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    buffer.push_back('\0');

    xml_document<> doc;
    doc.parse<0>(buffer.data());

    xml_node<>* rootNode = doc.first_node("Animations");
    xml_node<>* animationNode = rootNode->first_node("Animation");

        TextureData& textureData = TextureList.at(path.stem().string());

        for (xml_node<>* anim = rootNode->first_node("Animation");
            anim != nullptr;
            anim = anim->next_sibling("Animation"))
        {
            string name = anim->first_attribute("Name")->value();

            AnimationData data;

            if (anim->first_node("X") != nullptr)
                data.StartX = std::stoi(anim->first_node("X")->value());

            if (anim->first_node("Y") != nullptr)
                data.StartY = std::stoi(anim->first_node("Y")->value());

            if (anim->first_node("SizeX") != nullptr)
                data.SizeX = std::stoi(anim->first_node("SizeX")->value());

            if (anim->first_node("SizeY") != nullptr)
                data.SizeY = std::stoi(anim->first_node("SizeY")->value());

            if (anim->first_node("OffsetX") != nullptr)
                data.OffsetX = std::stoi(anim->first_node("OffsetX")->value());

            if (anim->first_node("OffsetY") != nullptr)
                data.OffsetY = std::stoi(anim->first_node("OffsetY")->value());

            if (anim->first_node("SpriteNum") != nullptr)
                data.AnimationSpriteCount = std::stoi(anim->first_node("SpriteNum")->value());

            if (anim->first_node("SpritesOnLine") != nullptr)
                data.SpriteOnLine = std::stoi(anim->first_node("SpritesOnLine")->value());

            if (anim->first_node("Reverted") != nullptr)
                data.IsReverted = std::stoi(anim->first_node("Reverted")->value());

            if (anim->first_node("TimeBetweenAnimation") != nullptr)
                data.TimeBetweenAnimationInS = std::stoi(anim->first_node("TimeBetweenAnimation")->value());

            textureData.AnimationsData.emplace(name, data);
        }
}

const TextureData& TextureMgr::GetTextureData(const std::string& name) const
{
    return TextureList.at(name);
}