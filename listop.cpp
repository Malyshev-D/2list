#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define POISON 0x2DA115FD // 765531645

#include "struct.h"
#include "listop.h"
#include "graphics.h"

void ListDataSort(FILE*  file, list_t* list, int size, int* dump_num)
{
    int next = 0;
    int head = list->next[0];
    for (int nPass = 0; nPass < list->size - 1; nPass++)
    {
        head = list->next[0];
        for (int idx = head; idx < list->size - 1 - nPass; idx ++)
        {
            next = list->next[idx];
            if (list->data[idx] > list->data[next])
            {
                SwapValues(list->data + idx, list->data + next);
            }
        }
        ListDump(file, *list, size, dump_num);
    }
}

void SwapValues(int* value1, int* value2)
{
    int temp = *value2;
    *value2 = *value1;
    *value1 = temp;
}

void ListInsertHead(list_t* list, int value, int position)
{
    ON_DBG(
    if (ListVerify != NOERROR)
        return ;
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
}

void ListInsertBefore(list_t* list, int value, int position) // добавление элемента по значению и номеру предыдущего элемента
{
    ON_DBG(
    if (ListVerify != NOERROR)
        return ;
    )

    int free = list->free;
    list->free = list->next[free];

    list->data[free] = value;
    list->next[list->prev[position]] = free;
    list->prev[free] = list->prev[position];
    list->next[free] = position;
    list->prev[position] = free;
    list->prev[0] = list->prev[list->next[0]]; // синхронизация head и tail
    list->size++;

    ON_DBG(
    if (ListVerify != NOERROR)
        return ;
    )
}

void ListInsertAfter(list_t* list, int value, int position) // добавление элемента по значению и номеру предыдущего элемента
{
    ON_DBG(
    if (ListVerify != NOERROR)
        return ;
    )

    int free = list->free;
    list->free = list->next[free];

    list->data[free] = value;
    list->prev[list->next[position]] = free;
    list->prev[free] = position;
    list->next[free] = list->next[position];
    list->next[position] = free;
    list->prev[0] = list->prev[list->next[0]];
    list->size++;

    ON_DBG(
    if (ListVerify != NOERROR)
        return ;
    )
}

void ListDelete(list_t* list, int position) // удаление элемента по индексу
{
    ON_DBG(
    if (ListVerify != NOERROR)
    {
        return ;
    })
    if (list->size == 0)
    {
        printf("NOTHING TO DELETE\n");
        return ;
    }

    if (list->next[0] == position)
    {
        list->next[0] = list->next[position];
    }

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
    {
        return ;
    })
}

void ListInit(list_t* list, int capacity) // создание списка
{
    list->data = (int*)calloc(capacity + 1, sizeof(int));
    assert(list->data != 0);
    list->next = (int*)calloc(capacity + 1, sizeof(int));
    assert(list->next != 0);
    list->prev = (int*)calloc(capacity + 1, sizeof(int));
    assert(list->prev != 0);

    list->data[0] = POISON;
    list->next[0] = 0;
    list->prev[0] = 0;
    // list->head = 0;
    // list->tail = 0;

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
}

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
