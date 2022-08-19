package com.serial4j.example;

import java.io.FileOutputStream;
import java.io.IOException;

import com.serial4j.core.serial.BaudRate;
import com.serial4j.core.serial.SerialPort;

public class HelloSerial4J {
	static SerialPort serial = new SerialPort("/dev/ttyUSB0");		

	public static void main(String args[]) throws IOException {
		System.out.println("Running");

		int portDescriptor = serial.openPort();
		if (portDescriptor > 0) {
			System.out.println("Port Opened with "+portDescriptor);
		}
		int initState = serial.initTermios();
		if (initState >= 0) {
			System.out.println("Port " + portDescriptor +" initialized");
		} else {
			System.err.println(initState);
		}
		serial.setBaudRate(BaudRate.B57600);
		System.out.println(serial.getBaudRate());
		System.out.println(serial.fetchSerialPorts());
		new Thread(new Runnable() {
			public void run() {
				while(true) {
					while (serial.readData() > 0) {
						if ((char) serial.getReadBuffer() > 0) 
						System.out.println((char) serial.getReadBuffer());
					}
				}			
			}
		}).start();
		try {
			Thread.sleep(2000);
			serial.writeData('C');
			serial.writeData('A');
			Thread.sleep(300);
			System.out.println(serial.closePort());
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}

