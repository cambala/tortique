#include <jni.h>
#include <cmath>

extern "C" JNIEXPORT jfloat JNICALL Java_org_cambala_utils_MathUtils_clamp(JNIEnv* env, jobject obj, jfloat value, jfloat min, jfloat max) {
    return fmax(min, fmin(max, value));
}