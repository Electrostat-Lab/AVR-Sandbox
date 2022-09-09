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
package com.serial4j.example;

import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Arrays;
import java.io.FileNotFoundException;
import com.serial4j.core.serial.control.TerminalControlFlag;
import com.serial4j.core.serial.control.TerminalLocalFlag;
import com.serial4j.core.serial.control.TerminalOutputFlag;
import com.serial4j.core.serial.control.TerminalInputFlag;
import com.serial4j.core.serial.ReadConfiguration;
import com.serial4j.core.serial.Permissions;
import com.serial4j.core.serial.BaudRate;
import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.serial.TerminalDevice;
import com.serial4j.core.serial.throwable.PermissionDeniedException;
import com.serial4j.core.serial.throwable.BrokenPipeException;
import com.serial4j.core.serial.throwable.NoSuchDeviceException;
import com.serial4j.core.serial.throwable.InvalidPortException;
import com.serial4j.core.serial.throwable.NoResultException;
import com.serial4j.core.serial.throwable.OperationFailedException;

/**
 * An example for Serial4j showing Native terminal control and 
 * native file io on a serial port.
 * 
 * @author pavl_g.
 */
public final class HelloNativeSerial4J {
	public static void main(String args[]) throws NoSuchDeviceException,
												  PermissionDeniedException,
												  BrokenPipeException,
												  InvalidPortException,
												  NoResultException,
												  OperationFailedException,
												  FileNotFoundException {		
		System.out.println("Started native io example: ");
		final TerminalDevice ttyDevice = new TerminalDevice();
		final Permissions permissions = Permissions.O_RDWR.append(Permissions.O_NOCTTY)
														  .append(Permissions.O_NONBLOCK);
		ttyDevice.setPermissions(permissions);
		final TerminalControlFlag TCF_VALUE = (TerminalControlFlag) TerminalControlFlag.CLOCAL
														   .append(TerminalControlFlag.CS8, TerminalControlFlag.CREAD);
		final TerminalLocalFlag TLF_VALUE = (TerminalLocalFlag) TerminalLocalFlag.EMPTY_INSTANCE
															 .disable(TerminalLocalFlag.ECHO, TerminalLocalFlag.ECHOK,
															 		  TerminalLocalFlag.ECHOE, TerminalLocalFlag.ECHOKE,
																	  TerminalLocalFlag.ECHONL, TerminalLocalFlag.ECHOPRT,
																	  TerminalLocalFlag.ECHOCTL, TerminalLocalFlag.ISIG,
																	  TerminalLocalFlag.IEXTEN, TerminalLocalFlag.ICANON);
		final TerminalOutputFlag TOF_VALUE = (TerminalOutputFlag) TerminalOutputFlag.EMPTY_INSTANCE
													           .disable(TerminalOutputFlag.OPOST, TerminalOutputFlag.ONLCR);
		final TerminalInputFlag TIF_VALUE = (TerminalInputFlag) TerminalInputFlag.EMPTY_INSTANCE.disableAll();
		ttyDevice.openPort(new SerialPort("/dev/ttyUSB0"));		
		ttyDevice.setTerminalControlFlag(TCF_VALUE);
		ttyDevice.setTerminalLocalFlag(TLF_VALUE);
		ttyDevice.setTerminalOutputFlag(TOF_VALUE);
		ttyDevice.setTerminalInputFlag(TIF_VALUE);
		ttyDevice.setSerial4jLoggingEnabled(true);
		ttyDevice.setNativeLoggingEnabled();
		if (ttyDevice.getSerialPort().getFd() > 0) {
			System.out.println("Port Opened with " + ttyDevice.getSerialPort().getFd());
		}
		ttyDevice.initTermios();
		ttyDevice.setBaudRate(BaudRate.B57600);
        ttyDevice.setReadConfigurationMode(ReadConfiguration.READ_WITH_INTERBYTE_TIMEOUT, 5, 510);
		System.out.println(Arrays.toString(ttyDevice.getSerialPorts()) + " " + ttyDevice.getSerialPorts().length);
		startReadThread(ttyDevice, 0);
		startWriteThread(ttyDevice, 2500);
	}

	private static void startReadThread(final TerminalDevice ttyDevice, final long millis) {
		new Thread(new Runnable() {
			public void run() {
				try {
					Thread.sleep(millis);
					while(true) {
						if (ttyDevice.readData() > 0) {
							System.out.println((char) ttyDevice.getReadBuffer());
						}
					}	
				} catch(Exception e) {
					e.printStackTrace();
				}		
			}
		}).start();
	}

	private static void startWriteThread(final TerminalDevice ttyDevice, final long millis) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				try {
					Thread.sleep(millis);
					ttyDevice.writeBuffer("AB");
					// ttyDevice.closePort();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}).start();
	}
}

