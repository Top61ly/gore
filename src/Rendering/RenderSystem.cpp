#include "Prefix.h"

#include "RenderSystem.h"

#include "Core/Log.h"
#include "Rendering/Vulkan/VulkanInstance.h"
#include "Rendering/Vulkan/VulkanDevice.h"

#include <iostream>
#include <vector>
#include <algorithm>

namespace gore
{

static RenderSystem* g_RenderSystem = nullptr;

RenderSystem::RenderSystem(gore::App* app) :
    System(app),
    m_VulkanInstance(nullptr),
    m_VulkanDevice(nullptr)
{
    g_RenderSystem = this;
}

RenderSystem::~RenderSystem()
{
    g_RenderSystem = nullptr;
}

void RenderSystem::Initialize()
{
    m_VulkanInstance = new VulkanInstance(m_App);
    bool result      = m_VulkanInstance->Initialize();

    std::vector<VulkanPhysicalDevice> physicalDevices = m_VulkanInstance->GetPhysicalDevices();
    std::sort(physicalDevices.begin(), physicalDevices.end(), [](const VulkanPhysicalDevice& a, const VulkanPhysicalDevice& b)
              { return a.Score() > b.Score(); });

    m_VulkanDevice = new VulkanDevice(m_VulkanInstance, physicalDevices[0]);
}

void RenderSystem::Update()
{
}

void RenderSystem::Shutdown()
{
    delete m_VulkanDevice;

    bool result = m_VulkanInstance->Shutdown();
    delete m_VulkanInstance;
}

void RenderSystem::OnResize(Window* window, int width, int height)
{
}

} // namespace gore
