#pragma once
#include "../pch.h"
#include "BaseObject.h"

class GameObject;
class Scene final : public BaseObject
{
public:
	Scene(const std::string_view sceneName);
	~Scene()                           = default;
	Scene(const Scene&)                = delete;
	Scene(Scene&&) noexcept            = delete;
	Scene& operator=(const Scene&)     = delete;
	Scene& operator=(Scene&&) noexcept = delete;
private:
	friend class SceneManager;
};