package org.cambala.core;

public class VulkanPhysicalDevice {
    private final long handle;

    public VulkanPhysicalDevice(long instanceHandle) {
        this.handle = findPhysicalDevice(instanceHandle);
    }

    private native long findPhysicalDevice(long instanceHandle);

    public long getHandle() {
        return handle;
    }
}