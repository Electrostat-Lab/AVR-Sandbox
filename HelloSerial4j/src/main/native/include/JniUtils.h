/**
 * @file JniUtils.util
 * @author pavl_g.
 * @brief Java Native Interface Utility methods for jni java 8 and invocation api.
 * @version 0.1
 * @date 2022-08-28
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
#ifndef JNI_UTILS 
#define JNI_UTILS 

#include<jni.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<ErrnoUtils.h>

#define CONSTRUCTOR ((const char*) "<init>")
#define STATIC_INIT ((const char*) "<clinit>")

#define NON_PARAMTERIZED_VOID_SIG ((const char*) "()V")
#define NON_PARAMETERIZED_INT_SIG ((const char*) "()I")
#define NON_PARAMETERIZED_STRING_SIG ((const char*) "()[Ljava/lang/String;")
#define NON_PARAMETERIZED_LONG_SIG ((const char*) "()J")

#define java_lang_String ((const char*) "java/lang/String")
#define java_io_IOException ((const char*) "java/io/IOException")
#define java_io_InputStream ((const char*) "java/io/InputStream")
#define java_io_OutputStream ((const char*) "java/io/OutputStream")
#define java_io_FileInputStream ((const char*) "java/io/FileIntputStream")
#define java_io_FileOutputStream ((const char*) "java/io/FileOutputStream")

namespace JniUtils {
    static JNIEnv* env;

    /**
     * @brief Sets the Jni Env pointer for jni functions.
     * 
     * @param env the environment pointer to use.
     */
    static inline int setJniEnv(JNIEnv* env) {
        if (env == NULL) {
            return OPERATION_FAILED;
        }
        JniUtils::env = env;
        return OPERATION_SUCCEEDED;
    }

    /**
     * @brief Gets the Jni Env pointer.
     * 
     * @return JNIEnv* the namespace env pointer.
     */
    static inline JNIEnv* getJniEnv() {
        return JniUtils::env;
    }

    /**
     * @brief Retrieves a java class from a name, the name is referred to by the
     * package/class, example: {"com/java/io/IOException"}.
     * 
     * @param clazzName the class name using the format {package/class}.
     * @return jclass the reflected java class.
     */
    static inline jclass getClassFromString(const char* clazzName) {
        return JniUtils::getJniEnv()->FindClass(clazzName);
    }

    /**
     * @brief Retrieves a java class method using the [methodName] for the method name
     * and the [sig] for the method signature.
     * 
     * @param clazzName the class name in the format {"package/class"}.
     * @param methodName the method name, use `<init>` for constructors.
     * @param sig the method signature, eg: ()V for non-parameterized void method.
     * @return jmethodID a new method id for the requested method.
     */
    static inline jmethodID getClassMethod(const char* clazzName, const char* methodName, const char* sig) {
        return JniUtils::getJniEnv()->GetMethodID(getClassFromString(clazzName), methodName, sig);
    }

    /**
     * @brief Retrieves the java class constructor.
     * 
     * @version version 0 from getClassConstructor for parameteized constructors using constructor
     * signature.
     * @param clazzName the java class name in the format {"package/class"}.
     * @param sig the constructor signature, eg: ()V for non-parameterized void type.
     * @return jmethodID an id referring to the class constructor.
     */
    static inline jmethodID getClassConstructor0(const char* clazzName, const char* sig) {
        return JniUtils::getClassMethod(clazzName, CONSTRUCTOR, sig);
    }

    /**
     * @brief Retrieves the java class non-parameterized constructor with signature
     * [NON_PARAMTERIZED_VOID_SIG].
     * 
     * @param clazzName the java class name.
     * @return jmethodID an id referring to the class non-parameterized constructor.
     */
    static inline jmethodID getClassConstructor1(const char* clazzName) {
        return JniUtils::getClassConstructor0(clazzName, NON_PARAMTERIZED_VOID_SIG);
    }

    /**
     * @brief Calls a parameterized method [methodName] from class [clazzName].
     * 
     * @param clazzName the class name where the method is located, eg: {"java/io/IOException"}.
     * @param methodName the method name to call.
     * @param sig the signature of the method, eg: ()V for non-paramterized void methods.
     * @param args an array for the method parameters of type [jvalue] referring to one of the JNI
     * data types [jint, jbyte, jlong, jshort, jchar, jobject...etc].
     */
    static inline void callParameterizedMethod(const char* clazzName, const char* methodName, const char* sig, jvalue* args) {
        jclass clazz = JniUtils::getClassFromString(clazzName);
        jmethodID mid = JniUtils::getClassMethod(clazzName, methodName, sig);
        if (args == NULL) {
            JniUtils::getJniEnv()->CallVoidMethod(clazz, mid);
        } else {
            JniUtils::getJniEnv()->CallVoidMethod(clazz, mid, args);
        }
    }

    /**
     * @brief Calls a non-parameterized method [methodName] with signature [sig].
     * 
     * @param clazzName the class name where the method is located, eg: {"java/lang/String"}.
     * @param methodName the method name to call.
     * @param sig the signature of the method, eg: ()V, ()I, ()J.
     */
    static inline void callNonParameterizedMethod(const char* clazzName, const char* methodName, const char* sig) {
        JniUtils::callParameterizedMethod(clazzName, methodName, sig, NULL);
    }

    /**
     * @brief Calls a class parameterized constructor (<init> method) with
     * signature and jvalue (holds only one variable of one JNI data type at a time) parameters.
     * 
     * @param clazzName 
     * @param sig 
     * @param args 
     */
    static inline void callParameterizedConstructor(const char* clazzName, const char* sig, jvalue* args) {
        JniUtils::callParameterizedMethod(clazzName, CONSTRUCTOR, sig, args);
    }

    static inline void callNonParameterizedConstructor(const char* clazzName) {
        JniUtils::callParameterizedConstructor(clazzName, NON_PARAMTERIZED_VOID_SIG, NULL);
    }

    static inline jobject getObjectFromClass0(const char* clazzName) {
        return JniUtils::getJniEnv()->AllocObject(JniUtils::getClassFromString(clazzName));
    }

    static inline jobject getObjectFromClass1(const char* clazzName, jmethodID constructor) {
        return JniUtils::getJniEnv()->NewObject(JniUtils::getClassFromString(clazzName), constructor);
    }

    static inline jobject getObjectFromClass2(const char* clazzName) {
        return JniUtils::getObjectFromClass1(clazzName, JniUtils::getClassConstructor1(clazzName));
    }

    static inline jobjectArray createNewArrayFromBuffer(const char* clazzName, jsize length) {
        jobject initialElement = JniUtils::getJniEnv()->NewStringUTF("");

        jclass clazz = JniUtils::getClassFromString(clazzName);
        jobjectArray array = JniUtils::getJniEnv()->NewObjectArray(length, clazz, initialElement);
        return array;
    }

    static inline jobject* getObjectBufferFromString(const char** buffer, int length) {
        jobject* objectBuffer = (jobject*) calloc(length, sizeof(jobject));
        for (int i = 0; i < length; i++) {
            objectBuffer[i] = JniUtils::getJniEnv()->NewStringUTF(buffer[i]);
        }
        return objectBuffer;
    } 

    static inline void setArrayElements(jobjectArray array, jsize length, jobject* buffer) {
        for (int i = 0; i < length; i++) {
            JniUtils::getJniEnv()->SetObjectArrayElement(array, i, buffer[i]);
        }
    }

    static inline jobject getArrayElement(jobjectArray array, jsize index) {
        return JniUtils::getJniEnv()->GetObjectArrayElement(array, index);
    } 

    static inline jint getIntArrayElement(jintArray array, jsize index) {
        return JniUtils::getJniEnv()->GetIntArrayElements(array, 0)[index];
    }
}

#endif