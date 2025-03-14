package org.cambala.core;

public class VulkanLogicalDevice {
    private final long handle;

    public VulkanLogicalDevice(long physicalDeviceHandle) {
        this.handle = createLogicalDevice(physicalDeviceHandle);
    }

    private native long createLogicalDevice(long physicalDeviceHandle);

    public long getHandle() {
        return handle;
    }
}