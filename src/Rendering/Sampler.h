#pragma once

#include "Prefix.h"
#include "Handle.h"

#include "Graphics/Vulkan/VulkanIncludes.h"

namespace gore::gfx
{
struct Sampler
{
    vk::Sampler sampler = VK_NULL_HANDLE;
};
} // namespace gore::gfx