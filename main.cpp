#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "struct.h"
#include "graphics.h"
#include "listop.h"
// TODO: закольцевать список, чтобы не было условных конструкций при добавлении нового элемента и удаления
// TODO: Разбить функцию ListAdd на ListInsertBefore и ListInsertAfter для удобства.
// TODO: Сделать функцию сортировки массива написанную пользователем через твой API.
// TODO: Условная компиляция дампа
// TODO: Сортировка
int main()
{
    int capacity = 15;
    int dump_num = 0;
    list_t list = {};
    ListInit(&list, capacity);

    FILE* file = DumpBegin();

    ListDump(file, list, capacity, &dump_num);
    ListInsertHead(&list, 10, 1);
    ListDump(file, list, capacity, &dump_num);
    int value = 0;
    for (int num = 1; num < 7; num++)
    {
        value = 10 * num;
        if (num % 2 == 1)
        {
            value *= -1;
        }
        ListInsertAfter(&list, value, num);
        // ListDump(file, list, capacity, &dump_num);
    }
    ListDump(file, list, capacity, &dump_num);
    ListDataSort(file, &list, capacity, &dump_num);
    ListDump(file, list, capacity, &dump_num);
    DumpEnd(file);

    free(list.data);
    free(list.next);
    free(list.prev);
    return 0;
}
