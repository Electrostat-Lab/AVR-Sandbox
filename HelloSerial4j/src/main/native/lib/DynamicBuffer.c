#include<DynamicBuffer.h>

int DynamicBuffer::add(void* item) {
    void** temp = buffer;
    buffer[count] = (void*) calloc(1, sizeof(void));
    buffer[count] = item;
    count++;
    return 1;
} 

int DynamicBuffer::remove(void* item) {
    return 0;
}

void* DynamicBuffer::getItem(int index) {
    return buffer[index];
}

int DynamicBuffer::getItemIndex(void* item) {
    return 0;
}

int& DynamicBuffer::getItemsCount() {
    return count;
}
