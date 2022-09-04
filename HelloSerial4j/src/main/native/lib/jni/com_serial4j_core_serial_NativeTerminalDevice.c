#include<jni/com_serial4j_core_serial_NativeTerminalDevice.h>
#include<Serial.h>
#include<stdlib.h>
#include<Logger.h>
#include<JniUtils.h>

Terminal::TerminalControl terminalControl;

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_setupJniEnvironment0
  (JNIEnv* env, jclass clazz) {
      return JniUtils::setJniEnv(env);
}

JNIEXPORT void JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_setLoggingEnabled0
  (JNIEnv* env, jobject object) {
    Logger::setLoggingEnabled();
}

JNIEXPORT void JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_setLoggingDisabled0
  (JNIEnv* env, jobject object) {
    Logger::setLoggingDisabled();
}


JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_setReadConfigurationMode0
  (JNIEnv* env, jobject object, jintArray mode, jint timeoutValue, jint minimumBytes) {
    
    const cc_t config[2] = { (cc_t) JniUtils::getIntArrayElement(mode, 0),
                             (cc_t) JniUtils::getIntArrayElement(mode, 1)};

    return terminalControl.setReadConfigurationMode(config, timeoutValue, minimumBytes);
}


JNIEXPORT jintArray JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getReadConfigurationMode0
  (JNIEnv *, jobject) {

}

JNIEXPORT jobjectArray JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getSerialPorts0
  (JNIEnv* env, jobject object) {
    JniUtils::setJniEnv(env);
    int length = *(terminalControl.getDynamicBuffer()->getItemsCount());

    jobjectArray objectArray = JniUtils::createNewArrayFromBuffer(
      java_lang_String, length);

    jobject* objectBuffer = JniUtils::getObjectBufferFromString(terminalControl.getSerialPorts(), length);
    JniUtils::setArrayElements(objectArray, length, objectBuffer);

    return objectArray;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_fetchSerialPorts0
  (JNIEnv* env, jobject object) {
    return terminalControl.fetchSerialPorts();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getReadBuffer0
  (JNIEnv* env, jobject object) {
    return terminalControl.readBuffer[0];
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_setBaudRate0
  (JNIEnv* env, jobject object, jint baudRate) {
    return terminalControl.setBaudRate(baudRate);
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getBaudRate0
  (JNIEnv* env, jobject object) {
    return terminalControl.getBaudRate();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getFileDescriptor0
  (JNIEnv* env, jobject object) {
    return *(terminalControl.getPortFileDescriptor());
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_initTermios0
  (JNIEnv* env, jobject object) {
    return terminalControl.initTermios();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_openPort0
  (JNIEnv* env, jobject object, jstring strBuffer) {
    return *(terminalControl.openPort(env->GetStringUTFChars(strBuffer, 0)));
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_writeData0
  (JNIEnv* env, jobject object, jint buffer) {
    terminalControl.writeBuffer[0] = buffer;
    return terminalControl.writeData();
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_readData0
  (JNIEnv* env, jobject object) {
    return terminalControl.readData();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_closePort0
  (JNIEnv* env, jobject object) {
    return terminalControl.closePort();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getErrno0
  (JNIEnv* env, jobject object) {
    return *(terminalControl.getErrno());
}