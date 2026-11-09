#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define POISON 0x2DA115FD // 765531645

#include "struct.h"
#include "listop.h"

void ListAdd(list_t* list, int value, int position) // добавление элемента по значению и номеру предыдущего элемента
{
    if (list->free == list->last_free)
    {
        printf("List is full, please free some cells\n");
        return ;
    }
    else if (list->head == 0)
    {
        list->head = 1;
        list->data[1] = value;
        list->prev[1] = 0;
        list->free = list->next[1];
        list->next[1] = 0;
        list->tail = 1;
    }
    else if (list->tail == position) // надо поставить в конец
    {
        int free = list->free; // ячейка, на которую ставим число
        list->data[free] = value;
        list->prev[free] = position;
        list->free = list->next[free];
        list->next[free] = list->next[position];
        list->next[position] = free;
        list->tail = free;
    }
    else // типичный случай:  находим первую свободную ячейку, ставим туда число
    {
        int free = list->free;
        list->data[free] = value;
        list->prev[list->next[position]] = free;
        list->prev[free] = position;
        list->free = list->next[free];
        list->next[free] = list->next[position];
        list->next[position] = free;
    }
}

void ListDelete(list_t* list, int position) // удаление элемента по индексу
{
    list->next[list->prev[position]] = list->next[position];
    list->prev[list->next[position]] = list->prev[position];
    list->next[list->last_free] = position;
    list->prev[position] = -1;
    list->next[position] = 0;
    list->last_free = position;
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
    list->head = 0;
    list->tail = 0;

    list->free = 1;
    for (int idx = 1; idx < capacity; idx++)
    {
        list->next[idx] = idx + 1; // при использовании free переходит на next[free]
        list->prev[idx] = -1;
    }
    list->prev[capacity] = -1;
    list->last_free = capacity;
    list->capacity = capacity;
}
