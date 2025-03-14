#include <jni.h>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <iostream>

extern "C" JNIEXPORT jlong JNICALL Java_org_cambala_window_VulkanWindow_createWindow(JNIEnv* env, jobject obj, jlong instanceHandle, jint width, jint height, jstring title) {
    const char* windowTitle = env->GetStringUTFChars(title, nullptr);

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        return 0;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return 0;
    }

    env->ReleaseStringUTFChars(title, windowTitle);
    return reinterpret_cast<jlong>(window);
}

extern "C" JNIEXPORT jlong JNICALL Java_org_cambala_window_VulkanWindow_createSurface(JNIEnv* env, jobject obj, jlong instanceHandle, jlong windowHandle) {
    VkInstance instance = reinterpret_cast<VkInstance>(instanceHandle);
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(windowHandle);
    VkSurfaceKHR surface;

    if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
        std::cerr << "Failed to create window surface!" << std::endl;
        return 0;
    }

    return reinterpret_cast<jlong>(surface);
}

extern "C" JNIEXPORT jboolean JNICALL Java_org_cambala_window_VulkanWindow_shouldClose(JNIEnv* env, jobject obj) {
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(env->GetLongField(obj, env->GetFieldID(env->GetObjectClass(obj), "handle", "J")));
    return glfwWindowShouldClose(window);
}

extern "C" JNIEXPORT void JNICALL Java_org_cambala_window_VulkanWindow_pollEvents(JNIEnv* env, jobject obj) {
    glfwPollEvents();
}

extern "C" JNIEXPORT void JNICALL Java_org_cambala_window_VulkanWindow_destroy(JNIEnv* env, jobject obj) {
    GLFWwindow* window = reinterpret_cast<GLFWwindow*>(env->GetLongField(obj, env->GetFieldID(env->GetObjectClass(obj), "handle", "J")));
    glfwDestroyWindow(window);
    glfwTerminate();
}