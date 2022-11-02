#include "Renderer.h"

#include "render/Window.h"
#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_glfw.h>

class Renderer::RendererImpl
{
public:
    RendererImpl(Renderer* pBaseRenderer)
        : m_pBaseRenderer(pBaseRenderer)
    {
    }
    virtual ~RendererImpl()
    {
        m_pBaseRenderer = nullptr;
    }
    RendererImpl(const RendererImpl&) = delete;
    RendererImpl(RendererImpl&&) noexcept  = delete;
    RendererImpl& operator=(const RendererImpl&) = delete;
    RendererImpl& operator=(RendererImpl&&) noexcept  = delete;    

    virtual void Draw() = 0;
    virtual void InitImGui() = 0;
    virtual void DestroyImGui() = 0;
    virtual void RenderImGui() = 0;

protected:
    Renderer* m_pBaseRenderer;
};


#pragma region RendererVulkan
class RendererVulkan final : public Renderer::RendererImpl
{
public:
    RendererVulkan(Renderer* pBaseRenderer)
        : Renderer::RendererImpl(pBaseRenderer)
    {
    }
    virtual ~RendererVulkan() override = default;
    RendererVulkan(const RendererVulkan&) = delete;
    RendererVulkan(RendererVulkan&&) noexcept  = delete;
    RendererVulkan& operator=(const RendererVulkan&) = delete;
    RendererVulkan& operator=(RendererVulkan&&) noexcept  = delete;
    
    virtual void Draw() override;

    virtual void InitImGui() override;
    virtual void DestroyImGui() override;
    virtual void RenderImGui() override;
};

void RendererVulkan::Draw()
{

}

#pragma region imgui
void RendererVulkan::InitImGui()
{

}

void RendererVulkan::DestroyImGui()
{
    
}

void RendererVulkan::RenderImGui()
{
    
}
#pragma engregion

#pragma endregion


#pragma region Renderer
Renderer::Renderer(Window* pWindow)
    : m_pWindow(pWindow)
{
    m_pImpl = new RendererVulkan(this);

    m_pImpl->InitImGui();
}

Renderer::~Renderer()
{
    m_pImpl->DestroyImGui();

    SafeDelete(m_pImpl);
}

void Renderer::Draw()
{
    m_pImpl->Draw();
}
#pragma endregion