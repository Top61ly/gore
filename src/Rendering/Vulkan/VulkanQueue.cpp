#include "Prefix.h"

#include "VulkanQueue.h"
#include "VulkanDevice.h"
#include "VulkanSwapchain.h"
#include "VulkanSynchronization.h"

#include "Core/Log.h"

namespace gore
{

VulkanQueue::VulkanQueue(VulkanDevice* device, uint32_t familyIndex, uint32_t queueIndex, VkQueue queue, VkQueueFlags flags, bool presentable) :
    m_Device(device),
    m_Queue(queue),
    m_FamilyIndex(familyIndex),
    m_QueueIndex(queueIndex),
    m_Flags(flags),
    m_Presentable(presentable)
{
    LOG_STREAM(DEBUG) << "Created Vulkan Queue in family " << familyIndex << " with index " << queueIndex << std::endl;
}

VulkanQueue::~VulkanQueue()
{
}

bool VulkanQueue::IsCapableOf(VulkanQueueType type) const
{
    return IsCapableOf(m_Flags, m_Presentable, type);
}

bool VulkanQueue::IsCapableOf(VkQueueFlags flags, bool presentable, VulkanQueueType type)
{
    switch (type)
    {
        case VulkanQueueType::Graphics:
            return (flags & VK_QUEUE_GRAPHICS_BIT) != 0;
        case VulkanQueueType::Compute:
            return (flags & VK_QUEUE_COMPUTE_BIT) != 0;
        case VulkanQueueType::Transfer:
            return (flags & VK_QUEUE_TRANSFER_BIT) != 0;
        case VulkanQueueType::SparseBinding:
            return (flags & VK_QUEUE_SPARSE_BINDING_BIT) != 0;
#ifdef VK_KHR_video_decode_queue
        case VulkanQueueType::VideoDecode:
            return (flags & VK_QUEUE_VIDEO_DECODE_BIT_KHR) != 0;
#endif
#if defined(VK_KHR_video_encode_queue) && defined(VK_ENABLE_BETA_EXTENSIONS)
        case VulkanQueueType::VideoEncode:
            return (flags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR) != 0;
#endif
        case VulkanQueueType::Present:
            return presentable;
        default:
            return false;
    }
}

int VulkanQueue::QueueFlagBitCount(VkQueueFlags flags, bool presentable)
{
    int count = 0;

    if (flags & VK_QUEUE_GRAPHICS_BIT)
        count++;
    if (flags & VK_QUEUE_COMPUTE_BIT)
        count++;
    if (flags & VK_QUEUE_TRANSFER_BIT)
        count++;
    if (flags & VK_QUEUE_SPARSE_BINDING_BIT)
        count++;
#ifdef VK_KHR_video_decode_queue
    if (flags & VK_QUEUE_VIDEO_DECODE_BIT_KHR)
        count++;
#endif
#if defined(VK_KHR_video_encode_queue) && defined(VK_ENABLE_BETA_EXTENSIONS)
    if (flags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR)
        count++;
#endif
    if (presentable)
        count++;

    return count;
}

std::mutex& VulkanQueue::GetMutex() const
{
    return *m_Device->m_QueueMutexes[m_FamilyIndex][m_QueueIndex];
}

void VulkanQueue::Present(VulkanSwapchain* swapchain, const std::vector<VulkanSemaphore*>& waitSemaphores)
{
    if (!IsCapableOf(VulkanQueueType::Present))
    {
        LOG(ERROR, "Vulkan queue is not capable of presenting\n");
        return;
    }

    uint32_t imageIndex = swapchain->GetCurrentBufferIndex();
    VkSwapchainKHR swapchainHandle = swapchain->Get();

    std::vector<VkSemaphore> waitSemaphoreHandles(waitSemaphores.size());
    for (size_t i = 0; i < waitSemaphores.size(); i++)
    {
        waitSemaphoreHandles[i] = waitSemaphores[i]->Get();
    }

    VkResult res;

    VkPresentInfoKHR presentInfo{
        .sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
        .pNext = VK_NULL_HANDLE,
        .waitSemaphoreCount = static_cast<uint32_t>(waitSemaphoreHandles.size()),
        .pWaitSemaphores = waitSemaphoreHandles.data(),
        .swapchainCount = 1,
        .pSwapchains = &swapchainHandle,
        .pImageIndices = &imageIndex,
        .pResults = &res
    };

    {
        std::lock_guard<std::mutex> lock(GetMutex());
        res = m_Device->API.vkQueuePresentKHR(m_Queue, &presentInfo);
    }

    VK_CHECK_RESULT(res);

    if (res == VK_ERROR_OUT_OF_DATE_KHR || res == VK_SUBOPTIMAL_KHR)
    {
        LOG(DEBUG, "Vulkan swapchain is out of date or suboptimal\n");
        swapchain->Recreate();
    }

    swapchain->AcquireNextImageIndex();
}

} // namespace gore