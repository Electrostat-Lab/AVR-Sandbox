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
import com.serial4j.core.serial.Permissions;
import com.serial4j.core.errno.ErrnoToException;
import com.serial4j.core.util.natives.NativeImageLoader;
import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.serial.NativeTerminalDevice;
import com.serial4j.core.serial.ReadConfiguration;
import com.serial4j.core.serial.control.TerminalControlFlag;
import com.serial4j.core.serial.control.TerminalLocalFlag;
import com.serial4j.core.serial.control.TerminalInputFlag;
import com.serial4j.core.serial.control.TerminalOutputFlag;
import com.serial4j.core.serial.throwable.PermissionDeniedException;
import com.serial4j.core.serial.throwable.BrokenPipeException;
import com.serial4j.core.serial.throwable.NoSuchDeviceException;
import com.serial4j.core.serial.throwable.InvalidPortException;
import com.serial4j.core.serial.throwable.NoResultException;
import com.serial4j.core.serial.throwable.OperationFailedException;
import com.serial4j.core.serial.throwable.NoAvailableTtyDevicesException;

/**
 * The main entry class for the native terminal device for Serial4j api.
 * 
 * @author pavl_g.
 */
public final class TerminalDevice {

    /**
     * Static initializer for loading and setting up the native image.
     */
    static {
        setupJniEnvironment();
    }

    private static final Logger LOGGER = Logger.getLogger(SerialPort.class.getName());
    private final NativeTerminalDevice nativeTerminalDevice = new NativeTerminalDevice();
    
    private SerialPort serialPort;
    private ReadConfiguration readConfiguration;
    private String permissionsDescription;
    private boolean loggingEnabled;
    private InputStream inputStream;
    private OutputStream outputStream;

    /**
     * Instantiates a Unix terminal device object.
     */
    public TerminalDevice() {
    }

    private static void setupJniEnvironment() {
        try {
            final int errno = NativeTerminalDevice.setupJniEnvironment0();
            ErrnoToException.throwFromErrno(errno, "Jni Environment passed is invalid !");
        } catch (NoSuchDeviceException |
                 PermissionDeniedException |
                 BrokenPipeException |
                 InvalidPortException |
                 NoResultException |
                 OperationFailedException |
                 NoAvailableTtyDevicesException e) {
            e.printStackTrace();
        }
    }

    public final void openPort(final SerialPort serialPort) throws NoSuchDeviceException,
                                                                   PermissionDeniedException,
                                                                   BrokenPipeException,
                                                                   InvalidPortException,
                                                                   NoResultException,
                                                                   OperationFailedException,
                                                                   NoAvailableTtyDevicesException {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Opening serial device " + serialPort.getName());
        }
        final int errno = nativeTerminalDevice.openPort0(serialPort.getName());
        ErrnoToException.throwFromErrno(errno, serialPort.getName());
        this.serialPort = serialPort;
        this.serialPort.setFd(getPortDescriptor());
    }

    public void initTermios() throws NoSuchDeviceException,
                                     PermissionDeniedException,
                                     BrokenPipeException,
                                     InvalidPortException,
                                     NoResultException,
                                     OperationFailedException,
                                     FileNotFoundException,
                                     NoAvailableTtyDevicesException {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Initializing serial device " + getSerialPort().getName());
        }
        final int errno = nativeTerminalDevice.initTermios0();
        ErrnoToException.throwFromErrno(errno, getSerialPort().getName());

        /* get the java streams from the port after initializing it with the native terminal */
        inputStream = new FileInputStream(getSerialPort().getName());
        outputStream = new FileOutputStream(getSerialPort().getName());
    }

    public void setTerminalControlFlag(final TerminalControlFlag flag) throws NoSuchDeviceException,
                                                                            PermissionDeniedException,
                                                                            BrokenPipeException,
                                                                            InvalidPortException,
                                                                            NoResultException,
                                                                            OperationFailedException,
                                                                            NoAvailableTtyDevicesException {
                                       
        final long errno = nativeTerminalDevice.setTerminalControlFlag(flag.getValue());
        /* Warning: Force cast the errno to (int) */
        ErrnoToException.throwFromErrno((int) errno, getSerialPort().getName());
    }

    public void setTerminalLocalFlag(final TerminalLocalFlag flag) throws NoSuchDeviceException,
                                                                            PermissionDeniedException,
                                                                            BrokenPipeException,
                                                                            InvalidPortException,
                                                                            NoResultException,
                                                                            OperationFailedException,
                                                                            NoAvailableTtyDevicesException {

    }

    public void setTerminalInputFlag(final TerminalInputFlag flag)throws NoSuchDeviceException,
                                                                            PermissionDeniedException,
                                                                            BrokenPipeException,
                                                                            InvalidPortException,
                                                                            NoResultException,
                                                                            OperationFailedException,
                                                                            NoAvailableTtyDevicesException {

    }

    public void setTerminalOutputFlag(final TerminalOutputFlag flag)throws NoSuchDeviceException,
                                                                            PermissionDeniedException,
                                                                            BrokenPipeException,
                                                                            InvalidPortException,
                                                                            NoResultException,
                                                                            OperationFailedException,
                                                                            NoAvailableTtyDevicesException {

    }

    public void setPermissions(final Permissions permissions) {
        nativeTerminalDevice.setIOFlags(permissions.getValue());
        permissionsDescription = permissions.getDescription();
    }

    public final Permissions getPermissions() {
        final int permissionsValue = nativeTerminalDevice.getIOFlags();
        return Permissions.createCustomPermissions(permissionsValue, permissionsDescription);
    }

    public void setBaudRate(final BaudRate baudRate) throws NoSuchDeviceException,
                                                            PermissionDeniedException,
                                                            BrokenPipeException,
                                                            InvalidPortException,
                                                            NoResultException,
                                                            OperationFailedException,
                                                            NoAvailableTtyDevicesException {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Setting device baud rate to " + baudRate.getRealBaud());
        }
        final int errno = nativeTerminalDevice.setBaudRate0(baudRate.getBaudRate());
        ErrnoToException.throwFromErrno(errno, getSerialPort().getName()); 
    } 

    public void setReadConfigurationMode(final ReadConfiguration readConfiguration, final int timeoutValue, final int minimumBytes) throws NoSuchDeviceException,
                                                                                    PermissionDeniedException,
                                                                                    BrokenPipeException,
                                                                                    InvalidPortException,
                                                                                    NoResultException,
                                                                                    OperationFailedException,
                                                                                    NoAvailableTtyDevicesException {
         
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Setting reading config to " + readConfiguration.getDescription());
        }
        final int errno = nativeTerminalDevice.setReadConfigurationMode0(readConfiguration.getMode(), timeoutValue, minimumBytes);
        ErrnoToException.throwFromErrno(errno, "port is not invalid.");                                                                            
    }

    public final ReadConfiguration getReadConfigurationMode() {
        return ReadConfiguration.getFromNativeReadConfig(nativeTerminalDevice.getReadConfigurationMode0());
    }
    
    public final long writeBuffer(final String buffer) throws NoSuchDeviceException,
                                                          PermissionDeniedException,
                                                          BrokenPipeException,
                                                          InvalidPortException,
                                                          NoResultException,
                                                          OperationFailedException,
                                                          NoAvailableTtyDevicesException {
        final long numberOfWrittenBytes = nativeTerminalDevice.writeBuffer0(buffer, buffer.length());
        String message;
        if (numberOfWrittenBytes == -1) {
            message = "Write Permission [O_WRONLY] isnot granted, [Permissions: " + permissionsDescription + "]";
        } else {
            message = "Invalid Port " + serialPort.getName(); 
        }
        if (numberOfWrittenBytes < 1) {
            ErrnoToException.throwFromErrno((int) numberOfWrittenBytes, message);                                                                        
        }
        return numberOfWrittenBytes;
    }

    public final long writeData(final int data) throws NoSuchDeviceException,
                                                       PermissionDeniedException,
                                                       BrokenPipeException,
                                                       InvalidPortException,
                                                       NoResultException,
                                                       OperationFailedException,
                                                       NoAvailableTtyDevicesException {
        final long numberOfWrittenBytes = nativeTerminalDevice.writeData0(data);
        String message;
        if (numberOfWrittenBytes == -1) {
            message = "Write Permission [O_WRONLY] isnot granted.";
        } else {
            message = "Invalid Port " + serialPort.getName(); 
        }
        if (numberOfWrittenBytes < 1) {
            ErrnoToException.throwFromErrno((int) numberOfWrittenBytes, message);                                                                            
        }
        return numberOfWrittenBytes;
    }

    public final long readData() {
        return nativeTerminalDevice.readData0();
    }

    public final String readBuffer() {
        return nativeTerminalDevice.readBuffer0();
    }

    public final int getBaudRate() throws NoSuchDeviceException,
                                    PermissionDeniedException,
                                    BrokenPipeException,
                                    InvalidPortException,
                                    NoResultException,
                                    OperationFailedException,
                                    NoAvailableTtyDevicesException {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Getting device baud");
        }
        final int errno = nativeTerminalDevice.getBaudRate0();
        ErrnoToException.throwFromErrno(errno, getSerialPort().getName()); 
        return errno;
    }

    public final String[] getSerialPorts() throws NoSuchDeviceException,
                                                  PermissionDeniedException,
                                                  BrokenPipeException,
                                                  InvalidPortException,
                                                  NoResultException,
                                                  OperationFailedException,
                                                  NoAvailableTtyDevicesException {
        fetchSerialPorts();
        return nativeTerminalDevice.getSerialPorts0();
    }

    public void throwExceptionFromNativeErrno() throws NoSuchDeviceException,
                                                       PermissionDeniedException,
                                                       BrokenPipeException,
                                                       InvalidPortException,
                                                       NoResultException,
                                                       OperationFailedException,
                                                       NoAvailableTtyDevicesException {                                                
        final int errno = nativeTerminalDevice.getErrno0();
        ErrnoToException.throwFromErrno(errno, "Native Errno: " + errno);
    }

    public void closePort() throws NoSuchDeviceException,
                                   PermissionDeniedException,
                                   BrokenPipeException,
                                   InvalidPortException,
                                   NoResultException,
                                   OperationFailedException,
                                   NoAvailableTtyDevicesException {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Closing port: " + getSerialPort().getName());
        }
        final int errno = nativeTerminalDevice.closePort0();
        ErrnoToException.throwFromErrno(errno, getSerialPort().getName());
    }
    
    public void setSerial4jLoggingEnabled(final boolean loggingEnabled) {
        this.loggingEnabled = loggingEnabled;
    }

    public final boolean isSerial4jLoggingEnabled() {
        return loggingEnabled;
    }

    public final int getReadBuffer() {
        return nativeTerminalDevice.getReadBuffer0();
    }

    public void setNativeLoggingEnabled() {
        nativeTerminalDevice.setLoggingEnabled0();
    }

    public void setNativeLoggingDisabled() {
        nativeTerminalDevice.setLoggingDisabled0();
    }

    public final InputStream getInputStream() {
        return inputStream;
    }

    public final OutputStream getOutputStream() {
        return outputStream;
    }

    public final SerialPort getSerialPort() {
        return serialPort;
    }

    private final int getPortDescriptor() throws NoSuchDeviceException,
                                                 PermissionDeniedException,
                                                 BrokenPipeException,
                                                 InvalidPortException,
                                                 NoResultException,
                                                 OperationFailedException,
                                                 NoAvailableTtyDevicesException {
        final int value = nativeTerminalDevice.getFileDescriptor0();
        ErrnoToException.throwFromErrno(value, serialPort.getName() + " " + serialPort.getFd());
        return value;
    }

    private void fetchSerialPorts() throws NoSuchDeviceException,
                                           PermissionDeniedException,
                                           BrokenPipeException,
                                           InvalidPortException,
                                           NoResultException,
                                           OperationFailedException,
                                           NoAvailableTtyDevicesException {
        if (isSerial4jLoggingEnabled()) {
            LOGGER.log(Level.INFO, "Fetching Serial ports.");
        }
        final int errno = nativeTerminalDevice.fetchSerialPorts0();
        ErrnoToException.throwFromErrno(errno, "No available devices !");                                    
    }
}