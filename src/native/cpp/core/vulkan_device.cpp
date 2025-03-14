#include <jni.h>
#include <vulkan/vulkan.h>
#include <vector>
#include <iostream>

extern "C" JNIEXPORT jlong JNICALL Java_org_cambala_core_VulkanPhysicalDevice_findPhysicalDevice(JNIEnv* env, jobject obj, jlong instanceHandle) {
    VkInstance instance = reinterpret_cast<VkInstance>(instanceHandle);
    VkPhysicalDevice physicalDevice = nullptr;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        std::cerr << "No Vulkan-compatible devices found!" << std::endl;
        return 0;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            physicalDevice = device;
            break;
        }
    }

    if (physicalDevice == nullptr) {
        std::cerr << "No suitable GPU found!" << std::endl;
        return 0;
    }

    return reinterpret_cast<jlong>(physicalDevice);
}

extern "C" JNIEXPORT jlong JNICALL Java_org_cambala_core_VulkanLogicalDevice_createLogicalDevice(JNIEnv* env, jobject obj, jlong physicalDeviceHandle) {
    VkPhysicalDevice physicalDevice = reinterpret_cast<VkPhysicalDevice>(physicalDeviceHandle);
    VkDevice logicalDevice;

    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = 0; // Индекс семейства очередей
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pQueueCreateInfos = &queueCreateInfo;

    if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice) != VK_SUCCESS) {
        std::cerr << "Failed to create logical device!" << std::endl;
        return 0;
    }

    return reinterpret_cast<jlong>(logicalDevice);
}