
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./include/main.h"

static void PrintList(LIST *pThis)
{
}

void bubbleSort(struct _LIST *pList[], int n)
{
   struct _LIST *temp = malloc(sizeof(struct _LIST));
   int i;
   int j;

   for (i = 1; i < n; i++)
   {
      for (j = 1; j < n; j++)
      {
         if (strcmp(pList[j]->szString, pList[j + 1]->szString) > 0)
         {
            temp = pList[j];
            pList[j] = pList[j + 1];
            pList[j + 1] = temp;
         }
      }
   }
}

void getOne(LIST *pThis[])
{

   int size = pThis[1]->size;

   for (int i = 1; i < size; i++)
   {
      if (pThis[i]->id == pThis[i]->intToFind)
      {
         printf("found it!\n"
                "String: %s\n"
                "index: %d\n",
                pThis[i]->szString, pThis[i]->intToFind);
         return;
      }
   }
}

int main(int argc, char *argv[])
{
   int iargc = argc - 1;
   struct _LIST *list[iargc];

   int i;
   int j;
   int unused;

   if (argc <= 1)
   {
      printf("Not any arguments! Need to type ./main 'string' ....\n");
      return -1;
   }
   printf("\nBefore sort:\n");
   for (i = 1; argv[i]; i++)
   {
      list[i] = (struct _LIST *)malloc(sizeof(list[i]) * iargc);
      list[i]->size = iargc;

      list[i]->length = strlen(argv[i]);
      printf("");
      strcpy(list[i]->szString, argv[i]);

      list[i]
          ->pPointerToArray = list[1];
      list[i]->id = i;
      printf("String: %s\n"
             "Length: %d\n"
             "id: %d\n",
             list[i]->szString, list[i]->length, list[i]->id);
   }

   bubbleSort(list, iargc);

   printf("\n After sort\n");
   for (i = 1; argv[i]; i++)
   {
      printf("String: %s\n"
             "Length: %d\n",
             list[i]->szString, list[i]->length);
      list[i]->id = i;
      list[i]->pPointerToArray = list[1];
   }

   printf("\nWhat word would you like to find?\n");
   unused = scanf("%d", &j);
   for (i = 1; argv[i]; i++)
   {
      list[i]->intToFind = j;
   }
   printf("Getting one struct: \n");
   if (j <= iargc && j >= 1)
   {
      getOne(&list[j - 1]);
   }
   else
   {
      printf("Not valid number\n");
   }

   return 0;
}
