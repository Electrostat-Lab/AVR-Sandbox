package com.serial4j.core.serial;

public enum BaudRate {
    B57600(0010001); /* BAUD_RATE 57600 as defined by POSIX */

    private final int baudRate;

    BaudRate(final int baudRate) {
        this.baudRate = baudRate;
    }

    public int getBaudRate() {
        return baudRate;
    }
}
