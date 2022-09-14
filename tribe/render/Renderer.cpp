#include "Renderer.h"

#include "GLFW/glfw3.h"
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>


Renderer::Renderer()
{    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    m_pWindow = glfwCreateWindow(1280, 720, "Testing Window", NULL, NULL);
    if (!m_pWindow)
        throw "Failed to initialize window";        

    glfwMakeContextCurrent(m_pWindow);
    glfwSwapInterval(1); // enable vsync


    InitImGui();
}

Renderer::~Renderer()
{
    glfwDestroyWindow(m_pWindow);

    DestroyImGui();
}

void Renderer::Update()
{
    // Rendering
    int display_w, display_h;
    glfwGetFramebufferSize(m_pWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);

    glClearColor(m_ClearColor.x * m_ClearColor.w, m_ClearColor.y * m_ClearColor.w, m_ClearColor.z * m_ClearColor.w, m_ClearColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // render everything from the scenegraph
    RenderImGui();

    glfwSwapBuffers(m_pWindow);
    glfwPollEvents();
}


void Renderer::InitImGui()
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
    ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void Renderer::DestroyImGui()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Renderer::RenderImGui()
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