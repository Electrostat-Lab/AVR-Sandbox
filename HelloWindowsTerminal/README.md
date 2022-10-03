# <img src="https://user-images.githubusercontent.com/60224159/193262155-bf82f982-e84d-4af4-835f-152c8e923f60.png" width="40" height="30"> Windows Terminal
## Steps to use WSL on Windows terminal to compile, hex and upload code for avr chips

1) Enable WSL (Windows Subsystem for linux) microsoft widows feature.

| `Access Windows program features list` | `Enabling the WSL feature` |
|---------------------------------------|-----------------------------|
| ![image-1](https://user-images.githubusercontent.com/60224159/193261736-e008010f-1cc3-4996-8881-93f3e0919d07.png) | ![image-2](https://user-images.githubusercontent.com/60224159/193261758-483a1058-ed42-46d4-a196-b4f4c6cd13e9.png) |

2) Download WSL from the command prompt or MS powershell using:

```
C:\Users\pavl_g> wsl --install
```

3) Download usbipd 3rd party utility using the latest github `.msi` file or the windows package manager directly via the command prompt:

```
C:\Users\pavl_g> winget install usbipd
The `msstore` source requires that you view the following agreements before using.
Terms of Transaction: https://aka.ms/microsoft-store-terms-of-transaction
The source requires the current machine's 2-letter geographic region to be sent to the backend service to function properly (ex. "US").

Do you agree to all the source agreements terms?
[Y] Yes  [N] No: Y
Found usbipd-win [dorssel.usbipd-win] Version 2.3.0
This application is licensed to you by its owner.
Microsoft is not responsible for, nor does it grant any licenses to, third-party packages.
Downloading https://github.com/dorssel/usbipd-win/releases/download/v2.3.0/usbipd-win_2.3.0.msi
  ██████████████████████████████  10.4 MB / 10.4 MB
Successfully verified installer hash
Starting package install...
Successfully installed
```

4) Download debian linux image and install libusb utilities and other usbip utilities from the apt package manager: 

```
C:\Users\pavl_g> wsl --install -d debian
```

5) Set it as the default linux distribution using: 

```
C:\Users\pavl_g> wsl --setdefault debian
```

6) Now open a windows terminal tap and start a debian session to setup your user and root accounts.

7) Now update the apt package manager and install the libusb utils via:

```bash
pavl_g@pavl-machine:~$ sudo apt-get update
pavl_g@pavl-machine:~$ sudo apt-get install usbutils
```

8) Now download usbip for debian via: 

```bash
pavl_g@pavl-machine:~$ sudo apt install usbip hwdata usbutils
```

9) Now start an administrator command prompt session alongside with the original debian session, then connect your usb device and run the following: 


- On the Debian session:
```bash
pavl_g@pavl-machine:~$ lsusb
Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
```

- On the cmd session:
```
C:\Users\pavl_g>usbipd wsl list
BUSID  VID:PID    DEVICE                                                        STATE
1-1    1a86:7523  USB-SERIAL CH340 (COM3)                                       Not attached
1-2    12c9:102a  USB Input Device                                              Not attached
1-5    0bda:5689  Integrated Webcam                                             Not attached
1-6    0bda:0129  Realtek USB 2.0 Card Reader                                   Not attached
1-8    8087:0a2a  Intel(R) Wireless Bluetooth(R)                                Not attached
```
In this case, i am trying to connect the USB-SERIAL CH340 (COM3) device to my debian wsl image.

- Now attach the serial device with `BUSID` to the debian virtual machine using:
```
C:\Users\pavl_g>usbipd wsl attach -b 1-1 -d debian
```

- On the debian session:
```
pavl_g@pavl-machine:~$ lsusb
Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
Bus 001 Device 013: ID 1a86:7523 QinHeng Electronics CH340 serial converter
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
```
And, here is our port for the serial device: 
```
pavl_g@pavl-machine:~$ ls /dev/ttyUSB*
/dev/ttyUSB0
```

10) Now clone the git repo and start development using the Ccoffee build script.

```bash
git clone https://github.com/Software-Hardware-Codesign/AVR-Sandbox.git
```
----------------------------------------------------------------------------------------------------

### For more refer to the documentation pages:
- [A quick tour around](https://www.linkedin.com/feed/update/urn:li:activity:6981421099192340480/)
- [Windows-Terminal-Documentation](https://learn.microsoft.com/en-us/windows/terminal/)
- [WSL-Documentation](https://learn.microsoft.com/en-us/windows/wsl/)
- [Usbipd-Wiki](https://github.com/dorssel/usbipd-win/wiki)
- [Windows-Package-Manager-Documentation](https://learn.microsoft.com/en-us/windows/package-manager/winget/)
- [Debian-Documentation](https://wiki.debian.org/FrontPage)
- [Apt-Documentation](https://wiki.debian.org/Apt)
