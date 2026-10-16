#pragma once

#include <string>
#include <SFML/Graphics.hpp>

#include <TextureMgr.h>
#include <vector>

class IComponent;

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

	std::string GetName() const;

	bool operator==(const Entity& other) const
	{
		return name == other.name;
	}

	template <typename C>
	C* AddComponent();

	template <typename C>
	C* GetComponent() const;

protected :

	std::string name = "";

	sf::Texture texture;

	TextureData& textureData;

private:
	std::vector<IComponent*> Components;
};

#include <Component.hxx>
