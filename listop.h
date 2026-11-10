#ifndef LISTOPERATIONS
#define LISTOPERATIONS

enum error_value {
    NOERROR,
    ZEROLIST,
    ZERODATA,
    ZERONEXT,
    ZEROPREV,
    UNLINKED,
    NEGCAPACITY,
    NEGSIZE,
    OVERFLOW,
    WRONGFREE
};

#ifdef DEBUG_MODE
#define ON_DBG(...) __VA_ARGS__
#else
#define ON_DBG(...)
#endif

#ifdef MEGADUMP
#define ADV_DUMP(...) __VA_ARGS__
#else
#define ADV_DUMP(...)
#endif

void ListInit        (list_t* list,   int capacity);
void ListInsertHead  (list_t* list,   int value,    int position);
void ListInsertBefore(list_t* list,   int value,    int position);
void ListInsertAfter (list_t* list,   int value,    int position);
void ListDelete      (list_t* list,   int position);
void ListDataSort    (FILE*   file,   list_t* list, int size, int* dump_num);
void SwapValues      (int*    value1, int* value2);
ON_DBG(
int  ListVerify      (list_t* list);)

#endif
