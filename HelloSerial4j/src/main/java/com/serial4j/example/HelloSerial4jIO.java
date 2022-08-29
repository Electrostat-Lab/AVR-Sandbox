package com.serial4j.example;

import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Arrays;
import java.io.FileNotFoundException;
import com.serial4j.core.serial.BaudRate;
import com.serial4j.core.serial.SerialPort;
import com.serial4j.core.serial.throwable.PermissionDeniedException;
import com.serial4j.example.HelloNativeSerial4J;
import com.serial4j.core.serial.throwable.BrokenPipeException;
import com.serial4j.core.serial.throwable.NoSuchDeviceException;
import com.serial4j.core.serial.throwable.InvalidPortException;
import com.serial4j.core.serial.throwable.NoResultException;
import com.serial4j.core.serial.throwable.OperationFailedException;

public final class HelloSerial4jIO {
    static SerialPort serialPort = new SerialPort();		
    public static void main(String args[]) throws NoSuchDeviceException,
												  PermissionDeniedException,
												  BrokenPipeException,
												  InvalidPortException,
												  NoResultException,
												  OperationFailedException,
												  FileNotFoundException,
                                                  InterruptedException {
        
        // HelloNativeSerial4J.main(args);
        System.out.println("Started java io example: ");
		serialPort.setSerial4jLoggingEnabled(true);
		serialPort.setNativeLoggingEnabled();
		serialPort.openPort(serialPort.getSerialPorts()[0]);
		if (serialPort.getPortDescriptor() > 0) {
			System.out.println("Port Opened with "+serialPort.getPortDescriptor());
		} else {
            System.err.println("Cannot open serial port" + " " + serialPort.getPortDescriptor());
        }
		serialPort.initTermios();
		serialPort.setBaudRate(BaudRate.B57600);
		System.out.println("Available serial ports: " + Arrays.toString(serialPort.getSerialPorts()));
        startReadThread(serialPort, 5000);
        startWriteThread(serialPort, 8000);
    }

    private static void startWriteThread(final SerialPort serialPort, final long millis) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    Thread.sleep(millis);
                    serialPort.getOutputStream().write('A');
                    serialPort.getOutputStream().write('D');
                    serialPort.closePort();
                } catch (IOException | InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    private static void startReadThread(final SerialPort serialPort, final long millis) {
        new Thread(new Runnable() {
			public void run() {
                try {
                    Thread.sleep(millis);
                    while(true) {
                        if (serialPort.getInputStream().available() > 0) {
                            System.out.println((char) serialPort.getInputStream().read());
                        }
                    }
                } catch(IOException | InterruptedException e) {
                    e.printStackTrace();
                }
			}
		}).start();
    }
}
