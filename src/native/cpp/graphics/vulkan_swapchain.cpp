#include <jni.h>
#include <vulkan/vulkan.h>
#include <iostream>

extern "C" JNIEXPORT jlong JNICALL Java_org_cambala_graphics_VulkanSwapchain_createSwapchain(JNIEnv* env, jobject obj, jlong deviceHandle, jlong surfaceHandle, jint width, jint height) {
    VkDevice device = reinterpret_cast<VkDevice>(deviceHandle);
    VkSurfaceKHR surface = reinterpret_cast<VkSurfaceKHR>(surfaceHandle);
    VkSwapchainKHR swapchain;

    VkSwapchainCreateInfoKHR createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;
    createInfo.minImageCount = 2; // Двойная буферизация
    createInfo.imageFormat = VK_FORMAT_B8G8R8A8_UNORM;
    createInfo.imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
    createInfo.imageExtent = {static_cast<uint32_t>(width), static_cast<uint32_t>(height)};
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    createInfo.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;
    createInfo.clipped = VK_TRUE;

    if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapchain) != VK_SUCCESS) {
        std::cerr << "Failed to create swapchain!" << std::endl;
        return 0;
    }

    return reinterpret_cast<jlong>(swapchain);
}