#include <Scene.h>
#include <Entity.h>

Scene::Scene(const std::string& name)
{
	SceneName = name;
}

Scene::~Scene()
{
}

void Scene::Start()
{
	for (Entity entity : EntitList)
	{
		entity.Start();
	}
}

void Scene::Update(float fDeltaTime)
{
	for (Entity entity : EntitList)
	{
		entity.Update(fDeltaTime);
	}
}

void Scene::Destroy()
{
	for (Entity entity : EntitList)
	{
		entity.Destroy();
	}
}

void Scene::Draw(sf::RenderWindow& window) const
{
	for(Entity entity : EntitList)
	{
		entity.Draw(window);
	}
}

void Scene::AddEntity(Entity entity)
{
	EntitList.push_back(entity);
}

void Scene::RemoveEntity(Entity entity)
{
	for(Entity e : EntitList)
	{
		if(e == entity)
		{
			EntitList.erase(std::remove(EntitList.begin(), EntitList.end(), e), EntitList.end());
			return;
		}
	}
}

std::string Scene::GetName() const
{
	return SceneName;
}
