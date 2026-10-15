#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include <TextureMgr.h>

class TransformComponent;
class RenderComponent;

namespace sf
{
	class RenderWindow;
}

class Entity
{
public:
	Entity(std::string name = "");
	virtual ~Entity();

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void Destroy();

	void Draw(sf::RenderWindow& window) const;

	void UpdateAnimation();

	std::string GetName() const;

	bool operator==(const Entity& other) const
	{
		return name == other.name;
	}

	TransformComponent* Transform;
	RenderComponent* Render;

protected :
	std::string name = "";

	sf::Texture texture;

	sf::Sprite headSprite;
	sf::Sprite bodySprite;

	bool isMoving = false;

	TextureData& textureData;

	AnimationData headData;
	AnimationData bodyData;

	std::string currentAnimationHead = "";
	std::string currentAnimationBody = "";

	int currentFrameAnimation = 0;
	float frameIntervale = 0.085f;
	float elapsedTime = 0.f;
};
