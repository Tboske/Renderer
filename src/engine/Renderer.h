#pragma once
#include "../pch.h"
#include <GLFW/glfw3.h>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool IsRunning();
    void Update();

    GLFWwindow* const GetWindow() const { return m_pWindow; }

private:
    GLFWwindow* m_pWindow;

    glm::fvec4 m_ClearColor{0.45f, 0.55f, 0.60f, 1.00f};

    void InitImGui();
    void DestroyImGui();
    void RenderImGui();
};