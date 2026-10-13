#include "DebugMgr.h"

#ifdef _USE_IMGUI
#include <Imgui/imgui.h>
#endif

void DebugMgr::Draw()
{
#ifdef _USE_IMGUI
	if (ImGui::Begin("Debug"))
	{
		if (ImGui::BeginTabBar("##Sections"))
		{
			for (const auto& [name, ptr] : Debugables)
			{
				if (ImGui::BeginTabItem(name.c_str()))
				{
					ptr->DrawDebug();
					ImGui::EndTabItem();
				}
			}
			ImGui::EndTabBar();
		}

	}
	ImGui::End();
#endif
}

bool DebugMgr::RegisterDebugableWindow(const std::string& debugName, IDebugable* pDebugable)
{
#ifdef _USE_IMGUI
	const auto& it = Debugables.find(debugName);
	if (it != Debugables.end())
	{
		return false;
	}

	Debugables.emplace(debugName, pDebugable);
#endif
	return true;
}

void DebugMgr::UnregisterDebugableWindow(const std::string& debugName)
{
#ifdef _USE_IMGUI
	const auto& it = Debugables.find(debugName);
	if (it == Debugables.end())
	{
		return;
	}

	Debugables.erase(it);
#endif
}

bool DebugMgr::RegisterDebugAction(const std::string& debugName, std::function<void(void*)> callback, void* userData)
{
#ifdef _USE_IMGUI
	const auto& it = Actions.find(debugName);
	if (it != Actions.end())
	{
		return false;
	}

	Actions.emplace(debugName, sDebugAction{ callback , userData });
#endif
	return true;
}

void DebugMgr::UnregisterDebugAction(const std::string& debugName)
{
#ifdef _USE_IMGUI
	const auto& it = Actions.find(debugName);
	if (it == Actions.end())
	{
		return;
	}

	Actions.erase(it);
#endif
}
