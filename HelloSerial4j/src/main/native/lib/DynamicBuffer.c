#include<DynamicBuffer.h>

int DynamicBuffer::add(void* item) {
    buffer[count] = (void*) calloc(1, sizeof(void*));
    buffer[count] = item;
    count++;
    return 1;
} 

int DynamicBuffer::remove(int index) {
    BufferUtils::nullifyBuffer(buffer, index);
    BufferUtils::reValidateBuffer(buffer, getItemsCount(), &(this->isProcessed));
    
    while (!this->isProcessed);
    this->isProcessed = 0;
    
    count--;
    return OPERATION_SUCCEEDED;
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
