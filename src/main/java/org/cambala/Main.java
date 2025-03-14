package org.cambala;

import org.cambala.vulkan.VulkanInstance;

public class Main {
    public static void main(String[] args) {
        VulkanInstance instance = new VulkanInstance();
        System.out.println("Vulkan instance created: " + instance.getHandle());
    }
}