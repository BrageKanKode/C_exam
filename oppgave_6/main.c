#include "include/main.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define MAXCHAR 10

struct _ft
{
    char *filename;
    char *buffer;
    int iNum;
    int read;
    int done;
};

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *myThreadFun(void *ft)
{

    struct _ft *pft = (struct _ft *)ft;

    pthread_mutex_lock(&mutex);

    FILE *file_to_read;
    char *buffer = malloc(sizeof(char) * MAXCHAR);
    int iNumberOfCharacters = pft->iNum;
    char character;

    file_to_read = fopen("textfile.txt", "r");

    if (file_to_read != NULL)
    {
        while ((character = fgetc(file_to_read)) != EOF && iNumberOfCharacters++ < 9)
        {

            strcpy(&buffer[iNumberOfCharacters], &character);
        }
        pft->buffer = buffer;
    }
    if (character == EOF)
    {
        pft->done = 1;
    }

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, char *argv[])
{

    pthread_t tId;
    struct _ft *ft = malloc(sizeof(struct _ft));

    ft->filename = argv[1];
    ft->iNum = -1;
    ft->read = 10;
    ft->done = 0;

    int characteramount = 0;

    while (ft->done != 1)
    {

        pthread_create(&tId, NULL, myThreadFun, (void *)ft);
        pthread_join(tId, NULL);
        printf("Buffer: %s\n", ft->buffer);
        characteramount += strlen(ft->buffer);
        memset(ft->buffer, 0, sizeof((char *)ft->buffer));
        ft->iNum = ft->iNum - 10;
    }

    printf("Total amount of characters read and printed: %d\n", characteramount);

    return 0;
}
