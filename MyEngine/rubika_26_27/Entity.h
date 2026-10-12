#pragma once

#include <string>
#include <TransformComponent.h>
#include <SFML/Graphics.hpp>

namespace sf
{
	class RenderWindow;
}

class Entity
{
public:
	Entity(std::string friendlyName = "");
	virtual ~Entity();

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void Destroy();

	/*
	 * This function will be removed later, when the rendering system will be more robust. But for now, we need it here.
	 * Function that will be called each frame to draw the entity
	*/
	void Draw(sf::RenderWindow& window) const;
	
	std::string GetName() const;

	bool operator==(const Entity& other) const
	{
		return name == other.name;
	}

	TransformComponent Transform;

private :
	std::string name = "";

	sf::CircleShape sprite;
};
