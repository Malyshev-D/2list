#ifndef GRAPHICDEBUG
#define GRAPHICDEBUG

FILE* DumpBegin  ();
void  ListDump   (FILE*  file, list_t list, int size, int* dump_num);
void  CreateHtml (FILE*  file, list_t list, int size, int dump_num);
void  CreateGraph(list_t list, int    size);
void  CreateNodes(FILE*  file, list_t list, int size);
void  LinkNodes  (FILE*  file, list_t list, int size);
void  DumpEnd    (FILE*  file);

#endif
