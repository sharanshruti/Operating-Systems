#include "mem.h"

int last = 0;
unsigned short bitmap[BITMAPSIZE];

char *mm;

int init_alloc() {
    mm = mmap(NULL, MEMSIZE, 
            PROT_WRITE | PROT_READ, 
            MAP_ANONYMOUS | MAP_PRIVATE, 
            0, 0);
    for (int i = 0; i < BITMAPSIZE; i++)
        bitmap[i] = 0;
    return (int) *mm;
}

char *alloc(int size) {
    for (int i = last, j = 0; i < BITMAPSIZE; i = j + 1)
        for (j = i; j < BITMAPSIZE && bitmap[j] == 0; j++)
            if ((j - i + 1) * MINBUFSIZE >= size)
            {
                bitmap[i] = j;
                for (int k = i+1; k <= j; k++)
                    bitmap[k] = 1;
                return mm + i * 8;
            }
    return NULL;
}

void dealloc(char *buf) {
    int i = (buf - mm) / 8;
    int len = bitmap[i];
    for (; i <= len; i++)
        bitmap[i] = 0;
}

int cleanup() {
    return munmap(mm, MEMSIZE);
}