/**
 * @file com_serial4j_core_serial_NativeTerminalDevice.c
 * @author pavl_g.
 * @brief Instantiates a native interface of Serial4j API for the java programming language.
 * @version 0.1
 * @date 2022-09-06
 * 
 * @copyright 
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Scrappers Team, The AVR-Sandbox Project, Serial4j API.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include<jni/com_serial4j_core_serial_NativeTerminalDevice.h>
#include<TerminalDevice.h>
#include<stdlib.h>
#include<Logger.h>
#include<JniUtils.h>
#include<DynamicBuffer.h>

struct Terminal::TerminalDevice terminalDevice;
struct Terminal::TerminalDevice terminalDevice0;
/** Define read buffers for different types of read [BLOCK_READ] and [SINGLE_CHAR_READ] */
const char** strBuffer = (const char**) calloc(1, sizeof(const char*));
int* intBuffer = (int*) calloc(1, sizeof(int));

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

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_setTerminalControlFlag
  (JNIEnv* env, jobject object, jlong flag) {
    return terminalDevice.setTerminalControlFlag((jlong) flag);
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_setTerminalLocalFlag
  (JNIEnv* env, jobject object, jlong flag) {
    return terminalDevice.setTerminalLocalFlag((jlong) flag);
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_setTerminalInputFlag
  (JNIEnv* env, jobject object, jlong flag) {
    return terminalDevice.setTerminalInputFlag((jlong) flag);
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_setTerminalOutputFlag
  (JNIEnv* env, jobject object, jlong flag) {
    return terminalDevice.setTerminalOutputFlag((jlong) flag);
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getTerminalControlFlag
  (JNIEnv* env, jobject object) {
    return (jlong) terminalDevice.getTerminalControlFlag();
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getTerminalLocalFlag
  (JNIEnv* env, jobject object) {
    return (jlong) terminalDevice.getTerminalLocalFlag();
} 

JNIEXPORT jlong JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getTerminalInputFlag
  (JNIEnv* env, jobject object) {
    return (jlong) terminalDevice.getTerminalInputFlag();
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getTerminalOutputFlag
  (JNIEnv* env, jobject object) {
    return (jlong) terminalDevice.getTerminalOutputFlag();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_setReadConfigurationMode0
  (JNIEnv* env, jobject object, jintArray mode, jint timeoutValue, jint minimumBytes) {
    
    const cc_t config[READ_CONFIG_SIZE] = { (cc_t) JniUtils::getIntArrayElement(mode, 0),
                             (cc_t) JniUtils::getIntArrayElement(mode, 1)};

    return terminalDevice.setReadConfigurationMode(config, timeoutValue, minimumBytes);
}

JNIEXPORT void JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_setIOFlags
  (JNIEnv* env, jobject object, jint flags) {
    terminalDevice.setIOFlags(&flags);
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getIOFlags
  (JNIEnv* env, jobject object) {
    return *(terminalDevice.getIOFlags());
}

JNIEXPORT jintArray JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getReadConfigurationMode0
  (JNIEnv* env, jobject object) {
    const cc_t* readConfigBuffer = terminalDevice.getReadConfigurationMode();
    return JniUtils::getIntArrayFromBuffer((int*) readConfigBuffer, READ_CONFIG_SIZE);
}

JNIEXPORT jobjectArray JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getSerialPorts0
  (JNIEnv* env, jobject object) {
    JniUtils::setJniEnv(env);
    int length = *(terminalDevice.getDynamicBuffer()->getItemsCount());

    jobjectArray objectArray = JniUtils::createNewArrayFromBuffer(
      java_lang_String, length);

    jobject* objectBuffer = JniUtils::getObjectBufferFromString(terminalDevice.getSerialPorts(), length);
    JniUtils::setArrayElements(objectArray, length, objectBuffer);

    return objectArray;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_fetchSerialPorts0
  (JNIEnv* env, jobject object) {
    return terminalDevice.fetchSerialPorts();
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_writeData0
  (JNIEnv* env, jobject object, jint buffer) {
    return terminalDevice.writeData(&buffer, 1);
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_readData0
  (JNIEnv* env, jobject object) {
    return terminalDevice.readData((void*) intBuffer, 1);
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getReadBuffer0
  (JNIEnv* env, jobject object) {
    return *intBuffer;
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_writeBuffer0
  (JNIEnv* env, jobject object, jstring string, jint length) {
    const char* buffer = JniUtils::getBufferFromString(string);
    int state = terminalDevice.writeData(buffer, length);
    free((void*) buffer);
    buffer = NULL;
    return state;
}

JNIEXPORT jstring JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_readBuffer0
  (JNIEnv* env, jobject object) {
    int length = terminalDevice.tty.c_cc[VMIN];
    if (terminalDevice.readData((void*) *strBuffer, length) <= 0) {
        return NULL;
    }
    return JniUtils::getStringFromBuffer(*strBuffer);
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_setBaudRate0
  (JNIEnv* env, jobject object, jint baudRate) {
    return terminalDevice.setBaudRate(baudRate);
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getBaudRate0
  (JNIEnv* env, jobject object) {
    return terminalDevice.getBaudRate();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getFileDescriptor0
  (JNIEnv* env, jobject object) {
    return *(terminalDevice.getPortFileDescriptor());
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_initTermios0
  (JNIEnv* env, jobject object) {
    return terminalDevice.initTermios();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_openPort0
  (JNIEnv* env, jobject object, jstring strBuffer) {
    return *(terminalDevice.openPort(env->GetStringUTFChars(strBuffer, 0)));
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_closePort0
  (JNIEnv* env, jobject object) {
    return terminalDevice.closePort();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_NativeTerminalDevice_getErrno0
  (JNIEnv* env, jobject object) {
    return *(terminalDevice.getErrno());
}