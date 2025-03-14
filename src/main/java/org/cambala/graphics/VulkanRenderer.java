package org.cambala.graphics;

public class VulkanRenderer {
    private final long handle;
    private final long deviceHandle;
    private final long pipelineHandle;

    public VulkanRenderer(long deviceHandle, long swapchainHandle, long pipelineHandle) {
        this.deviceHandle = deviceHandle;
        this.pipelineHandle = pipelineHandle;
        this.handle = createRenderer(deviceHandle, swapchainHandle, pipelineHandle);
    }

    private native long createRenderer(long deviceHandle, long swapchainHandle, long pipelineHandle);

    public void render() {
        renderFrame(handle);
    }

    private native void renderFrame(long rendererHandle);
}