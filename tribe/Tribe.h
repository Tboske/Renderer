#pragma once
#include "pch.h"
#include <memory>

class GLFWwindow;
class Window;
class GameTime;
class SceneManager;
class Renderer;

class Tribe
{
public:
	Tribe();
	~Tribe();

	// loadgame needs to become pure virtual 
	virtual void LoadGame();
	void Run();


private:
	std::unique_ptr<Renderer> m_pRenderer;
	std::unique_ptr<GameTime> m_pGameTime;
	std::unique_ptr<SceneManager> m_pSceneManager;

	static void InputCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
};
