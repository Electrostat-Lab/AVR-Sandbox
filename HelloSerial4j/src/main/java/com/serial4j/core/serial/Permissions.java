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
package com.serial4j.core.serial;

/**
 * Provides Unix file system permissions for the specified serial port
 * of the terminal device.
 * 
 * @author pavl_g.
 */
public final class Permissions {

    public static final Permissions O_RDONLY = new Permissions(00, "Read Only");
    public static final Permissions O_WRONLY = new Permissions(01, "Write Only");
    public static final Permissions O_RDWR = new Permissions(02, "Read/Write");
    public static final Permissions O_NOCTTY = new Permissions(0400, "No Control terminal device");
    public static final Permissions O_NONBLOCK = new Permissions(04000, "");

    private final int value;
    private final String description;

    private Permissions(final int value, final String description) {
        this.value = value;
        this.description = description;
    }
    
    public static final Permissions createCustomPermissions(final int value, final String description) {
        return new Permissions(value, description);
    }

    public int getValue() {
        return value;
    }

    public String getDescription() {
        return description;
    }
}
