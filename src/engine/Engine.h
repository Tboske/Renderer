#pragma once
#include "../pch.h"
#include <memory>

class GLFWwindow;
class Renderer;
class GameTime;
class SceneManager;

class Engine
{
public:
	Engine();
	~Engine();


	void Run();

private:
	std::unique_ptr<Renderer> m_pRenderer;
	std::unique_ptr<GameTime> m_pGameTime;
	std::unique_ptr<SceneManager> m_pSceneManager;

	static void InputCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
};
