package org.cambala.graphics;

public class VulkanSwapchain {
    private final long handle;

    public VulkanSwapchain(long deviceHandle, long surfaceHandle, int width, int height) {
        this.handle = createSwapchain(deviceHandle, surfaceHandle, width, height);
    }

    private native long createSwapchain(long deviceHandle, long surfaceHandle, int width, int height);

    public long getHandle() {
        return handle;
    }
}