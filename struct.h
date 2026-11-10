#ifndef LIST_STRUCTURE
#define LIST_STRUCTURE

struct list_t
{
    int* data;
    int* next;
    int* prev;
    int  capacity;
    int  size;
    int  free;
    int  last_free;
};

#endif
