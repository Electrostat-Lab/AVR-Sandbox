#include<com_serial4j_core_serial_SerialPort.h>
#include<Serial.h>
#include<stdlib.h>

Terminal::TerminalControl terminalControl;
int writeBuffer[1];

JNIEXPORT jobjectArray JNICALL Java_com_serial4j_core_serial_SerialPort_getSerialPorts0
  (JNIEnv* env, jobject object) {
    return NULL;
}


JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_SerialPort_fetchSerialPorts0
  (JNIEnv* env, jobject object) {
    return terminalControl.fetchSerialPorts();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_SerialPort_getReadBuffer0
  (JNIEnv* env, jobject object) {
    return terminalControl.readBuffer[0];
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_SerialPort_setBaudRate0
  (JNIEnv* env, jobject object, jint baudRate) {
    terminalControl.setBaudRate(baudRate);
    return 0;
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_SerialPort_getBaudRate0
  (JNIEnv* env, jobject object) {
    return terminalControl.getBaudRate();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_SerialPort_getFileDescriptor0
  (JNIEnv* env, jobject object) {
    return terminalControl.getPortFileDescriptor();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_SerialPort_initTermios0
  (JNIEnv* env, jobject object) {
    return terminalControl.initTermios();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_SerialPort_openPort0
  (JNIEnv* env, jobject object, jstring strBuffer) {
    return terminalControl.openPort(env->GetStringUTFChars(strBuffer, 0));
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_serial_SerialPort_writeData0
  (JNIEnv* env, jobject object, jint buffer) {
    terminalControl.writeBuffer[0] = buffer;
    return terminalControl.writeData();
}

JNIEXPORT jlong JNICALL Java_com_serial4j_core_serial_SerialPort_readData0
  (JNIEnv* env, jobject object) {
    return terminalControl.readData();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_SerialPort_closePort0
  (JNIEnv* env, jobject object) {
    return terminalControl.closePort();
}

JNIEXPORT jint JNICALL Java_com_serial4j_core_serial_SerialPort_getErrno0
  (JNIEnv* env, jobject object) {
    return terminalControl.getErrno();
}