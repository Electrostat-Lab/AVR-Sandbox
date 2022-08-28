/**
 * @file BufferUtils.util
 * @author pavl_g.
 * @brief Represents utility functions for buffers.
 * @version 0.1
 * @date 2022-08-24
 * 
 * @copyright 
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
#ifndef BUFFER_UTILS
#define BUFFER_UTILS

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>

namespace BufferUtils {

    /**
     * @brief Deletes a typified buffer.
     * 
     * @param buffer the buffer to delete.
     */
    static inline void deleteBuffer(void* buffer) {
        free(buffer);
        buffer = NULL;
    }
    
    /**
     * @brief Deeply copies the data of the [src] buffer into a new
     * buffer and returns it.
     * 
     * @param src the source buffer to get the data from.
     * @param count the count length of the buffer.
     * @return void** a new buffer with the same data as the source.
     */
    static inline void** copy(void** src, int count) {
        void** copy = (void**) calloc(1, sizeof(void*));
        for (int i = 0; i < count; i++) {
            copy[i] = (void*) calloc(1, sizeof(void*));
            copy[i] = src[i];
        }
        return copy;
    }

    /**
     * @brief Re-validates the buffer from [NULL] pointers.
     * 
     * @param buffer the buffer to re-validate.
     * @param count the pointers count.
     */
    static inline void reValidateBuffer(void** buffer, int* count) {
        /* get a temp copy from flagged buffer */
        void** temp = BufferUtils::copy(buffer, *count);
        for (int i = 0, j = 0; i < *count; i++) {
            if (temp[i] == 0) {
                continue;
            }
            buffer[j] = temp[i];
            j++;
        }
        BufferUtils::deleteBuffer(*temp);
    }
}
#endif