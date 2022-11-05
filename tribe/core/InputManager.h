#pragma once
#include "pch.h"
#include "utils/Singleton.h"

class GLFWwindow;

class InputManager final : public Singleton<InputManager>
{
public:
    ~InputManager() = default;

    static void Init(GLFWwindow* pWindow);

    // add method for adding inputactions

    static void InputCallBack(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
private:
    friend class Singleton<InputManager>;
    InputManager() = default;


};