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
#define MEGADUMP
#ifdef MEGADUMP
#define ADV_DUMP(...) __VA_ARGS__
#else
#define ADV_DUMP(...)
#endif

void ListInit        (list_t* list,   int  capacity                          ADV_DUMP(, FILE* file, int* dump_num, int line, const char* fname, const char* func));
void ListInsertHead  (list_t* list,   int  value,      int  position         ADV_DUMP(, FILE* file, int* dump_num, int line, const char* fname, const char* func));
void ListInsertBefore(list_t* list,   int  value,      int  position         ADV_DUMP(, FILE* file, int* dump_num, int line, const char* fname, const char* func));
void ListInsertAfter (list_t* list,   int  value,      int  position         ADV_DUMP(, FILE* file, int* dump_num, int line, const char* fname, const char* func));
void ListDelete      (list_t* list,   int  position                          ADV_DUMP(, FILE* file, int* dump_num, int line, const char* fname, const char* func));
void ListDataSort    (list_t* list,   bool (*CompFunc)(int first, int second)ADV_DUMP(, FILE* file, int* dump_num, int line, const char* fname, const char* func));
void SwapValues      (int*    value1, int* value2);
int  CheckDataOrder  (list_t  list);
bool CompareUp       (int     first,  int  second);
bool CompareDown     (int     first,  int  second);
void ListInsert      (list_t* list,   int  value,      int position);
ON_DBG(
int  ListVerify      (list_t* list);)

#endif
