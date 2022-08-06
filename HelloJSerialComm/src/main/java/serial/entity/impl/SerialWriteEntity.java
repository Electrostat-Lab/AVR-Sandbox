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
package serial.entity.impl;

import serial.entity.EntityStatus;
import serial.entity.SerialMonitorEntity;
import serial.monitor.SerialMonitor;
import serial.monitor.SerialMonitorException;
import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;

/**
 * Represents a serial write data entity for the {@link SerialMonitor}.
 * Use {@link SerialMonitor#startDataMonitoring(String, int)} to start this entity.
 *
 * @author pavl_g.
 */
public class SerialWriteEntity extends SerialMonitorEntity {

    private final ArrayList<SerialWriteCapsule> capsules = new ArrayList<>();

    public SerialWriteEntity(final SerialMonitor threadGroup) {
        super(threadGroup, SerialWriteEntity.class.getName());
    }

    @Override
    protected void onDataMonitored(SerialMonitor serialMonitor) {
        for (; ; ) {
            /* throws if not initialized yet */
            if (getMonitorPort() == null) {
                throw new SerialMonitorException(SerialMonitorException.DEFAULT_MSG);
            }

            /* sanity check [terminate] flag */
            if (isTerminate()) {
                terminate();
                if (getSerialEntityStatusListener() != null) {
                    getSerialEntityStatusListener().onSerialEntityTerminated(this);
                }
                return;
            }

            /* sanity check data monitoring status */
            if (!isMonitoringStarted()) {
                continue;
            }

            /* initialize and update serial entity */
            if (!isSerialEntityInitialized()) {
                if (getSerialEntityStatusListener() != null) {
                    getSerialEntityStatusListener().onSerialEntityInitialized(this);
                }
                setSerialEntityInitialized(true);
            }

            if (getSerialEntityStatusListener() != null) {
                getSerialEntityStatusListener().onUpdate(this);
            }

            /* write required data  */
            for (SerialWriteCapsule capsule : capsules) {
                /* skip capsules with written data */
                if (capsule.isDataWritten()) {
                    continue;
                }
                /* send capsule data to the UART */
                final String data = capsule.getData();
                for (int j = 0; j < data.length(); j++) {
                    sendToUART(data.charAt(j));
                    for (int k = 0; k < getSerialDataListeners().size(); k++) {
                        getSerialDataListeners().get(k).onDataTransmitted(data.charAt(j));
                    }
                }
                capsule.setDataWritten(true);
            }
        }
    }

    public ArrayList<SerialWriteCapsule> getCapsules() {
        return capsules;
    }

    public void addWriteCapsule(final SerialWriteCapsule serialWriteCapsule) {
        if (capsules.contains(serialWriteCapsule)) {
            return;
        }
        capsules.add(serialWriteCapsule);
    }

    public void removeWriteCapsule(final SerialWriteCapsule serialWriteCapsule) {
        if (!capsules.contains(serialWriteCapsule)) {
            return;
        }
        capsules.remove(serialWriteCapsule);
    }

    private void sendToUART(final int data) {
        try {
            getEntityStream().write(data);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected OutputStream getEntityStream() {
        return getSerialMonitor().getWriteEntityStream();
    }

    @Override
    protected boolean isSerialEntityInitialized() {
        return getSerialMonitor().isWriteSerialMonitorInitialized;
    }

    @Override
    protected void setSerialEntityInitialized(boolean state) {
        getSerialMonitor().isWriteSerialMonitorInitialized = state;
    }

    @Override
    protected EntityStatus<SerialWriteEntity> getSerialEntityStatusListener() {
        return getSerialMonitor().writeThreadEntityStatus;
    }
}
