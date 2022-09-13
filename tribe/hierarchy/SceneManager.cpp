#include "SceneManager.h"

#include "Scene.h"

#include <cstddef>
#include <memory>
#include <vector>

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

Scene* SceneManager::AddScene(const std::string_view sceneName)
{
	if (sceneName.empty())
		throw "Provided parameter (sceneName) is invalid.";

	return m_pScenes.emplace_back(/*std::make_unique(sceneName)*/).get();
}

Scene* SceneManager::GetScene(const std::string_view sceneName) const
{
	const auto& foundIt = std::ranges::find_if(
	    m_pScenes, [&sceneName](const std::unique_ptr<Scene>& pScene) { return sceneName == pScene->GetName(); });

	if (foundIt == m_pScenes.cend())
		throw "Couldn't find parameter (sceneName) in m_pScenes.";

	return foundIt->get();
}

Scene* SceneManager::GetScene(size_t sceneID) const
{
	if (sceneID >= m_pScenes.size())
		throw "Provided parameter (sceneID) is invalid.";

	return m_pScenes[sceneID].get();
}

Scene* SceneManager::GetActiveScene() const
{
	return m_pScenes[m_ActiveSceneIdx].get();
}

void SceneManager::ActivateScene(size_t sceneID)
{
	if (sceneID >= m_pScenes.size())
		throw "Provided parameter (sceneID) is invalid.";

	m_ActiveSceneIdx = sceneID;
}

void SceneManager::ActivateScene(const std::string_view sceneName)
{
	if (sceneName.empty())
		throw "Provided parameter (sceneName) is invalid.";

	for (int i = 0; i < int(m_pScenes.size()); ++i)
	{
		if (m_pScenes[i]->GetName() != sceneName)
			continue;

		ActivateScene(i);
		return;
	}

	// if nothing was found, throw exception
	throw std::runtime_error(std::string("SceneManager::ActivateScene: sceneName '") + sceneName.data() + "' does not exist");
}

void SceneManager::Update()
{
	for (const auto& pScene : m_pScenes)
		pScene->Update();
}

void SceneManager::Render() const
{
	m_pScenes[m_ActiveSceneIdx]->Render();
}