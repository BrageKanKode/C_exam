#ifndef __MAIN_H__
#define __MAIN_H__

#define OK 0
#define ERROR 1

#define FALSE 0
#define TRUE 1

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
void getOne(struct _LIST *pThis[]);

//void function(void);

#endif //_MAIN_H_