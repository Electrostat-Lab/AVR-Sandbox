/*
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
package com.serial4j.core.serial;

import com.serial4j.core.util.natives.NativeImageLoader;

public final class NativeTerminalDevice {

    /**
     * Static initializer: Loads the native image when this object is created or referenced.
     */
    static {
        NativeImageLoader.loadLibrary();
    }

    protected NativeTerminalDevice() {
    }

    /**
     * Sets up the native environment for this terminal device.
     * 
     * @return (-1) if the jni env pointer is NULL, (1) for successful initialization.
     */
    protected static native int setupJniEnvironment0();

    protected native int setReadConfigurationMode0(final int[] mode, final int VTIME_VALUE, final int VMIN_VALUE);

    protected native int[] getReadConfigurationMode0();

    protected native void setLoggingEnabled0();

    protected native void setLoggingDisabled0();

    protected native String[] getSerialPorts0();

    protected native int fetchSerialPorts0();

    protected native int getBaudRate0();

    protected native int getReadBuffer0();

    protected native int getFileDescriptor0();

    protected native long writeData0(final int data);

    protected native long readData0();

    protected native int getErrno0();

    protected native int initTermios0();

    protected native int setBaudRate0(int baudRate);

    protected native int openPort0(final String port);

    protected native int closePort0();
}
