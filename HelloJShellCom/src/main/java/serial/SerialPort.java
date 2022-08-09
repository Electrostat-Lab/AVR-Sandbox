package serial;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;

public final class SerialPort {

    private final String portDescription;
    private String superuserPassword;
    private int baudRate;
    private InputStream inputStream;
    private final ArrayList<Integer> ERRNO = new ArrayList<>();
    private String[] environments = new String[] {"/bin/sh"};

    public SerialPort(final String portDescription, final int baudRate) {
        this.portDescription = portDescription;
        this.baudRate = baudRate;
    }

    public void initPort(final String superuserPassword) throws IOException {
        this.superuserPassword = superuserPassword;

        final Process initProcess = Runtime.getRuntime().exec("echo "+ superuserPassword + " | sudo -S " + getInitPortScript(superuserPassword, portDescription, baudRate), getEnvironments());
        final InputStream initProcessStream = initProcess.getInputStream();
        while (initProcessStream.available() > 0) {
            ERRNO.add(initProcessStream.read());
        }
    }

    public void openPort() throws IOException {
        final Process readProcess = Runtime.getRuntime().exec("sudo "+ superuserPassword + " " + getReadPortScript(portDescription, baudRate), getEnvironments());
        inputStream = readProcess.getInputStream();
    }

    public void writeToPort(final String data) throws IOException {
        Runtime.getRuntime().exec(getWritePortScript(superuserPassword, portDescription, data), getEnvironments());
    }

    public void setEnvironments(String[] environments) {
        this.environments = environments;
    }

    public ArrayList<Integer> getERRNO() {
        return ERRNO;
    }

    public String[] getEnvironments() {
        return environments;
    }

    public void setBaudRate(int baudRate) {
        this.baudRate = baudRate;
    }

    public int getBaudRate() {
        return baudRate;
    }

    public InputStream getInputStream() {
        return inputStream;
    }

    private String getWritePortScript(String superuserPassword, String port, String data) {
        return SerialPort.class.getResource("/writeToTTL.sh").getFile() + " " + superuserPassword
                + " " + port + " " + data;
    }

    private String getInitPortScript(String superuserPassword, String port, int baudRate) {
        return SerialPort.class.getResource("/initPort.sh").getFile() + " " + superuserPassword
                + " " + port + " " + baudRate;
    }

    private String getReadPortScript(String port, int baudRate) {
        return SerialPort.class.getResource("/readFromTTL.sh").getFile() + " " + port + " " + baudRate;
    }
}
