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
    struct QueueFamilyIndices
    {
        std::optional<uint32_t> graphicsFamily;

        bool isComplete() 
        {
            return graphicsFamily.has_value();
        }
    };

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
    VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
    VkDevice m_Device;
    float m_QueuePriority = 1.f;
    VkQueue m_GraphicsQueue;

    // vulkan methods
    void CreateInstance();
    void SetupDebugMessenger();
    std::vector<const char*> GetRequiredExtensions();

    void PickPhysicalDevice();
    bool IsDeviceSuitable(VkPhysicalDevice device) const;
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) const;

    void CreateLogicalDevice();

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
    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
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
    PickPhysicalDevice();
    CreateLogicalDevice();
}

void RendererVulkan::Cleanup()
{
    vkDestroyDevice(m_Device, nullptr);

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

void RendererVulkan::PickPhysicalDevice()
{
    uint32_t deviceCount{0};
    vkEnumeratePhysicalDevices(m_Instance, &deviceCount, nullptr);
    if (deviceCount <= 0)
        throw std::runtime_error("failed to find GPUs with Vulkan support!");

    std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
    vkEnumeratePhysicalDevices(m_Instance, &deviceCount, physicalDevices.data());

    for (const auto& device : physicalDevices)
    {
        if (IsDeviceSuitable(device))
        {
            m_PhysicalDevice = device;
            break;
        }
    }

    if (m_PhysicalDevice == VK_NULL_HANDLE)
        throw std::runtime_error("failed to find a suitable GPU!");


}

bool RendererVulkan::IsDeviceSuitable(VkPhysicalDevice device) const
{
    QueueFamilyIndices indices = FindQueueFamilies(device);

    return indices.isComplete();
}

RendererVulkan::QueueFamilyIndices RendererVulkan::FindQueueFamilies(VkPhysicalDevice device) const
{
    QueueFamilyIndices indices{};

    uint32_t count{0};
    vkGetPhysicalDeviceQueueFamilyProperties(device, &count, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilies(count);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &count, queueFamilies.data());

    for (int i{0}; i < queueFamilies.size(); ++i) 
    {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
            indices.graphicsFamily = i;

        if (indices.isComplete())
            break;
    }

    return indices;
}

void RendererVulkan::CreateLogicalDevice()
{
    QueueFamilyIndices indices = FindQueueFamilies(m_PhysicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &m_QueuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.pQueueCreateInfos = & queueCreateInfo;
        createInfo.queueCreateInfoCount = 1;
        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledExtensionCount = 0;
        createInfo.enabledLayerCount = 0;
    if (m_EnableValidationLayers) 
    {
        createInfo.enabledLayerCount = static_cast<uint32_t>(m_ValidationLayers.size());
        createInfo.ppEnabledLayerNames = m_ValidationLayers.data();
    }

    if (vkCreateDevice(m_PhysicalDevice, &createInfo, nullptr, &m_Device) != VK_SUCCESS)
        throw std::runtime_error("failed to create logical device!");

    vkGetDeviceQueue(m_Device, indices.graphicsFamily.value(), 0, &m_GraphicsQueue);
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