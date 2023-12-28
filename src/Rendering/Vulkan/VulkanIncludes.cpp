#include "Prefix.h"

#define VOLK_IMPLEMENTATION
#include "VulkanIncludes.h"

const char* gore::VkResultToString(VkResult result)
{
#define ENUM_TO_STRING_CASE(x) \
    case x:                    \
        return #x
    switch (result)
    {
        ENUM_TO_STRING_CASE(VK_SUCCESS);
        ENUM_TO_STRING_CASE(VK_NOT_READY);
        ENUM_TO_STRING_CASE(VK_TIMEOUT);
        ENUM_TO_STRING_CASE(VK_EVENT_SET);
        ENUM_TO_STRING_CASE(VK_EVENT_RESET);
        ENUM_TO_STRING_CASE(VK_INCOMPLETE);
        ENUM_TO_STRING_CASE(VK_ERROR_OUT_OF_HOST_MEMORY);
        ENUM_TO_STRING_CASE(VK_ERROR_OUT_OF_DEVICE_MEMORY);
        ENUM_TO_STRING_CASE(VK_ERROR_INITIALIZATION_FAILED);
        ENUM_TO_STRING_CASE(VK_ERROR_DEVICE_LOST);
        ENUM_TO_STRING_CASE(VK_ERROR_MEMORY_MAP_FAILED);
        ENUM_TO_STRING_CASE(VK_ERROR_LAYER_NOT_PRESENT);
        ENUM_TO_STRING_CASE(VK_ERROR_EXTENSION_NOT_PRESENT);
        ENUM_TO_STRING_CASE(VK_ERROR_FEATURE_NOT_PRESENT);
        ENUM_TO_STRING_CASE(VK_ERROR_INCOMPATIBLE_DRIVER);
        ENUM_TO_STRING_CASE(VK_ERROR_TOO_MANY_OBJECTS);
        ENUM_TO_STRING_CASE(VK_ERROR_FORMAT_NOT_SUPPORTED);
        ENUM_TO_STRING_CASE(VK_ERROR_SURFACE_LOST_KHR);
        ENUM_TO_STRING_CASE(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR);
        ENUM_TO_STRING_CASE(VK_SUBOPTIMAL_KHR);
        ENUM_TO_STRING_CASE(VK_ERROR_OUT_OF_DATE_KHR);
        ENUM_TO_STRING_CASE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR);
        ENUM_TO_STRING_CASE(VK_ERROR_VALIDATION_FAILED_EXT);
        ENUM_TO_STRING_CASE(VK_ERROR_INVALID_SHADER_NV);
        default:
            return "Unknown error";
    }
#undef ENUM_TO_STRING_CASE
}