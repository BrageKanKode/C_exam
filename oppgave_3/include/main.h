#ifndef __MAIN_H__
#define __MAIN_H__

#define OK 0
#define ERROR 1

#define FALSE 0
#define TRUE 1

#define MAX_SIZE 32

struct _LIST
{
   struct _LIST *pNext;
   struct _LIST *pPrevious;
   int iKey;
   char name[MAX_SIZE];
   int age;
   char kommune[MAX_SIZE];
};

struct _LIST *pHead = NULL;
struct _LIST *pTail = NULL;

// Prototypes

void removeMiddleElement(struct _LIST current);
void InsertInList(char tempName[], int tempAge, char tempKommune[], int iKey);
static void PrintList();
void createData(char *string);
void find(struct _LIST *pHead, char *name);
void deleteNode(struct _LIST *pCurrent);
void findDeleteNode(char *name);
void subMenu();
void findDeleteAgeNode(int age, int option);

#endif //__MAIN_H_