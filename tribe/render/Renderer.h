#pragma once
#include "pch.h"

class Window;
class Renderer final
{
public:
    Renderer(Window* pWindow);
    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) noexcept  = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer& operator=(Renderer&&) noexcept  = delete;
    
    void Draw();

protected:
    Window* m_pWindow = nullptr;

    glm::fvec4 m_ClearColor{0.45f, 0.55f, 0.60f, 1.00f};

private:
    class RendererImpl;
    RendererImpl* m_pImpl;


    // we need to friend all rendererImpl for them to be able to inherit from RendererImpl
    friend class RendererVulkan;
};