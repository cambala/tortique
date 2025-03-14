package org.cambala.vulkan;

public class VulkanInstance {

    static {
        System.loadLibrary("vulkanjava");
    }

    private long handle;

    public VulkanInstance() {
        this.handle = createInstance();
    }

    private native long createInstance();

    public long getHandle() {
        return handle;
    }
}
