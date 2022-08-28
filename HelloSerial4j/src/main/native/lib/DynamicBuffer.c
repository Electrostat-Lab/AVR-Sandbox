#include<DynamicBuffer.h>

int DynamicBuffer::add(void* item) {
    buffer[count] = (void*) calloc(1, sizeof(void*));
    buffer[count] = item;
    count++;
    return 1;
} 

int DynamicBuffer::remove(int index) {
    buffer[index] = 0;
    BufferUtils::reValidateBuffer(buffer, getItemsCount());

    count--;
    return 0;
}

void* DynamicBuffer::getItem(int index) {
    return buffer[index];
}

int DynamicBuffer::getItemIndex(void* item) {
    for (int i = 0; i < *getItemsCount(); i++) {
        if (buffer[i] == item) {
            return i;
        }
    }
    return OPERATION_FAILED;
}

int* DynamicBuffer::getItemsCount() {
    return &count;
}
