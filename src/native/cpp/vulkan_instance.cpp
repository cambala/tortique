#include <jni.h>
#include <vulkan/vulkan.h>

extern "C" JNIEXPORT jlong JNICALL Java_org_cambala_vulkan_VulkanInstance_createInstance(JNIEnv* env, jobject obj) {
    VkInstance instance;
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Vulkan Java";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        return 0; // Ошибка
    }

    return reinterpret_cast<jlong>(instance);
}