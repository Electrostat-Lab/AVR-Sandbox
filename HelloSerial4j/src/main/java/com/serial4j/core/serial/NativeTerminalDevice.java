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

import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.util.natives.NativeImageLoader;

/**
 * Represents the native java binding for Serial4j API, represented by 
 * [com_serial4j_core_serial_NativeTerminalDevice.h] natively.
 * 
 * @author pavl_g.
 */
public final class NativeTerminalDevice {

    /**
     * Static initializer: Loads the native image when this object is created or referenced.
     */
    static {
        NativeImageLoader.loadLibrary();
    }

    private SerialPort serialPort;
    private String[] serialPorts;
    private char[] readData;
    private String readBuffer = new String();

    protected NativeTerminalDevice() {
    }

    /**
     * Initializes the serial port path of the native terminal device before opening the terminal device port.
     * 
     * @param serialPort the object to initialize the serial port with.
     */
    protected void setSerialPort(final SerialPort serialPort) {
        this.serialPort = serialPort;
    }

    /**
     * Retrieves the serial port associated with this terminal device.
     * 
     * @return the serial port object associated with this terminal device.
     */
    public SerialPort getSerialPort() {
        return this.serialPort;
    }

    /**
     * Retrieves all the available teletype terminal (tty) devices from the filesystem "/dev".
     * 
     * @return the available tty devices in an array of strings format.
     */
    public String[] getSerialPorts() {
        return this.serialPorts;
    }

    /**
     * Gets the read data in an up-to 32-bit integer format resulting from using the native method {@link NativeTerminalDevice#readData0()}.
     *
     * @return the read data from this terminal device in an up-to 32-bit integer format.
     */
    public char[] getReadData() {
        return this.readData;
    }

    public String getReadBuffer() {
        return this.readBuffer;
    }

    /**
     * Sets up the native environment for this terminal device.
     * 
     * @return (-1) if the jni env pointer is NULL, (1) for successful initialization.
     */
    protected static native int setupJniEnvironment0(); 

    /**
     * Adjusts the native terminal control [c_cflag] of the [termios] structure variable for this terminal device.
     * @note The terminal control flag controls the way the terminal device r/w the charachters on the console.
     * For more, refer to the POSIX terminal control guide.
     * 
     * Default value = tty->c_cflag |= (CREAD | CS8 | CLOCAL); defined by {@link NativeTerminalDevice#initTermios0()}.
     * 
     * @param flag the flag to set the [c_cflag] to.
     * @return errno(-1) for failure, errno(-2) for invalid port, errno(1) for success.
     * @see com.serial4j.core.serial.control.TerminalControlFlag
     */
    protected native int setTerminalControlFlag(final long flag);

    /**
     * Adjusts the native terminal local [c_lflag] of the [termios] structure variable for this terminal device.
     * @note The terminal local flag controls the way the terminal device interprets and displays the charachters on the console (i.e local console).
     * For more, refer to the POSIX terminal control guide.
     *
     * Default value = tty->c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHOKE | ECHONL | ECHOPRT | ECHOCTL | ISIG | IEXTEN); 
     * defined by {@link NativeTerminalDevice#initTermios0()}.
     *
     * @param flag the flag to set the [c_lflag] to.
     * @return errno(-1) for failure, errno(-2) for invalid port, errno(1) for success.
     * @see com.serial4j.core.serial.control.TerminalLocalFlag
     */    
    protected native int setTerminalLocalFlag(final long flag);

    /**
     * Adjusts the native terminal input [c_iflag] of the [termios] structure variable for this terminal device.
     * @note The terminal input flag controls the way the terminal device receives and interprets the charachters on input.
     * For more, refer to the POSIX terminal control guide.
     * 
     * Default value = tty->c_iflag = 0x00; defined by {@link NativeTerminalDevice#initTermios0()}.
     *
     * @param flag the flag to set the [c_iflag] to.
     * @return errno(-1) for failure, errno(-2) for invalid port, errno(1) for success.
     * @see com.serial4j.core.serial.control.TerminalInputFlag
     */    
    protected native int setTerminalInputFlag(final long flag);

    /**
     * Adjusts the native terminal output [c_oflag] of the [termios] structure variable for this terminal device.
     * @note The terminal output flag controls the way the terminal device transmits and interprets the charachters on output.
     * For more, refer to the POSIX terminal control guide.
     * 
     * Default value = tty->c_oflag &= ~(OPOST | ONLCR); defined by {@link NativeTerminalDevice#initTermios0()}.
     *
     * @param flag the flag to set the [c_oflag] to.
     * @return errno(-1) for failure, errno(-2) for invalid port, errno(1) for success.
     * @see com.serial4j.core.serial.control.TerminalOutputFlag
     */    
    protected native int setTerminalOutputFlag(final long flag);

    /**
     * Retrieves the terminal control flag from this terminal device port descriptor in 64-bit format.
     * 
     * @return the [c_cflag] value in longs.
     */
    protected native long getTerminalControlFlag();

    /**
     * Retrieves the terminal local flag from this terminal device port descriptor in 64-bit format.
     * 
     * @return the [c_lflag] value in longs.
     */
    protected native long getTerminalLocalFlag();

    /**
     * Retrieves the terminal input flag from this terminal device port descriptor in 64-bit format.
     * 
     * @return the [c_iflag] value in longs.
     */
    protected native long getTerminalInputFlag();

    /**
     * Retrieves the terminal output flag from this terminal device port descriptor in 64-bit format.
     * 
     * @return the [c_oflag] value in longs.
     */
    protected native long getTerminalOutputFlag();

    /**
     * Adjusts the read mode for this terminal device, the read mode is defined by the read timeout value and the minimum
     * number of bytes to read at that time.
     * 
     * Default value = BLOCKING_READ_ONE_CHAR {0, 1}; defined by {@link NativeTerminalDevice#initTermios0()}.
     *
     * @param mode the read mode in a 2 lengthed array format, where first index refers to the timeout config and second index
     *             refers to the bytes config.
     * @param VTIME_VALUE the value of the read timeout, applied only when the first index of [mode] is 1 (aka read timeout is activated).
     * @param VMIN_VALUE the value of the minimum byte to read in this time.
     * @return errno(-1) for failure, errno(-2) for invalid port, errno(1) for success.
     * @see com.serial4j.core.serial.ReadConfiguration
     */
    protected native int setReadConfigurationMode0(final byte VTIME_VALUE, final byte VMIN_VALUE);

    /**
     * Gets the read configuration for this terminal device defining the timeout value as the first index and 
     * the minimum number of read byte in this timeout as the second index.
     *
     * Default value = BLOCKING_READ_ONE_CHAR {0, 1}; defined by {@link NativeTerminalDevice#initTermios0()}.
     *
     * @return an array refering to the read mode, where index [0] represents the read timeout, index [1] represents
     *         the minimum bytes to read.
     */
    protected native byte[] getReadConfigurationMode0();

    /**
     * Retrieves the last error encountered by the native code,
     *
     * @return the last error code from the native <errno.h>.
     */
    protected native int getErrno0();

    /**
     * Fetches the available system teletype terminal devices (tty) located within "/dev" directory
     * and insert the result into {@link NativeTerminalDevice#serialPorts}.
     *
     * @return errno(-1) for failure, errno(-2) for invalid port, errno(1) for success.
     */
    protected native int fetchSerialPorts0();

    /**
     * Retrieves the baud rate for this terminal process.
     * 
     * @return the baud rate in integers.
     */
    protected native int getBaudRate0();

    /**
     * Writes an integer buffer to this terminal device.
     * 
     * @param data an integer data buffer to write up-to 32-bit.
     * @return the number of written bytes in long format.
     */
    protected native long writeData0(final int data);

    /**
     * Reads the data from the terminal device and inserts the result into an integer buffer 
     * {@link NativeTerminalDevice#readData}.
     *
     * @return the number of read bytes.
     */
    protected native long readData0();

    protected native long writeBuffer0(final String buffer, final int length);

    protected native long readBuffer0();

    protected native int initTermios0();

    protected native int setBaudRate0(int baudRate);

    protected native int openPort0(final String port, final int flag);

    /**
     * Closes the serial port of this terminal device releasing the resources.
     * @note This call triggers {@link NativeTerminalDevice#serialPort#portOpened} to 0, 
     * the port descriptor {@link NativeTerminalDevice#serialPort#fd} to 0 and the port path {@link NativeTerminalDevice#serialPort#fd} to "".
     * 
     * @return errno(-1) for failure, errno(-2) for invalid port, errno(1) for success.
     */
    protected native int closePort0();
}