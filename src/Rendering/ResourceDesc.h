#pragma once

#include "ResourcePrefix.h"
#include <glm/glm.hpp>

struct BufferDesc final
{
    const char* debugName = "Noname Vertex_Buffer";
    uint32_t byteSize     = 0;
    BufferUsage usage     = BufferUsage::Vertex;
    MemoryUsage memUsage  = MemoryUsage::GPU;
};

struct TextureDesc final
{
    const char* debugName = "Noname Texture_2D_R8G8B8A8_SRGB";
    TextureType type      = TextureType::Tex2D;
    // use dimentions.z for different texturetypes
    glm::ivec3 dimentions = glm::ivec3(0);
    TextureFormat format  = TextureFormat::R8G8B8A8_SRGB;
    MemoryUsage memUsage  = MemoryUsage::GPU;
    int numMips           = 1;
    int numLayers         = 1;
    int numSamples        = 1;
    uint8_t* data         = nullptr;
};

// TODO: Add more options
// Default values are linear, repeat
struct SamplerDesc final
{
    const char* debugName   = "Noname Sampler";
    SamplerFilter minFilter = SamplerFilter::Linear;
    SamplerFilter magFilter = SamplerFilter::Linear;

    SamplerMipmapMode mipmapMode = SamplerMipmapMode::Linear;

    SamplerAddressMode addressModeU = SamplerAddressMode::Repeat;
    SamplerAddressMode addressModeV = SamplerAddressMode::Repeat;
    SamplerAddressMode addressModeW = SamplerAddressMode::Repeat;
};

struct MaterialDesc final
{
    const char* debugName = "Noname Material";
};

struct ShaderModuleDesc final
{
    const char* debugName = "Noname Shader";
    ShaderStage stage     = ShaderStage::Vertex;
    uint8_t* data         = nullptr;
    uint32_t byteSize     = 0;
    const char* entryFunc = "main";
};
