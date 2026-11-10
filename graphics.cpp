#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
const char graph_code[] = "meow.txt";
const char graph_img[]  = "meow.png";
const char html_code[]  = "meow.html";

#include "graphics.h"

FILE* DumpBegin() // начало дампа = создание файла
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

void DumpEnd(FILE* file) // окончание дампа = вызываем system()
{
    fprintf(file,
    "</body>\n"
    "</html>\n");
    fclose(file);
    system("start meow.html");
}

void ListDump(FILE* file, list_t list, int size, int* dump_num) // добавление таблиц и графов
{
    CreateGraph(list, size);
    // snprintf() - создаем форматированную строку и вставляем в system
    char command[150] = {};
    snprintf(command, sizeof(command), "dot -Tpng meow.txt -o meow%d.png", *dump_num);
    system(command);
    CreateHtml(file, list, size, *dump_num);
    (*dump_num)++;
}

void CreateHtml(FILE* file, list_t list, int size, int dump_num) // запись в html
{
    fprintf(file, "<!DOCTYPE html>\n"
        "<head>\n"
        "<hr>\n"
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
    for (int idx = 0; idx <= size; idx++)
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
    "\t<h1>Graph visualization</h1>\n"
    "\t<img src=\"meow%d.png\" alt=\"Graph\">\n"
    , list.free, list.last_free, list.next[0], list.prev[0], dump_num);
}

void CreateGraph(list_t list, int size) // создаем граф
{
    FILE* g_file = fopen(graph_code, "w");
    fprintf(g_file, "digraph G {\n");
    fprintf(g_file, "rankdir=LR;\nbgcolor=\"#0a0b17\";\nsplines=ortho;\n");
    fprintf(g_file, "node[fontsize=9, color=\"#8bf3ff\","
        "style=\"rounded, filled\", fillcolor=\"#060844\","
        "fontname=\"Arial\", fontcolor=\"#8bf3ff\"];\n"
        "edge [style=invis, weight=100];\n");
    CreateNodes(g_file, list, size);
    LinkNodes(g_file, list, size);
    fprintf(g_file, "}");
    fclose(g_file);
}

void CreateNodes(FILE* file, list_t list, int size) // создаем узлы для графа и первично связываем
{
    for (int idx = 0; idx <= size; idx++)
    {
        fprintf(file, "\"%d\"[shape=record, label=\"index = %d | data = %d |{prev = %d|next = %d}|",
        idx, idx, list.data[idx], list.prev[idx], list.next[idx]);
        if (list.prev[idx] == -1)
        {
            fprintf(file, "FREE\","
            "color=\"#a1f787\", fillcolor=\"#020f01a9\", fontcolor=\"#95ff82\"];\n");
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

void LinkNodes(FILE* file, list_t list, int size) // связываем по next
{
    fprintf(file, "edge [style=solid, weight=1, constraint=false, color=\"#24ffed\"];\n");
    for (int idx = 1; idx <= size; idx++)
    {
        if (list.prev[idx] != -1)
            fprintf(file, "\"%d\" -> \"%d\";\n", idx, list.next[idx]);
    }
}
