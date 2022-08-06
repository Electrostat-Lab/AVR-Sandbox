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

