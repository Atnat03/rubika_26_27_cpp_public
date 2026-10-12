#include <SceneManager.h>
#include <Scene.h>
#include <Logger.h>
#include <Entity.h>

#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#endif

SceneManager::SceneManager()
{
	Logger::Info("SceneManager created");
}

SceneManager::~SceneManager()
{
}

void SceneManager::Start()
{
	for(Scene* scene : SceneList)
	{
		scene->Start();
	}
}

void SceneManager::Update(float fDeltaTime)
{
	for (Scene* scene : SceneList)
	{
		scene->Update(fDeltaTime);
	}
}

void SceneManager::Destroy()
{
	for (Scene* scene : SceneList)
	{
		scene->Destroy();
	}
}

void SceneManager::Draw(sf::RenderWindow& window) const
{
	if(GetActiveScene() == nullptr)
		return;

	GetActiveScene()->Draw(window);
}

void SceneManager::AddScene(Scene* scene)
{
	for (Scene* s : SceneList)
	{
		if (s == scene)
			return;
	}

	SceneList.push_back(scene);
}

void SceneManager::RemoveScene(std::string name)
{
	for (Scene* scene : SceneList)
	{
		if (scene == nullptr) continue;

		if (scene->GetName() == name)
		{
			SceneList.erase(std::remove(SceneList.begin(), SceneList.end(), scene), SceneList.end());
		}
	}
}

Scene* SceneManager::GetActiveScene() const
{
	for (size_t i = 0; i < SceneList.size(); i++)
	{
		if(i == activeSceneIndex)
		{
			return SceneList[i];
		}
	}

	return nullptr;
}

void SceneManager::SetNextSceneAsActive()
{
	activeSceneIndex = (activeSceneIndex + 1) % SceneList.size();
}

void SceneManager::SetPreviousSceneAsActive()
{
	activeSceneIndex = (activeSceneIndex - 1 + SceneList.size()) % SceneList.size();
}

Scene* SceneManager::GetActiveScene(std::string name) const
{
	for(Scene* scene : SceneList)
	{
		if(scene == nullptr) continue;

		if(scene->GetName() == name)
		{
			return scene;
		}
	}

	return nullptr;
}

void SceneManager::DrawDebug()
{
#ifdef _USE_IMGUI
	if (ImGui::Button("Add Scene"))
	{
		AddScene(new Scene("Scene "  + std::to_string(currentSceneIndex)));

		currentSceneIndex++;

		Logger::Info("new scene created");
	}

	if (SceneList.size() > 1)
	{
		ImGui::Text("Change active scene");

		if (ImGui::Button("Next Scene"))
		{
			SetNextSceneAsActive();
		}
		if (ImGui::Button("Previous Scene"))
		{
			SetPreviousSceneAsActive();
		}
	}

	if (GetActiveScene())
	{
		Scene* activeScene = GetActiveScene();

		ImGui::Text("Active Scene : %s", activeScene->GetName().c_str());
		ImGui::Text("Number of entities in active scene : %d", activeScene->EntitList.size());

		if (ImGui::Button("Inspec Active Scene"))
		{
			Logger::Warning("Scene name : " + activeScene->GetName());

			for(Entity entity : activeScene->EntitList)
			{
				Logger::Warning("Entity name : " + entity.GetName());
			}
		}

		if (ImGui::Button("Add Entity"))
		{
			activeScene->AddEntity(Entity("Entity " + std::to_string(rand() % 100)));
			Logger::Warning("new entity");
		}

		if(ImGui::Button("Remove Active Scene"))
		{
			Logger::Warning("Removing scene : " + activeScene->GetName());
			RemoveScene(activeScene->GetName());
		}
	}


#endif
}
