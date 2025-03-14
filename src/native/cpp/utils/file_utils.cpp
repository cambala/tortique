#include <jni.h>
#include <fstream>
#include <vector>
#include <iostream>

extern "C" JNIEXPORT jbyteArray JNICALL Java_org_cambala_utils_FileUtils_readFile(JNIEnv* env, jobject obj, jstring filePath) {
    const char* path = env->GetStringUTFChars(filePath, nullptr);

    std::ifstream file(path, std::ios::ate | std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return nullptr;
    }

    size_t fileSize = (size_t) file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    jbyteArray result = env->NewByteArray(fileSize);
    env->SetByteArrayRegion(result, 0, fileSize, reinterpret_cast<jbyte*>(buffer.data()));

    env->ReleaseStringUTFChars(filePath, path);
    return result;
}