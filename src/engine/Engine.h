#pragma once
#include "../pch.h"
#include "GameTime.h"

class Renderer;
class GameTime;

class Engine
{
public:
	Engine();
	~Engine();


	void Run();

private:
	std::unique_ptr<Renderer> m_pRenderer;
	std::unique_ptr<GameTime> m_pGameTime;

	static void InputCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
};
