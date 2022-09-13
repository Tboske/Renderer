#pragma once
#include "../pch.h"
#include "Base.h"

class GameObject;
class Scene final : public Base
{
public:
	Scene(const std::string_view sceneName);
	virtual ~Scene() override          = default;
	Scene(const Scene&)                = delete;
	Scene(Scene&&) noexcept            = delete;
	Scene& operator=(const Scene&)     = delete;
	Scene& operator=(Scene&&) noexcept = delete;
private:
	friend class SceneManager;
};