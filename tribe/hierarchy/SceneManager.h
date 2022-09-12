#pragma once
#include "../pch.h"

class Scene;
class SceneManager final
{
public:
	SceneManager();
	~SceneManager();
	SceneManager(const SceneManager&)                = delete;
	SceneManager(SceneManager&&) noexcept            = delete;
	SceneManager& operator=(const SceneManager&)     = delete;
	SceneManager& operator=(SceneManager&&) noexcept = delete;

    Scene* AddScene(const std::string_view sceneName);
	Scene* GetScene(const std::string_view sceneName) const;
	Scene* GetScene(size_t sceneID) const;
	Scene* GetActiveScene() const;
	void ActivateScene(size_t sceneID);
	void ActivateScene(const std::string_view sceneName);

private:
	std::vector<std::unique_ptr<Scene>> m_pScenes;
	int m_ActiveSceneIdx;
	
	friend class Tribe;
	void Update();
	void Render() const;
};