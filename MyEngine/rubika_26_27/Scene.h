#pragma once

#include <string>
#include <vector>

namespace sf
{
	class RenderWindow;
}

class Scene
{
public:

	Scene(const std::string& name);
	~Scene();

	virtual void Start();
	virtual void Update(float fDeltaTime);
	virtual void Destroy();

	/*
	 * This function will be removed later, when the rendering system will be more robust. But for now, we need it here.
	 * Function that will be called each frame to draw the entity
	*/
	void Draw(sf::RenderWindow& window) const;

	void AddEntity(class Entity* entity);
	void RemoveEntity(class Entity* entity);

	bool operator==(const Scene& other) const
	{
		return SceneName == other.SceneName;
	}

	std::string GetName() const;
	std::vector<class Entity*> EntitList;

private:
	std::string SceneName = "";

};