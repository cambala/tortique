package org.cambala.graphics;

public class VulkanPipeline {
    private final long handle;

    public VulkanPipeline(long deviceHandle, long renderPassHandle) {
        this.handle = createPipeline(deviceHandle, renderPassHandle);
    }

    private native long createPipeline(long deviceHandle, long renderPassHandle);

    public long getHandle() {
        return handle;
    }
}
