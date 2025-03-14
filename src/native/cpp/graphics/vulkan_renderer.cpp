#include <jni.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <vector>

extern "C" JNIEXPORT jlong JNICALL Java_org_cambala_graphics_VulkanRenderer_createRenderer(JNIEnv* env, jobject obj, jlong deviceHandle, jlong swapchainHandle, jlong pipelineHandle) {
    VkDevice device = reinterpret_cast<VkDevice>(deviceHandle);
    VkSwapchainKHR swapchain = reinterpret_cast<VkSwapchainKHR>(swapchainHandle);
    VkPipeline pipeline = reinterpret_cast<VkPipeline>(pipelineHandle);

    // Создание командного пула
    VkCommandPool commandPool;
    VkCommandPoolCreateInfo poolInfo = {};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = 0; // Индекс семейства очередей
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
        std::cerr << "Failed to create command pool!" << std::endl;
        return 0;
    }

    // Создание командного буфера
    VkCommandBuffer commandBuffer;
    VkCommandBufferAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) != VK_SUCCESS) {
        std::cerr << "Failed to allocate command buffers!" << std::endl;
        return 0;
    }

    // Возвращаем handle командного буфера
    return reinterpret_cast<jlong>(commandBuffer);
}

extern "C" JNIEXPORT void JNICALL Java_org_cambala_graphics_VulkanRenderer_renderFrame(JNIEnv* env, jobject obj, jlong rendererHandle) {
    VkCommandBuffer commandBuffer = reinterpret_cast<VkCommandBuffer>(rendererHandle);

    // Начало записи команд
    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

    if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS) {
        std::cerr << "Failed to begin recording command buffer!" << std::endl;
        return;
    }

    // Начало рендеринга
    VkRenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderArea.offset = VkOffset2D{0, 0};
    renderPassInfo.renderArea.extent = VkExtent2D{800, 600}; // Размер окна
    VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    // Привязка пайплайна
    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, reinterpret_cast<VkPipeline>(env->GetLongField(obj, env->GetFieldID(env->GetObjectClass(obj), "pipelineHandle", "J"))));

    // Отрисовка треугольника
    vkCmdDraw(commandBuffer, 3, 1, 0, 0);

    // Завершение рендеринга
    vkCmdEndRenderPass(commandBuffer);

    // Завершение записи команд
    if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS) {
        std::cerr << "Failed to record command buffer!" << std::endl;
        return;
    }

    // Отправка командного буфера на выполнение
    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    VkQueue graphicsQueue;
    vkGetDeviceQueue(reinterpret_cast<VkDevice>(env->GetLongField(obj, env->GetFieldID(env->GetObjectClass(obj), "deviceHandle", "J"))), 0, 0, &graphicsQueue);

    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, nullptr) != VK_SUCCESS) {
        std::cerr << "Failed to submit draw command buffer!" << std::endl;
        return;
    }

    std::cout << "Rendered frame!" << std::endl;
}