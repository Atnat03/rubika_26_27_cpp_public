#include "TextureMgr.h"
#include <SFML/Graphics.hpp>
#include <string.h>

#include <rapidxml/rapidxml.hpp>
#include <rapidxml/rapidxml_utils.hpp>
#include <rapidxml/rapidxml_print.hpp>

#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#include <Imgui/imgui-SFML.h>
#endif

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

void TextureMgr::PrintDebug()
{
#ifdef _USE_IMGUI
    ImGui::Begin("Loading Debug");

    ImGui::Text("Nombre de textures : %zu", TextureList.size());

    for (auto& [name, data] : TextureList)
    {
        if (ImGui::Button(name.c_str()))
        {
            SelectedTextureName = name;
            ShowAnimations = false;
            ShowStaticTiles = false;
        }
    }

    if (!SelectedTextureName.empty() && TextureList.contains(SelectedTextureName))
    {
        ImGui::Separator();

        ImGui::Text("Texture selectionnee : %s",
            SelectedTextureName.c_str());

        PrintTextureData(TextureList.at(SelectedTextureName));
    }

    ImGui::End();
#endif
}

void TextureMgr::PrintTextureData(TextureData& data)
{
#ifdef _USE_IMGUI
    ImGui::Text("Animations : %zu", data.AnimationsData.size());
    ImGui::Text("Static tiles : %zu", data.StaticTilesData.size());
    ImGui::Text("Texture handle : %u", data.Texture.getNativeHandle());

    ImGui::Image(data.Texture);

    if (ImGui::Button("Afficher les animations"))
        ShowAnimations = !ShowAnimations;

    if (ShowAnimations)
    {
        for (auto& [name, animation] : data.AnimationsData)
        {
            ImGui::PushID(name.c_str());

            if (ImGui::TreeNode(name.c_str()))
            {
                PrintAnimationData(animation);
                ImGui::TreePop();
            }

            ImGui::PopID();
        }
    }

    if (ImGui::Button("Afficher les tiles statiques"))
        ShowStaticTiles = !ShowStaticTiles;

    if (ShowStaticTiles)
    {
        for (auto& [name, tile] : data.StaticTilesData)
        {
            ImGui::PushID(name.c_str());

            if (ImGui::TreeNode(name.c_str()))
            {
                PrintStaticData(tile);
                ImGui::TreePop();
            }

            ImGui::PopID();
        }
    }
#endif
}

void TextureMgr::PrintAnimationData(AnimationData& data)
{
#ifdef _USE_IMGUI
    ImGui::Text("Start Position : {%d ; %d}", data.StartX, data.StartY);
    ImGui::Text("Size : {%d ; %d}", data.SizeX, data.SizeY);
    ImGui::Text("Offset : {%d ; %d}", data.OffsetX, data.OffsetY);
    ImGui::Text("Animation Count : %d", data.AnimationSpriteCount);
    ImGui::Text("Sprite on line : %d", data.SpriteOnLine);
    ImGui::Text("Is reversed : %s", data.IsReverted ? "true" : "false");
    ImGui::Text("Time between animation : %.3f s", data.TimeBetweenAnimationInS);
#endif
}

void TextureMgr::PrintStaticData(StaticTileData& data)
{
#ifdef _USE_IMGUI
    ImGui::Text("Start Position : {%d ; %d}", data.StartX, data.StartY);
    ImGui::Text("Size : {%d ; %d}", data.SizeX, data.SizeY);
    ImGui::Text("Is reversed X : %s", data.IsRevertedX ? "true" : "false");
    ImGui::Text("Is reversed Y : %s", data.IsRevertedY ? "true" : "false");
#endif
}

const TextureData& TextureMgr::GetTextureData(const std::string& name) const
{
    return TextureList.at(name);
}