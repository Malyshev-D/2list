#ifndef GRAPHICDEBUG
#define GRAPHICDEBUG

FILE* DumpBegin  ();
void  ListDump   (FILE*  file, list_t list, int* dump_num);
void  CreateHtml (FILE*  file, list_t list, int dump_num);
void  CreateGraph(list_t list);
void  CreateNodes(FILE*  file, list_t list);
void  LinkNodes  (FILE*  file, list_t list);
void  DumpEnd    (FILE*  file);

#endif
