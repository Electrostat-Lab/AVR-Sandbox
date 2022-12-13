# HelloJSerialComm

## Topics Covered:
1) What's `JSerialComm` ?
2) Serial-Monitor API Basic Paradigm.
3) Serial-Monitor API implementation code.

--------------------------------------------------
## 1) What's `JSerialComm` ?

jSerialComm is a Java library designed to provide a platform-independent way to access standard serial ports without requiring external libraries, 
native code, or any other tools. 

It is meant as an alternative to RxTx and the (deprecated) Java Communications API, with increased ease-of-use, an enhanced support for timeouts, 
and the ability to open multiple ports simultaneously.

For more, refer to the documentation provided at: 
- [JSerialComm Website](https://fazecast.github.io/jSerialComm/)
- [JSerialComm Github](https://github.com/Fazecast/jSerialComm)
- [JSerialComm Wiki](https://github.com/Fazecast/jSerialComm/wiki)

-----------------------------------------------------
## 2) Serial-Monitor API Basic Paradigm:

![SerialMonitor](https://software-hardware-codesign.github.io/AVR-Sandbox/HelloJSerialComm/UML/SerialMonitor.svg)

- `com.serial.monitor.SerialMonitor`: A threadgroup, it starts, controls and monitors the serial monitor R/W entities threads, 
it also holds the basic piece of operation, the monitor port, an instance of `com.fazecast.jSerialComm.SerialPort`.

- `com.serial.monitor.SerialMonitorException`: An `IllegalStateException` fired whenever the user tries to access the serial monitor R/W entities 
without opening the port.

- `com.serial.monitor.SerialDataListener`: Represents a data listener to Serial-Monitor R/W entities.

- `com.serial.entity.SerialMonitorEntity`: A data entity represented by a thread, holds a data state, either read for Rx and write or transmit for Tx signals.

- `com.serial.entity.EntityStatus`: An interface that provides a life for the Serial-Monitor entities.

- `com.serial.entity.impl.SerialReadEntity`: A `SerialMonitorEntity` that provides the reading state of the UART monitor dispatching the 
`com.serial.monitor.SerialDataListener#onDataReceived()`.

- `com.serial.entity.impl.SerialWriteEntity`: A `SerialMonitorEntity` that provides a writing strategy to the serial port using the `SerialWriteCapsule`s.

- `com.serial.entity.impl.SerialWriteCapsule`: A wrapper class for the data to be written by the `SerialWriteEntity` to the UART port, the class is
provided by a boolean flag to indicate that the data has been transmitted successfully.

--------------------------------------------------------
## 3) Serial-Monitor API implementation code: 

1) Create a `SerialMonitor` instance and start data monitoring on a PORT with a BAUD_RATE: 
```java
final SerialMonitor serialMonitor = new SerialMonitor("Monitor A");
serialMonitor.startDataMonitoring("/dev/ttyUSB0", 57600);
```
2) Set the write entity status instance to monitor the life cycle code for the SerialWriteEntity as follows:
```java
public class HelloJSerialComm implements SerialDataListener, EntityStatus<SerialWriteEntity> {
  ...
  public void run() {
  ...
      serialMonitor.setWriteEntityStatus(this);
  ...
  }
  @Override
  public void onSerialEntityInitialized(SerialWriteEntity serialMonitorEntity) {

  }

  @Override
  public void onSerialEntityTerminated(SerialWriteEntity serialMonitorEntity) {
      System.err.println("JSerialComm: Terminated");
  }

  @Override
  public void onUpdate(SerialWriteEntity serialMonitorEntity) {
      if (isDataSent) {
          return;
      }
      /* send data after 5 seconds */
      delay(5000);
      /* send data in a UART capsule on the serial write entity thread */
      writeInUARTCapsule(serialMonitorEntity.getSerialMonitor(), "0\n\r");
      isDataSent = true;
  }
  ...
}
```
3) Add a SerialData listener to listen for data R/W: 
```java
public class HelloJSerialComm implements SerialDataListener, EntityStatus<SerialWriteEntity> {
    ...
    public void run() {
    ...
        serialMonitor.addSerialDataListener(this);
    ...
    }
    @Override
    public void onDataReceived(int data) {

    }

    @Override
    public void onDataTransmitted(int data) {

    }

    @Override
    public void onDataReceived(String data) {

    }
    ...
}
```
4) Write data using write capsules and monitor the output using `onDataReceived(data: String)`: 
```java
public class HelloJSerialComm implements SerialDataListener, EntityStatus<SerialWriteEntity> {
    ...
    public void run() {
    ...
        /* write data to UART with return-carriage/newline */
        delay(2000);
        writeInUARTCapsule(serialMonitor, "0\n\r");
    ...
    }
    @Override
    public void onDataReceived(int data) {

    }

    @Override
    public void onDataTransmitted(int data) {

    }

    @Override
    public void onDataReceived(String data) {
        System.out.println(data);
    }
    ...
}
```
5) Test by uploading the [HelloUART](https://github.com/Software-Hardware-Codesign/AVR-Sandbox/blob/master/HelloUART/main/lib/HelloUART.c) code to the ATMega328p.

### This is the C code for testing purposes, it prints the number transmitted from java in hex:
```c
/**
 * @file HelloUART.c
 * @author pavl_g.
 * @brief Shows a basic implementation of the [Serial.h] library.
 * @version 0.1
 * @date 2022-07-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<avr/io.h>
#include<string.h>

#include<Serial.h>

const char* message = "Data Transmission completed successfully !";

void Serial::UART::onDataReceiveCompleted(const uint8_t& data) {
	Serial::UART::getInstance()->println((const uint8_t) data, 16);
}

void Serial::UART::onDataTransmitCompleted(const uint8_t& data) {
	Serial::UART::getInstance()->sprintln((char*) message);
}

int main(void) {
	 Serial::UART::getInstance()->startProtocol(BAUD_RATE_57600);
	 while (true); // wait forever
 return 0;
}
```

### Output: 
```
9:18:37 PM: Executing task 'Launcher.main()'...

> Task :compileJava
> Task :processResources NO-SOURCE
> Task :classes

> Task :Launcher.main()
---------------Welcome to JSerialComm Testcase---------------
30ad





Data Transmission completed successfully !

JSerialComm: Terminated

BUILD SUCCESSFUL in 22s
2 actionable tasks: 2 executed
9:19:00 PM: Task execution finished 'Launcher.main()'.
```
The transmitted value here is [`30ad`] which the hexdecimal code for [`0\n\r`]

| [0x30] | [0x0a] | [0x0d] |
|--------|--------|--------|
| `0`   | `\n` | `\r` |
