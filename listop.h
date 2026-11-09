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

void ListInit   (list_t* list, int capacity);
void ListAdd    (list_t* list, int value,    int position);
void ListDelete (list_t* list, int position);
ON_DBG(
int  ListVerify (list_t* list);)

#endif
