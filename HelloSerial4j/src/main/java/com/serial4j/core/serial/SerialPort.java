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

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.logging.Level;
import java.util.logging.Logger;
import com.serial4j.core.errno.ErrnoToException;
import com.serial4j.core.util.natives.NativeImageLoader;
import com.serial4j.core.serial.throwable.PermissionDeniedException;
import com.serial4j.core.serial.throwable.BrokenPipeException;
import com.serial4j.core.serial.throwable.NoSuchDeviceException;
import com.serial4j.core.serial.throwable.InvalidPortException;
import com.serial4j.core.serial.throwable.NoResultException;
import com.serial4j.core.serial.throwable.OperationFailedException;

/**
 * The main entry class for the native terminal device for Serial4j api.
 * 
 * @author pavl_g.
 */
public class SerialPort {

    static {
        NativeImageLoader.loadLibrary();
        setupJniEnvironment();
    }

    private static final Logger LOGGER = Logger.getLogger(SerialPort.class.getName());
    private boolean loggingEnabled;
    private String portName;
    private InputStream inputStream;
    private OutputStream outputStream;

    public SerialPort() {
    }

    public void openPort(final String portName) throws NoSuchDeviceException,
                                  PermissionDeniedException,
                                  BrokenPipeException,
                                  InvalidPortException,
                                  NoResultException,
                                  OperationFailedException {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Opening serial device" + portName);
        }
        final int errno = openPort0(portName);
        ErrnoToException.throwFromErrno(errno, portName);
        this.portName = portName;
    }

    public void initTermios() throws NoSuchDeviceException,
                                     PermissionDeniedException,
                                     BrokenPipeException,
                                     InvalidPortException,
                                     NoResultException,
                                     OperationFailedException,
                                     FileNotFoundException {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Initializing serial device" + portName);
        }
        final int errno = initTermios0();
        ErrnoToException.throwFromErrno(errno, portName);

        /* get the java streams from the port after initializing it with the native terminal */
        inputStream = new FileInputStream(portName);
        outputStream = new FileOutputStream(portName);
    }

    public void setBaudRate(final BaudRate baudRate) throws NoSuchDeviceException,
                                                            PermissionDeniedException,
                                                            BrokenPipeException,
                                                            InvalidPortException,
                                                            NoResultException,
                                                            OperationFailedException {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Setting device baud rate to " + baudRate.getRealBaud());
        }
        final int errno = setBaudRate0(baudRate.getBaudRate());
        ErrnoToException.throwFromErrno(errno, portName); 
    } 

    public long writeData(final int data) {
        return writeData0(data);
    }

    public long readData() {
        return readData0();
    }

    public int getBaudRate() throws NoSuchDeviceException,
                                    PermissionDeniedException,
                                    BrokenPipeException,
                                    InvalidPortException,
                                    NoResultException,
                                    OperationFailedException {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Getting device baud");
        }
        final int errno = getBaudRate0();
        ErrnoToException.throwFromErrno(errno, portName); 
        return errno;
    }

    public final String[] getSerialPorts() throws NoSuchDeviceException,
                                                  PermissionDeniedException,
                                                  BrokenPipeException,
                                                  InvalidPortException,
                                                  NoResultException,
                                                  OperationFailedException {
        fetchSerialPorts();
        return getSerialPorts0();
    }

    public void throwExceptionFromNativeErrno() throws NoSuchDeviceException,
                                                       PermissionDeniedException,
                                                       BrokenPipeException,
                                                       InvalidPortException,
                                                       NoResultException,
                                                       OperationFailedException {                                                
        final int errno = getErrno0();
        ErrnoToException.throwFromErrno(errno, "Native Errno: " + errno);
    }

    public void closePort() throws NoSuchDeviceException,
                                   PermissionDeniedException,
                                   BrokenPipeException,
                                   InvalidPortException,
                                   NoResultException,
                                   OperationFailedException {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Closing port: " + portName);
        }
        final int errno = closePort0();
        ErrnoToException.throwFromErrno(errno, portName);
    }
    
    public void setSerial4jLoggingEnabled(final boolean loggingEnabled) {
        this.loggingEnabled = loggingEnabled;
    }

    public boolean isSerial4jLoggingEnabled() {
        return loggingEnabled;
    }

    public int getReadBuffer() {
        return getReadBuffer0();
    }

    public void setNativeLoggingEnabled() {
        setLoggingEnabled0();
    }

    public void setNativeLoggingDisabled() {
        setLoggingDisabled0();
    }

    public final int getPortDescriptor() {
        return getFileDescriptor0();
    }

    public final InputStream getInputStream() {
        return inputStream;
    }

    public final OutputStream getOutputStream() {
        return outputStream;
    }

    public final String getPortName() {
        return portName;
    }

    private static void setupJniEnvironment() {
        try {
            final int errno = setupJniEnvironment0();
            ErrnoToException.throwFromErrno(errno, "Jni Environment passed is invalid !");
        } catch (NoSuchDeviceException |
                 PermissionDeniedException |
                 BrokenPipeException |
                 InvalidPortException |
                 NoResultException |
                 OperationFailedException e) {
            e.printStackTrace();
        }
    }

    private void fetchSerialPorts() throws NoSuchDeviceException,
                                           PermissionDeniedException,
                                           BrokenPipeException,
                                           InvalidPortException,
                                           NoResultException,
                                           OperationFailedException {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Fetching Serial ports.");
        }
        final int errno = fetchSerialPorts0();
        ErrnoToException.throwFromErrno(errno, "No available devices !");                                    
    }

    private static native int setupJniEnvironment0();

    private native void setLoggingEnabled0();

    private native void setLoggingDisabled0();

    private native String[] getSerialPorts0();

    private native int fetchSerialPorts0();

    private native int getBaudRate0();

    private native int getReadBuffer0();

    private native int getFileDescriptor0();

    private native long writeData0(final int data);

    private native long readData0();

    private native int getErrno0();

    private native int initTermios0();

    private native int setBaudRate0(int baudRate);

    private native int openPort0(final String port);

    private native int closePort0();
}