#pragma once

#include <SFML/Graphics/Texture.hpp>

#include <filesystem>
#include <string>
#include <vector>
#include <map>

struct AnimationData
{
	int StartX = 0;
	int StartY = 0;
	int SizeX = 0;
	int SizeY = 0;
	int OffsetX = 0;
	int OffsetY = 0;
	int AnimationSpriteCount = 0;
	int SpriteOnLine = 0;
	bool IsReverted = false;
	float TimeBetweenAnimationInS = 0.f;
};

struct StaticTileData
{
	int StartX = 0;
	int StartY = 0;
	int SizeX = 0;
	int SizeY = 0;
	bool IsRevertedX = false;
	bool IsRevertedY = false;
};

struct TextureData
{
	TextureData();
	~TextureData();

	sf::Texture Texture;

	std::map<std::string, StaticTileData> StaticTilesData;
	std::map<std::string, AnimationData> AnimationsData;

	friend class TextureMgr;
};

class TextureMgr final
{
public:
	void Init();
	void Shut();

	bool LoadTexture(const std::filesystem::path& path);
	const TextureData& GetTextureData(const std::string& name) const;

	void LoadXml(const std::filesystem::path& path);

	std::map<std::string, TextureData> TextureList;

	TextureData DefaultTextureData;
};