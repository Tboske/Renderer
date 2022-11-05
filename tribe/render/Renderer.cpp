#include "Renderer.h"

#include <GLFW/glfw3.h>
#include <backends/imgui_impl_vulkan.h>
#include <backends/imgui_impl_glfw.h>

#pragma region RendererBaseImpl
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
    // reference to base renderer for settings that apply to all implementations
    Renderer* m_pBaseRenderer;
};
#pragma endregion

class RendererVulkan final : public Renderer::RendererImpl
{
public:
    RendererVulkan(Renderer* pBaseRenderer)
        : Renderer::RendererImpl(pBaseRenderer)
    {
        Initialize();
    }
    virtual ~RendererVulkan() override
    {
        Cleanup();
    }
    RendererVulkan(const RendererVulkan&) = delete;
    RendererVulkan(RendererVulkan&&) noexcept  = delete;
    RendererVulkan& operator=(const RendererVulkan&) = delete;
    RendererVulkan& operator=(RendererVulkan&&) noexcept  = delete;
    
    virtual void Draw() override {};

    virtual void InitImGui() override {};
    virtual void DestroyImGui() override {};
    virtual void RenderImGui() override {};

private:
    void Initialize();
    void Cleanup();

    // vulkan variables
    VkInstance m_Instance;
    VkDebugUtilsMessengerEXT m_DebugMessenger;

    // vulkan methods
    void CreateInstance();
    void SetupDebugMessenger();

    std::vector<const char*> GetRequiredExtensions();
#ifdef NDEBUG
    const bool m_EnableValidationLayers = false;
#else
    const std::vector<const char*> m_ValidationLayers = {"VK_LAYER_KHRONOS_validation"};
    constexpr static bool m_EnableValidationLayers = true;
    bool CheckValidationLayerSupport() const;
#endif
};

#pragma region DebugVulkan
static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT messageType,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
    void* pUserData) 
{
    spdlog::error("Validation layer: {}", pCallbackData->pMessage);

    return VK_FALSE;
}
VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) 
{
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func)
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    else
        return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) 
{
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func)
        func(instance, debugMessenger, pAllocator);
}

void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) 
{
    createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = DebugCallback;
}
#pragma endregion

void RendererVulkan::Initialize()
{
    CreateInstance();
    SetupDebugMessenger();
}

void RendererVulkan::Cleanup()
{
    if (m_EnableValidationLayers)
        DestroyDebugUtilsMessengerEXT(m_Instance, m_DebugMessenger, nullptr);

    vkDestroyInstance(m_Instance, nullptr);
}

void RendererVulkan::CreateInstance()
{
    if (m_EnableValidationLayers && !CheckValidationLayerSupport())
        throw std::runtime_error("validation layers requested, but not available!");

    VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;


    auto extensions = GetRequiredExtensions();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{}; // needs to keep existing until vkCreateInstance gets called
    VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = nullptr;
    if (m_EnableValidationLayers)
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
        createInfo.ppEnabledLayerNames = m_ValidationLayers.data();

        PopulateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = &debugCreateInfo;
    }
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();


    if (vkCreateInstance(&createInfo, nullptr, &m_Instance) != VK_SUCCESS)
        throw std::runtime_error("Failed to create Vulkan instance!");    
}

void RendererVulkan::SetupDebugMessenger()
{
    if (!m_EnableValidationLayers)
        return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    PopulateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(m_Instance, &createInfo, nullptr, &m_DebugMessenger) != VK_SUCCESS)
        throw std::runtime_error("failed to set up debug messenger!");
}

bool RendererVulkan::CheckValidationLayerSupport() const
{
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layername : m_ValidationLayers)
    {
        for (const VkLayerProperties& layerProperties : availableLayers )
        {
            if (strcmp(layername, layerProperties.layerName) == 0)
                return true;
        }
    }

    return false;
}

std::vector<const char*> RendererVulkan::GetRequiredExtensions() 
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

    if (m_EnableValidationLayers)
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    return extensions;
}


#pragma region Renderer
Renderer::Renderer(GLFWwindow* pWindow)
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