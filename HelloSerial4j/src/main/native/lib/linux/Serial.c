#include<Serial.h>

int& Terminal::TerminalControl::openPort(const char* port) {
    this->portFileDescriptor = open(port, DEFAULT_FLAG);
    return this->portFileDescriptor;
}

int Terminal::TerminalControl::fetchSerialPorts() {
    DIR* dirp = opendir(DEVICES_DIR);
    
    /* sanity check the input */
    if (dirp == NULL) {
        return ERR_INVALID_DIR;
    }

    struct dirent* dp = (struct dirent*) calloc(1, sizeof(struct dp*));
    struct stat filestat;

    /* start reading available ports */
    for (long count = 0; (dp = readdir(dirp)) != NULL;) {
        char* port = (char*) calloc(1, sizeof(char));
        port = concatIntoDevice(port, dp->d_name);
        if (!isSerialPort(port)) {
            continue;
        }
        (this->serialPorts).add(port);

        free(port);
        port = NULL;
        ++count;
    }

    closedir(dirp);

    if ((this->serialPorts).getItem(0) == NULL) {
        return ERR_NO_RESULT;
    }

    return OPERATION_SUCCEEDED;
}

int Terminal::TerminalControl::initTermios() {
    if (this->portFileDescriptor <= 0) {
        return ERR_INVALID_PORT;
    }

    /* initialize the teletype terminal port */
    tcgetattr(this->portFileDescriptor, &(this->tty));

    /* setup tty attributes */
    this->tty.c_cflag &= ~(CBAUDEX | CBAUD); /* clear BAUDs */
    this->tty.c_cflag |= (CREAD | CS8 | CLOCAL); /* set flags */
    this->tty.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHOKE | ECHONL | ECHOPRT | ECHOCTL | ISIG | IEXTEN);
    this->tty.c_oflag &= ~(OPOST | ONLCR);
    this->tty.c_iflag = 0x00;
    this->tty.c_cc[VTIME] = 0;
    this->tty.c_cc[VMIN] = 1;

    /* apply attriutes flag bits */

    return tcsetattr(this->portFileDescriptor, TCSAFLUSH, &(this->tty));
}

int Terminal::TerminalControl::setBaudRate(int baudRate) {
    if (this->portFileDescriptor <= 0) {
        return ERR_INVALID_PORT;
    }
    cfsetspeed(&(this->tty), baudRate);
    return tcsetattr(this->portFileDescriptor, TCSAFLUSH, &(this->tty));
}

speed_t Terminal::TerminalControl::getBaudRate() {
    if (this->portFileDescriptor <= 0) {
        return ERR_INVALID_PORT;
    }
    return cfgetospeed(&(this->tty));
}

ssize_t Terminal::TerminalControl::writeData() {
    if (this->portFileDescriptor < 0) {
        return ERR_INVALID_PORT;
    }
    return write(this->portFileDescriptor, (void*) this->writeBuffer, BUFFER_SIZE);
}

ssize_t Terminal::TerminalControl::readData() {
    if (this->portFileDescriptor < 0) {
        return ERR_INVALID_PORT;
    }
    return read(this->portFileDescriptor, (void*) this->readBuffer, BUFFER_SIZE);
}

int Terminal::TerminalControl::closePort() {
    if (this->portFileDescriptor < 0) {
        return ERR_INVALID_PORT;
    }
    return close(this->portFileDescriptor);
} 

int& Terminal::TerminalControl::getPortFileDescriptor() {
    return this->portFileDescriptor;
}

int& Terminal::TerminalControl::getErrno() {
    return errno;
}