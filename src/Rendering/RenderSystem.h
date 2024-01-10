#pragma once

#include "Core/System.h"

#include "Graphics/Graphics.h"

#include "Graphics/Vulkan/VulkanIncludes.h"
#include "Graphics/Vulkan/VulkanExtensions.h"

namespace gore
{

class Window;

class RenderSystem final : System
{
public:
    explicit RenderSystem(App* app);
    ~RenderSystem() override;

    NON_COPYABLE(RenderSystem);

    void Initialize() override;
    void Update() override;
    void Shutdown() override;

    void OnResize(Window* window, int width, int height);

private:
    // Instance
    gfx::Instance m_Instance;

    // Device
    gfx::Device m_Device;

    // Surface & Swapchain
    vk::raii::SurfaceKHR m_Surface;
    vk::raii::SwapchainKHR m_Swapchain;
    vk::SurfaceFormatKHR m_SurfaceFormat;
    vk::Extent2D m_SurfaceExtent;

    uint32_t m_SwapchainImageCount;

    std::vector<vk::Image> m_SwapchainImages;
    std::vector<vk::raii::ImageView> m_SwapchainImageViews;
    std::vector<vk::raii::Semaphore> m_RenderFinishedSemaphores;
    std::vector<vk::raii::Fence> m_ImageAcquiredFences;
    std::vector<vk::raii::Fence> m_InFlightFences;

    uint32_t m_CurrentSwapchainImageIndex;

    // Shader
    vk::raii::ShaderModule m_CubeVertexShader;
    std::string m_CubeVertexShaderEntryPoint;
    vk::raii::ShaderModule m_CubeFragmentShader;
    std::string m_CubeFragmentShaderEntryPoint;

    // Render pass
    vk::raii::RenderPass m_RenderPass;

    // Pipeline
    vk::raii::PipelineLayout m_PipelineLayout;
    vk::raii::Pipeline m_Pipeline;

    // Framebuffer
    std::vector<vk::raii::Framebuffer> m_Framebuffers;

    // Queue
    vk::raii::Queue m_GraphicsQueue;
    uint32_t m_GraphicsQueueFamilyIndex;
    vk::raii::Queue m_PresentQueue;
    uint32_t m_PresentQueueFamilyIndex;

    // Command Pool & Command Buffer
    std::vector<vk::raii::CommandPool> m_CommandPools;
    std::vector<vk::raii::CommandBuffer> m_CommandBuffers;

    // Depth buffer
    vk::Image m_DepthImage;
    VmaAllocation m_DepthImageAllocation;
    vk::raii::ImageView m_DepthImageView;

private:
    void CreateSurface();
    void CreateSwapchain(uint32_t imageCount, uint32_t width, uint32_t height);
    void CreateDepthBuffer();
    void LoadShader(const std::string& name, const std::string& vertexEntryPoint, const std::string& fragmentEntryPoint);
    void CreateRenderPass();
    void CreatePipeline();
    void CreateFramebuffers();
    void GetQueues();
    void CreateCommandPools();

    [[nodiscard]] const gfx::PhysicalDevice& GetBestDevice(const std::vector<gfx::PhysicalDevice>& devices) const;
};

} // namespace gore
