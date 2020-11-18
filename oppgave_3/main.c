#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./include/main.h"

void menu()
{

   int iChar;
   char tempName[MAX_SIZE];
   char tempKommune[MAX_SIZE];
   int tempAge;
   int iKey = 1;

   // Defined to mute some error messages in terminal for Ubuntu
   int n;

   do
   {
      printf("\n\nSkriv inn ønsket kommando [1 - 5]:\n"
             "1. Legg til en person i databasen\n"
             "2. Finn en person i databasen\n"
             "3. Slette en person i databasen\n"
             "4. PRINT LIST\n"
             "5. Avslutte\n");

      n = scanf("%i", &iChar);

      switch (iChar)
      {
      case 1:

         printf("Skriv inn Navn, age and kommune separated with space \n");
         n = scanf("%s", tempName);
         n = scanf("%i", &tempAge);
         n = scanf("%s", tempKommune);
         InsertInList(tempName, tempAge, tempKommune, iKey);
         iKey++;

         break;

      case 2:
         printf("\nHvilket navn vil du finne?\n");
         n = scanf("%s", tempName);
         find(pHead, tempName);

         break;

      case 3:
         subMenu();
         iChar = 0;
         break;

      case 4:
         PrintList();
         break;

      case 5:
         printf("Avslutter\n");
         exit;
         break;

      default:
         printf("Not valid value");
         break;
      }
   } while (iChar != 5);

   return;
}

void subMenu()
{
   int iChar;
   int n;
   char tempName[250];
   int tempAge;
   int iOption;

   do
   {
      printf("\n\nSkriv inn ønsket kommando [1 - 5]:\n"
             "1. Slett alle elementer ved gitt NAVN\n"
             "2. Slett alle elementer ved gitt ALDER\n"
             "3. Slett alle elementer OVER gitt ALDER\n"
             "4. Slett alle elementer UNDER gitt ALDER\n"
             "5. Tilbake\n");

      n = scanf("%i", &iChar);

      switch (iChar)
      {
      case 1:

         printf("Slett ved GITT NAVN\n");
         n = scanf("%s", tempName);
         findDeleteNode(tempName);

         break;

      case 2:
         printf("Slett ved gitt ALDER\n");
         n = scanf("%i", &tempAge);
         iOption = 1;
         findDeleteAgeNode(tempAge, iOption);

         break;

      case 3:
         printf("Slett OVER ALDER\n");
         n = scanf("%i", &tempAge);
         iOption = 2;
         findDeleteAgeNode(tempAge, iOption);

         break;

      case 4:
         printf("Slett UNDER ALDER\n");
         n = scanf("%i", &tempAge);
         iOption = 3;
         findDeleteAgeNode(tempAge, iOption);

         break;

      case 5:
         exit;
         break;

      default:

         printf("Not valid value");
         break;
      }

   } while (iChar != 5);
}

void findDeleteNode(char *name)
{
   struct _LIST *pThis = NULL;

   if (pHead == NULL)
   {
      printf("Liste er tom\n");
      return;
   }

   pThis = pHead;

   while (pThis)
   {
      if (strcmp(pThis->name, name) == 0)
      {
         deleteNode(pThis);
      }
      pThis = pThis->pNext;
   }
}

void deleteNode(struct _LIST *pCurrent)
{

   if (pHead == pCurrent)
   {
      pHead = pCurrent->pNext;
   }

   if (pCurrent->pNext != NULL)
   {
      pCurrent->pNext->pPrevious = pCurrent->pPrevious;
   }

   if (pCurrent->pPrevious != NULL)
   {
      pCurrent->pPrevious->pNext = pCurrent->pNext;
   }
}

void findDeleteAgeNode(int age, int iOption)
{
   struct _LIST *pThis = NULL;

   if (pHead == NULL)
   {
      printf("Liste er tom\n");
      return;
   }

   pThis = pHead;

   switch (iOption)
   {
   case 1:
      while (pThis)
      {
         if (pThis->age == age)
         {

            deleteNode(pThis);
         }
         pThis = pThis->pNext;
      }

      break;

   case 2:
      while (pThis)
      {
         if (pThis->age > age)
         {

            deleteNode(pThis);
         }
         pThis = pThis->pNext;
      }

      break;

   case 3:
      while (pThis)
      {
         if (pThis->age < age)
         {

            deleteNode(pThis);
         }
         pThis = pThis->pNext;
      }

      break;
   }
}

void find(struct _LIST *pThis, char *name)
{

   if (pHead == NULL)
   {
      printf("Head is NULL\n");
      return;
   }

   pThis = pHead;

   while (pThis)
   {
      if (strcmp(pThis->name, name) == 0)
      {
         printf("iKey: %d\n"
                "Name: %s\n"
                "Age: %d\n"
                "Kommune: %s \n\n",
                pThis->iKey, pThis->name, pThis->age, pThis->kommune);
      }
      pThis = pThis->pNext;
   }
}

void InsertInList(char name[], int age, char kommune[], int iKey)
{

   struct _LIST *new_node = malloc(sizeof(struct _LIST));

   new_node->iKey = iKey;
   strcpy(new_node->name, name);
   new_node->age = age;
   strcpy(new_node->kommune, kommune);

   new_node->pPrevious = NULL;
   new_node->pNext = pHead;
   if (pHead != NULL)
   {
      pHead->pPrevious = new_node;
   }

   pHead = new_node;
   new_node = NULL;
   free(new_node);
}

static void PrintList()
{
   struct _LIST *current = NULL;
   current = pHead;
   while (current != NULL)
   {
      printf("Name: %s\n"
             "Age: %d\n"
             "Kommune: %s \n\n",
             current->name, current->age, current->kommune);
      current = current->pNext;
   }
   printf("\n");
}

int main()
{

   menu();

   return 0;
}