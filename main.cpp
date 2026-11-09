#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "struct.h"
#include "graphics.h"
#include "listop.h"
// DONE TODO: быстрый алгоритм поиска свободных элементов
// DONE TODO: верификатор (head + tail, всевозможные проверки)
// DONE TODO: добавить больше информации на дампе, поменять местами next и prev
// TODO: закольцевать список??
int main()
{
    int capacity = 15;
    int dump_num = 0;
    list_t list = {};
    ListInit(&list, capacity);

    FILE* file = DumpBegin();

    ListDump(file, list, capacity, &dump_num);
    for (int num = 1; num < 8; num++)
    {
        ListAdd(&list, num * 10, num - 1);
        ListDump(file, list, capacity, &dump_num);
    }
    ListAdd(&list, 35, 3);
    ListDump(file, list, capacity, &dump_num);
    ListDelete(&list, 4);
    ListDump(file, list, capacity, &dump_num);
    ListDelete(&list, 1);
    ListDump(file, list, capacity, &dump_num);
    ListDelete(&list, 7);
    ListDump(file, list, capacity, &dump_num);
    DumpEnd(file);

    free(list.data);
    free(list.next);
    free(list.prev);
    return 0;
}
