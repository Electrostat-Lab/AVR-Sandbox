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
import com.serial4j.core.serial.BaudRate;
import com.serial4j.core.serial.SerialPort;
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
	static SerialPort serialPort = new SerialPort();		
	public static void main(String args[]) throws NoSuchDeviceException,
												  PermissionDeniedException,
												  BrokenPipeException,
												  InvalidPortException,
												  NoResultException,
												  OperationFailedException,
												  FileNotFoundException {

		System.out.println("Started native io example: ");
		serialPort.setSerial4jLoggingEnabled(true);
		serialPort.setNativeLoggingEnabled();
		serialPort.openPort("/dev/ttyUSB0");
		if (serialPort.getPortDescriptor() > 0) {
			System.out.println("Port Opened with "+serialPort.getPortDescriptor());
		}
		serialPort.initTermios();
		serialPort.setBaudRate(BaudRate.B57600);
		System.out.println(Arrays.toString(serialPort.getSerialPorts()));
		startReadThread(serialPort, 2500);
		startWriteThread(serialPort, 0);
	}

	private static void startReadThread(final SerialPort serialPort, final long millis) {
		new Thread(new Runnable() {
			public void run() {
				try {
					Thread.sleep(millis);
					while(true) {
						if (serialPort.readData() > 0) {
							if ((char) serialPort.getReadBuffer() > 0) 
							System.out.println((char) serialPort.getReadBuffer());
						}
					}	
				}catch(InterruptedException e) {
					e.printStackTrace();
				}		
			}
		}).start();
	}

	private static void startWriteThread(final SerialPort serialPort, final long millis) {
		new Thread(new Runnable() {
			@Override
			public void run() {
				try {
					Thread.sleep(millis);
					serialPort.writeData('B');
					serialPort.writeData('C');
					serialPort.closePort();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}).start();
	}
}

