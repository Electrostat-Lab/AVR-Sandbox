package com.serial4j.core.serial;

import com.serial4j.core.util.natives.NativeImageLoader;

public class SerialPort {

    static {
        NativeImageLoader.loadLibrary();
    }

    private final String portDescriptor;

    public SerialPort(final String portDescriptor) {
        this.portDescriptor = portDescriptor;
    }

    public int fetchSerialPorts() {
        return fetchSerialPorts0();
    }

    public int openPort() {
        return openPort0(portDescriptor);
    }

    public int initTermios() {
        return initTermios0();
    }

    public void setBaudRate(final BaudRate baudRate) {
        setBaudRate0(baudRate.getBaudRate());
    } 

    public long writeData(final int data) {
        return writeData0(data);
    }

    public long readData() {
        return readData0();
    }

    public int getReadBuffer() {
        return getReadBuffer0();
    }

    public int getBaudRate() {
        return getBaudRate0();
    }

    public int closePort() {
        return closePort0();
    } 

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