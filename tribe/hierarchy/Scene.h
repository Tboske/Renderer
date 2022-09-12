#pragma once
#include "../pch.h"
#include "SceneManager.h"

class Scene final
{
public:
	Scene(const std::string_view sceneName);
	~Scene()                           = default;
	Scene(const Scene&)                = delete;
	Scene(Scene&&) noexcept            = delete;
	Scene& operator=(const Scene&)     = delete;
	Scene& operator=(Scene&&) noexcept = delete;

	const std::string_view GetName() const { return m_Name; };


private:
	std::string_view m_Name;

	friend class SceneManager;
	void Update();
	void Render() const;
};