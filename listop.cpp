#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define POISON 0x2DA115FD // 765531645

#include "struct.h"
#include "listop.h"
#include "graphics.h"

// сортировка значений
void ListDataSort(list_t* list, bool (*CompFunc)(int first, int second) ADV_DUMP(, FILE* file, int* dump_num, int line, const char* fname, const char* func))
{
    ADV_DUMP(
    fprintf(file,
        "<hr>\n"
        "<div class=\"cmd\">The command ListDataSort() was called in %s %s:%d </div>\n"
        "<h3>Before</h3>\n",
        fname, func, line);
    ListDump(file, *list, dump_num);
    )
    int next = 0;
    int head = list->next[0];
    int current = head;
    for (int nPass = 0; nPass < list->size - 1; nPass++)
    {
        head = list->next[0];
        current = head;
        for (int idx = 0; idx < list->size - 1 - nPass; idx ++)
        {
            next = list->next[current];
            if (CompFunc(list->data[current],list->data[next]))
            {
                SwapValues(list->data + current, list->data + next);
            }
            current = next;
        }
        if (CheckDataOrder(*list) == 1)
        {
            break;
        }
    }
    ADV_DUMP(
    fprintf(file, "<h3>After</h3>\n");
    ListDump(file, *list, dump_num);
    )
}
// компаратор по возрастанию
bool CompareUp(int first, int second)
{
    return (first > second);
}
// компаратор по убыванию
bool CompareDown(int first, int second)
{
    return (first < second);
}
// проверка на правильный порядок значений
int CheckDataOrder(list_t list)
{
    int next = 0;
    int current = list.next[0];
    for (int idx = 0; idx < list.size - 1; idx++)
    {
        next = list.next[current];
        if (list.data[current] > list.data[next])
        {
            return 0;
        }
        current = next;
    }
    return 1;
}
// обмен значениями
void SwapValues(int* value1, int* value2)
{
    int temp = *value2;
    *value2 = *value1;
    *value1 = temp;
}
// добавление первого элемента
void ListInsertHead(list_t* list, int value, int position ADV_DUMP(, FILE* file,   int* dump_num, int  line, const char* fname, const char* func))
{
    ON_DBG(
    if (ListVerify != NOERROR)
        return ;
    )

    ADV_DUMP(
    fprintf(file,
        "<hr>\n"
        "<div class=\"cmd\">The command ListInsertHead(value = %d, position = %d) was called in %s %s:%d </div>\n",
        value, position, fname, func, line);
    fprintf(file, "<h3>Before</h3>\n");
    ListDump(file, *list, dump_num);
    )
    list->free = list->next[position];

    list->data[position] = value;
    list->next[0] = position;
    list->prev[0] = position;
    list->next[position] = position;
    list->prev[position] = position;
    list->size++;

    ON_DBG(
    if (ListVerify != NOERROR)
        return ;
    )
    ADV_DUMP(
    fprintf(file, "<h3>After</h3>\n");
    ListDump(file, *list, dump_num);
    )
}
// добавление элемента по значению и номеру следующего элемента
void ListInsertBefore(list_t* list, int value, int position ADV_DUMP(, FILE* file, int* dump_num, int line, const char* fname, const char* func))
{
    ON_DBG(
    if (ListVerify != NOERROR)
        return ;
    )

    ADV_DUMP(
    ListDump(file, *list, dump_num);
    fprintf(file,
        "<hr>\n"
        "<div class=\"cmd\">The command ListInsertBefore(value = %d, position = %d) was called in %s %s:%d </div>\n",
        value, position, fname, func, line);
    fprintf(file, "<h3>Before</h3>\n");
    )

    ListInsert(list, value, list->prev[position]);

    ON_DBG(
    if (ListVerify != NOERROR)
        return ;
    )
    ADV_DUMP(
    fprintf(file, "<h3>After</h3>\n");
    ListDump(file, *list, dump_num);
    )
}
// добавление элемента по значению и номеру предыдущего элемента
void ListInsertAfter(list_t* list, int value, int position ADV_DUMP(, FILE* file, int* dump_num, int line, const char* fname, const char* func))
{
    ON_DBG(
    if (ListVerify != NOERROR)
        return ;)

    ADV_DUMP(
    fprintf(file,
        "<hr>\n"
        "<div class=\"cmd\">The command ListInsertAfter(value = %d, position = %d) was called in %s %s:%d </div>\n",
        value, position, fname, func, line);
    fprintf(file, "<h3>Before</h3>\n");
    ListDump(file, *list, dump_num);)

    ListInsert(list, value, position);

    ON_DBG(
    if (ListVerify != NOERROR)
        return ;)

    ADV_DUMP(
    fprintf(file, "<h3>After</h3>\n");
    ListDump(file, *list, dump_num);)
}
// вставка после элемента position
void ListInsert(list_t* list, int value, int position)
{
    int free = list->free;
    list->free = list->next[free];

    list->data[free] = value;
    list->prev[list->next[position]] = free;
    list->prev[free] = position;
    list->next[free] = list->next[position];
    list->next[position] = free;
    list->prev[0] = list->prev[list->next[0]];
    list->size++;
}
// удаление элемента по индексу
void ListDelete(list_t* list, int position ADV_DUMP(, FILE* file, int* dump_num, int line, const char* fname, const char* func)) // удаление элемента по индексу
{
    ON_DBG(
    if (ListVerify != NOERROR)
        return ; )

    ADV_DUMP(
    fprintf(file,
        "<hr>\n"
        "<div class=\"cmd\">The command ListDelete(position = %d) was called in %s %s:%d </div>\n",
        position, fname, func, line);
    fprintf(file, "<h3>Before</h3>\n");
    ListDump(file, *list, dump_num); )

    if (list->size == 0)
    {
        printf("NOTHING TO DELETE\n");
        return ;
    }

    if (list->next[0] == position)
        list->next[0] = list->next[position];

    list->next[list->prev[position]] = list->next[position];
    list->prev[list->next[position]] = list->prev[position];
    list->prev[position] = -1;
    list->next[position] = 0;
    list->last_free = position;

    list->size--;
    list->next[list->last_free] = position;
    list->prev[0] = list->prev[list->next[0]];

    ON_DBG(
    if (ListVerify != NOERROR)
        return ; )

    ADV_DUMP(
    fprintf(file, "<h3>After</h3>\n");
    ListDump(file, *list, dump_num); )
}
// создание списка
void ListInit(list_t* list, int capacity ADV_DUMP(, FILE* file, int* dump_num, int line, const char* fname, const char* func))
{
    ADV_DUMP(
    fprintf(file, "<div class=\"cmd\">The command ListInit(capacity = %d) was called in %s %s:%d </div>\n",
    capacity, fname, func, line); )

    list->data = (int*)calloc(capacity + 1, sizeof(int));
    assert(list->data != 0);
    list->next = (int*)calloc(capacity + 1, sizeof(int));
    assert(list->next != 0);
    list->prev = (int*)calloc(capacity + 1, sizeof(int));
    assert(list->prev != 0);

    list->data[0] = POISON;
    list->next[0] = 0;
    list->prev[0] = 0;
    list->free = 1;
    for (int idx = 1; idx < capacity; idx++)
    {
        list->data[idx] = POISON;
        list->next[idx] = idx + 1; // при использовании free переходит на next[free]
        list->prev[idx] = -1;
    }
    list->prev[capacity] = -1;
    list->last_free = capacity;
    list->capacity = capacity;

    ADV_DUMP(
    ListDump(file, *list, dump_num);)
}
// верификатор
ON_DBG(
int ListVerify(list_t* list)
{
    if (list == NULL)
    {
        printf("LIST IS NULL\n");
        return ZEROLIST;
    }
    if (list->data == NULL)
    {
        printf("DATA IS NULL\n");
        return ZERODATA;
    }
    if (list->next == NULL)
    {
        printf("NEXT IS NULL\n");
        return ZERONEXT;
    }
    if (list->prev == NULL)
    {
        printf("PREV IS NULL\n");
        return ZEROPREV;
    }
    if (list->capacity < 0)
    {
        printf("NEGATIVE CAPACITY\n");
        return NEGCAPACITY;
    }
    if (list->size < 0)
    {
        printf("NEGATIVE SIZE\n");
        return NEGSIZE;
    }
    if (list->size > list->capacity)
    {
        printf("SIZE IS BIGGER THAN CAPACITY\n");
        return OVERFLOW;
    }
    if (list->prev[list->free] != -1 || list->prev[list->last_free] != -1)
    {
        printf("INCORRECT FREE ELEMENT\n");
        return WRONGFREE;
    }

    int current = list->head;
    if (current != 0)
    {
        for (int count = 0; count < list->size; count++)
        {
            current = list->next[current];
        }
        if (current != list->tail)
        {
            printf("LIST IS NOT LINKED\n");
            return UNLINKED;
        }
    }
}
)
