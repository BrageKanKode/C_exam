#ifndef __MAIN_H__
#define __MAIN_H__

#define MAX 256

typedef struct _LIST
{
   int size;
   int length;
   char szString[MAX];
   int intToFind;
   int id;
   struct _LIST *pPointerToArray;
} LIST;

// Prototypes

void bubbleSort(struct _LIST *list[], int iargc);
int getOne(struct _LIST *pThis[]);

#endif //_MAIN_H_