/*
 * BSD 3-Clause License
 *
 * Copyright (c) 2022, Scrappers Team, The AVR-Sandbox Project
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
package serial.monitor;

import com.fazecast.jSerialComm.SerialPort;
import serial.entity.impl.SerialReadEntity;
import serial.entity.impl.SerialWriteEntity;
import serial.entity.EntityStatus;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;

/**
 * Monitors the UART Data Port using {@link SerialReadEntity} for serial data read and {@link SerialWriteEntity} for serial
 * data write.
 *
 * @author pavl_g.
 */
public class SerialMonitor extends ThreadGroup {

    private final ArrayList<SerialDataListener> listeners = new ArrayList<>();
    private volatile InputStream readEntityStream;
    private volatile OutputStream writeEntityStream;
    private volatile SerialPort monitorPort;
    private volatile boolean terminate = false;
    private volatile SerialReadEntity serialReadEntity;
    private volatile SerialWriteEntity serialWriteEntity;
    public volatile EntityStatus<SerialReadEntity> readThreadEntityStatus;
    public volatile EntityStatus<SerialWriteEntity> writeThreadEntityStatus;
    public volatile boolean isReadSerialMonitorInitialized;
    public volatile boolean isWriteSerialMonitorInitialized;
    public volatile boolean isMonitoringStarted;
    public volatile boolean useReturnCarriage = true;

    public SerialMonitor(final String monitorName) {
        super(monitorName);
    }

    /**
     * Starts data monitoring with a [port] and a [baudRate]
     *
     * @param port specify the serial port.
     * @param baudRate specify the baud rate aka bits/seconds based for the connected FOsc.
     */
    public void startDataMonitoring(final String port, final int baudRate) {
        setMaxPriority(Thread.MAX_PRIORITY);
        monitorPort = SerialPort.getCommPort(port);
        /* ignore timeout strategy */
        monitorPort.setComPortTimeouts(SerialPort.TIMEOUT_NONBLOCKING, 0, 0);
        monitorPort.setBaudRate(baudRate);
        monitorPort.openPort();
        readEntityStream = monitorPort.getInputStream();
        writeEntityStream = monitorPort.getOutputStream();

        serialWriteEntity = new SerialWriteEntity(this);
        serialWriteEntity.setPriority(Thread.MIN_PRIORITY);
        serialWriteEntity.start();

        serialReadEntity = new SerialReadEntity(this);
        serialWriteEntity.setPriority(Thread.MAX_PRIORITY);
        serialReadEntity.start();

    }

    /**
     * Tests whether the monitor is terminated by external means.
     *
     * @return true if terminated by the user, false otherwise.
     */
    public boolean isTerminate() {
        return terminate;
    }

    /**
     * Sets the termination flag to trigger termination on the next update.
     */
    public void setTerminate() {
        this.terminate = true;
    }

    public InputStream getReadEntityStream() {
        return readEntityStream;
    }

    public SerialPort getMonitorPort() {
        return monitorPort;
    }

    public OutputStream getWriteEntityStream() {
        return writeEntityStream;
    }

    public SerialReadEntity getSerialReadEntity() {
        return serialReadEntity;
    }

    public SerialWriteEntity getSerialWriteEntity() {
        return serialWriteEntity;
    }

    public void addSerialDataListener(final SerialDataListener serialDataListener) {
        if (listeners.contains(serialDataListener)) {
            return;
        }
        listeners.add(serialDataListener);
    }

    public void removeSerialDataListener(final SerialDataListener serialDataListener) {
        if (!listeners.contains(serialDataListener)) {
            return;
        }
        listeners.remove(serialDataListener);
    }

    public void setReadEntityListener(EntityStatus<SerialReadEntity> readThreadEntityStatus) {
        this.readThreadEntityStatus = readThreadEntityStatus;
    }

    public void setWriteEntityStatus(EntityStatus<SerialWriteEntity> writeThreadEntityStatus) {
        this.writeThreadEntityStatus = writeThreadEntityStatus;
    }

    public boolean isUsingReturnCarriage() {
        return useReturnCarriage;
    }

    public void setUseReturnCarriage(boolean useReturnCarriage) {
        this.useReturnCarriage = useReturnCarriage;
    }

    public ArrayList<SerialDataListener> getListeners() {
        return listeners;
    }
}
