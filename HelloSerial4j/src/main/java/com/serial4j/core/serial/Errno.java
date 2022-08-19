package com.serial4j.core.serial;

public enum Errno {
    ENOENT(2, "No Such file or directory"),
    EACCES(13, "Permission denied"),
    EPIPE(32, "Broken pipe");

    private final int value;
    private final String description;

    Errno(final int value, final String description) {
        this.value = value;
        this.description = description;
    }

    public int getValue() {
        return value;
    }

    public String getDescription() {
        return description;
    }
}
