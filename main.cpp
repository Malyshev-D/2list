#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "struct.h"
#include "graphics.h"
#include "listop.h"
// DONE TODO: закольцевать список, чтобы не было условных конструкций при добавлении нового элемента и удаления
// DONE TODO: Разбить функцию ListAdd на ListInsertBefore и ListInsertAfter для удобства.
// DONE TODO: Сделать функцию сортировки массива написанную пользователем через API.
// DONE TODO: Условная компиляция дампа
// done TODO: Сортировка
int main()
{
    int capacity = 15;
    int dump_num = 0;
    list_t list = {};
    FILE* file = DumpBegin();
    ListInit(&list, capacity, file, &dump_num, __LINE__, __FILE__, __FUNCTION__);
    ListInsertHead(&list, 10, 1, file, &dump_num, __LINE__, __FILE__, __FUNCTION__);

    int value = 0;
    for (int num = 1; num < 7; num++)
    {
        value = 10 * num;
        if (num % 2 == 1)
        {
            value *= -1;
        }
        ListInsertAfter(&list, value, num, file, &dump_num, __LINE__, __FILE__, __FUNCTION__);
    }

    ListDataSort(&list, CompareDown, file, &dump_num, __LINE__, __FILE__, __FUNCTION__);
    DumpEnd(file);

    free(list.data);
    free(list.next);
    free(list.prev);
    return 0;
}
