#ifndef DY_BUFFER

#define DY_BUFFER 1

#include<stdlib.h>

struct DynamicBuffer {
    int count = 0;
    void** buffer = (void**) calloc(1, sizeof(void*));

    void** getBuffer() {
        return buffer;
    }

    int& getItemsCount();

    int add(void* item);

    int remove(void* item);

    int getItemIndex(void* item);

    void* getItem(int index);
};


#endif