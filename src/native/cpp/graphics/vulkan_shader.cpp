#include <jni.h>
#include <vulkan/vulkan.h>
#include <fstream>
#include <vector>
#include <iostream>

extern "C" JNIEXPORT jlong JNICALL Java_org_cambala_graphics_VulkanShader_createShaderModule(JNIEnv* env, jobject obj, jlong deviceHandle, jstring shaderPath) {
    VkDevice device = reinterpret_cast<VkDevice>(deviceHandle);
    const char* path = env->GetStringUTFChars(shaderPath, nullptr);

    std::ifstream file(path, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open shader file: " << path << std::endl;
        return 0;
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> code(fileSize);
    file.seekg(0);
    file.read(code.data(), fileSize);
    file.close();

    VkShaderModule shaderModule;
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        std::cerr << "Failed to create shader module!" << std::endl;
        return 0;
    }

    env->ReleaseStringUTFChars(shaderPath, path);
    return reinterpret_cast<jlong>(shaderModule);
}