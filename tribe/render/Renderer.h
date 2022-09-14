#pragma once
#include "../pch.h"

enum class RenderType
{
    Vulkan,
    Opengl3
};

class GLFWwindow;
class Renderer final
{
public:
    Renderer();
    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) noexcept  = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer& operator=(Renderer&&) noexcept  = delete;
    
    GLFWwindow* const GetWindow() const { return m_pWindow; }
    void Draw();

protected:
    GLFWwindow* m_pWindow;

    glm::fvec4 m_ClearColor{0.45f, 0.55f, 0.60f, 1.00f};

private:
    class RendererImpl;
    RendererImpl* m_pImpl;

    // we need to friend all rendererImpl for them to be able to inherit from RendererImpl
    friend class RendererOpengl3;
};