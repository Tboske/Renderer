#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <backends/imgui_impl_opengl3.h>
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

#pragma region RendererOpengl3
class RendererOpengl3 final : public Renderer::RendererImpl
{
public:
    RendererOpengl3(Renderer* pBaseRenderer)
        : Renderer::RendererImpl(pBaseRenderer)
    {
    }
    virtual ~RendererOpengl3() override = default;
    RendererOpengl3(const RendererOpengl3&) = delete;
    RendererOpengl3(RendererOpengl3&&) noexcept  = delete;
    RendererOpengl3& operator=(const RendererOpengl3&) = delete;
    RendererOpengl3& operator=(RendererOpengl3&&) noexcept  = delete;
    
    virtual void Draw() override;

    virtual void InitImGui() override;
    virtual void DestroyImGui() override;
    virtual void RenderImGui() override;
};

void RendererOpengl3::Draw()
{
    // Rendering
    int display_w, display_h;
    glfwGetFramebufferSize(m_pBaseRenderer->m_pWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    const auto& color = m_pBaseRenderer->m_ClearColor;
    glClearColor(color.x * color.w, color.y * color.w, color.z * color.w, color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // render everything from the scenegraph
    RenderImGui();

    glfwSwapBuffers(m_pBaseRenderer->m_pWindow);
    glfwPollEvents();
}

void RendererOpengl3::InitImGui()
{
    // setup imgui
    const char* glsl_version = "#version 130";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_pBaseRenderer->m_pWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void RendererOpengl3::DestroyImGui()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void RendererOpengl3::RenderImGui()
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

	ImGui::DockSpaceOverViewport(nullptr, ImGuiDockNodeFlags_PassthruCentralNode);
    
    // Rendering
    ImGui::ShowDemoWindow();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}
#pragma endregion



#pragma region Renderer
Renderer::Renderer(RenderType renderType)
    : m_RenderType(renderType)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    m_pWindow = glfwCreateWindow(1280, 720, "Testing Window", NULL, NULL);
    if (!m_pWindow)
        throw "Failed to initialize window";        

    glfwMakeContextCurrent(m_pWindow);
    glfwSwapInterval(1); // enable vsync

    switch (m_RenderType) 
    {
    case RenderType::Opengl3:
        m_pImpl = new RendererOpengl3(this);
        break;
    case RenderType::Vulkan:

        break;
    }

    m_pImpl->InitImGui();
}

Renderer::~Renderer()
{
    m_pImpl->DestroyImGui();

    SafeDelete(m_pImpl);

    glfwDestroyWindow(m_pWindow);
}

void Renderer::Draw()
{
    m_pImpl->Draw();
}
#pragma endregion