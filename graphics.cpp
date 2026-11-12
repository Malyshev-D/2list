#include <stdio.h>
#include <stdlib.h>

const char graph_code[] = "meow.txt";
const char html_code[]  = "meow.html";

#include "struct.h"
#include "graphics.h"

// начало дампа = создание файла
FILE* DumpBegin()
{
    FILE* file = fopen(html_code, "w");
    fprintf(file, "<!DOCTYPE html>\n"
        "<head>\n"
        "\t<title>List Dump</title>\n"
        "\t<link rel=\"stylesheet\" href=\"style.css\">\n"
        "</head>\n"
    );
    return file;
}
// окончание дампа = вызываем system()
void DumpEnd(FILE* file)
{
    fprintf(file,
    "</body>\n"
    "</html>\n");
    fclose(file);
    system("start meow.html");
}
// добавление таблиц и графов
void ListDump(FILE* file, list_t list, int* dump_num)
{
    CreateGraph(list);
    // snprintf() - создаем форматированную строку и вставляем в system
    char command[150] = {};
    snprintf(command, sizeof(command), "dot -Tpng meow.txt -o meow%d.png", *dump_num);
    system(command);
    CreateHtml(file, list, *dump_num);
    (*dump_num)++;
}
// запись в html
void CreateHtml(FILE* file, list_t list, int dump_num)
{
    fprintf(file, "<!DOCTYPE html>\n"
        "<head>\n"

        "\t<title>List Dump</title>\n"
        "\t<link rel=\"stylesheet\" href=\"style.css\">\n"
        "</head>\n"
    );
    fprintf(file, "<body>\n"
        "\t<h1>List Structure</h1>\n"
        "\t<div class=\"list\">\n"
        "\t<div class=\"column\">\n"
        "\t\t<div class=\"head\">Index</div>\n"
        "\t\t<div class=\"head\">Data</div>\n"
        "\t\t<div class=\"head\">Next</div>\n"
        "\t\t<div class=\"head\">Prev</div>\n"
        "\t</div>\n"
    );
    for (int idx = 0; idx <= list.capacity; idx++)
    {
        fprintf(file,
        "\t<div class=\"column\">\n"
        "\t\t<div class=\"head\">%d</div>\n"
        "\t\t<div class=\"cell\">%d</div>\n"
        "\t\t<div class=\"cell\">%d</div>\n"
        "\t\t<div class=\"cell\">%d</div>\n"
        "\t</div>\n",
        idx, list.data[idx], list.next[idx], list.prev[idx]);
    }
    fprintf(file,
    "</div>\n"
    "<h2>Free = %d</h2>\n"
    "<h2>Last_free = %d</h2>\n"
    "<h2>Head = %d</h2>\n"
    "<h2>Tail = %d</h2>\n"
    "<h2>Size = %d</h2>\n"
    "\t<h1>Graph visualization</h1>\n"
    "\t<img src=\"meow%d.png\" alt=\"Graph\">\n"
    , list.free, list.last_free, list.next[0], list.prev[0], list.size, dump_num);
}
// создаем граф
void CreateGraph(list_t list)
{
    FILE* g_file = fopen(graph_code, "w");
    fprintf(g_file, "digraph G {\n");
    fprintf(g_file, "rankdir=LR;\nbgcolor=\"#0a0b17\";\nsplines=ortho;\n");
    fprintf(g_file, "node[fontsize=9, color=\"#8bf3ff\","
        "style=\"rounded, filled\", fillcolor=\"#060844\","
        "fontname=\"Arial\", fontcolor=\"#8bf3ff\"];\n"
        "edge [style=invis, weight=100];\n");
    CreateNodes(g_file, list);
    LinkNodes(g_file, list);
    fprintf(g_file, "}");
    fclose(g_file);
}
// создаем узлы для графа и первично связываем
void CreateNodes(FILE* file, list_t list)
{
    for (int idx = 0; idx <= list.capacity; idx++)
    {
        fprintf(file, "\"%d\"[shape=record, label=\"index = %d | data = %d |{prev = %d|next = %d}|",
        idx, idx, list.data[idx], list.prev[idx], list.next[idx]);
        if (list.prev[idx] == -1)
        {
            fprintf(file, "FREE\","
            "color=\"#3cff00\", fillcolor=\"#a7aba724\", fontcolor=\"#18ff18\"];\n");
        }
        else
        {
            fprintf(file, "RESERVED\"];\n");
        }
        if (idx > 0)
        {
            fprintf(file, "\"%d\" -> \"%d\";\n", idx - 1, idx);
        }
    }
}
// связываем по next
void LinkNodes(FILE* file, list_t list)
{
    fprintf(file, "edge [style=solid, weight=1, constraint=false, color=\"#24ffed\"];\n");
    for (int idx = 1; idx <= list.capacity; idx++)
    {
        if (list.prev[idx] != -1)
            fprintf(file, "\"%d\" -> \"%d\";\n", idx, list.next[idx]);
    }
}
