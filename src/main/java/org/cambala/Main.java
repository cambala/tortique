package org.cambala;

import org.cambala.core.VulkanInstance;
import org.cambala.core.VulkanLogicalDevice;
import org.cambala.core.VulkanPhysicalDevice;
import org.cambala.graphics.VulkanPipeline;
import org.cambala.graphics.VulkanRenderer;
import org.cambala.graphics.VulkanSwapchain;
import org.cambala.window.VulkanWindow;

public class Main {
    public static void main(String[] args) {
        VulkanInstance instance = new VulkanInstance();
        VulkanPhysicalDevice physicalDevice = new VulkanPhysicalDevice(instance.getHandle());
        VulkanLogicalDevice logicalDevice = new VulkanLogicalDevice(physicalDevice.getHandle());

        VulkanWindow window = new VulkanWindow(instance.getHandle(), 800, 600, "Vulkan Window");
        VulkanSwapchain swapchain = new VulkanSwapchain(logicalDevice.getHandle(), window.getSurfaceHandle(), 800, 600);

        VulkanPipeline pipeline = new VulkanPipeline(logicalDevice.getHandle(), 0); // Заглушка для renderPass
        VulkanRenderer renderer = new VulkanRenderer(logicalDevice.getHandle(), swapchain.getHandle(), pipeline.getHandle());

        while (!window.shouldClose()) {
            renderer.render();
            window.pollEvents();
        }

        window.destroy();
    }
}