#pragma once
#include "../pch.h"

class Renderer;

class Engine
{
public:
	Engine();
	~Engine();


	void Run();

private:
	std::unique_ptr<Renderer> m_pRenderer;

	static void InputCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
};
