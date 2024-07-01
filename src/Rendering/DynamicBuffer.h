#pragma once
#include "Prefix.h"

#include "Buffer.h"

#include "Graphics/Vulkan/VulkanIncludes.h"

namespace gore::gfx
{
struct DynamicBufferDesc
{
    const char* debugName = "Noname DynamicBuffer";
    Handle<Buffer> buffer = {};
    uint32_t offset       = 0;
};

struct DynamicBuffer
{
    vk::DescriptorSet set;
};

using DynamicBufferHandle = Handle<DynamicBuffer>;

} // namespace gore::gfx