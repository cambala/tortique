package org.cambala.window;

public class VulkanWindow {
    private final long handle;
    private final long surfaceHandle;

    public VulkanWindow(long instanceHandle, int width, int height, String title) {
        this.handle = createWindow(instanceHandle, width, height, title);
        this.surfaceHandle = createSurface(instanceHandle, handle);
    }

    private native long createWindow(long instanceHandle, int width, int height, String title);
    private native long createSurface(long instanceHandle, long windowHandle);

    public native boolean shouldClose();
    public native void pollEvents();
    public native void destroy();

    public long getHandle() {
        return handle;
    }

    public long getSurfaceHandle() {
        return surfaceHandle;
    }
}
