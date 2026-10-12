#pragma once

#include <DebugMgr.h>

#include <string>
#include <vector>

namespace sf
{
	class RenderWindow;
}

class Scene;

class SceneManager : IDebugable
{
public:
	SceneManager();
	~SceneManager();

	void Start();
	void Update(float fDeltaTime);
	void Destroy();
	void Draw(sf::RenderWindow& window) const;

	void AddScene(class Scene* scene);
	void RemoveScene(std::string name);
	Scene* GetActiveScene(std::string name) const;
	Scene* GetActiveScene() const;

	void SetNextSceneAsActive();
	void SetPreviousSceneAsActive();


	virtual void DrawDebug() override;

private:
	std::vector<Scene*> SceneList;
	int currentSceneIndex = 0;
	int activeSceneIndex = 0;
};

