#include "include/main.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 400

void main()
{
    FILE *file_to_read;
    FILE *file_to_write;
    int iNumberOfCharacters = 0;
    int iCharacter = 0;
    int j = 0;
    char *buffer = malloc(sizeof(char) * MAXCHAR);

    file_to_read = fopen("file_to_read.txt", "r");
    if (file_to_read != NULL)
    {
        file_to_write = fopen("file_to_write.txt", "w");
        if (file_to_write != NULL)
        {
            while ((iCharacter = fgetc(file_to_read)) != EOF)
            {
                buffer[iNumberOfCharacters] = (char)iCharacter;
                iNumberOfCharacters++;
            }

            fputs(decodeTheThing(buffer, strlen(buffer)), file_to_write);
        }
        printf("\n read file length: %ld\n", strlen(buffer));
        printf("First letter: %c\n", buffer[0]);
        buffer[iNumberOfCharacters] = '\0';
    }
}

char *decodeTheThing(char chinese[], int len_str)
{
    char *decoded;

    decoded = (char *)malloc(sizeof(char) * MAXCHAR);

    int i;
    int j;
    int k = 0;
    int num = 0;

    int count_bits = 0;

    for (i = 0; i < len_str; i += 4)
    {
        num = 0, count_bits = 0;
        for (j = 0; j < 4; j++)
        {

            if (chinese[i + j] != '=')
            {
                num = num << 6;
                count_bits += 6;
            }

            if (chinese[i + j] >= 'A' && chinese[i + j] <= 'Z')
            {
                num = num | (chinese[i + j] - 'A');
            }

            else if (chinese[i + j] >= 'a' && chinese[i + j] <= 'z')
            {
                num = num | (chinese[i + j] - 'a' + 26);
            }

            else if (chinese[i + j] >= '0' && chinese[i + j] <= '9')
            {
                num = num | (chinese[i + j] - '0' + 52);
            }

            else if (chinese[i + j] == '+')
            {
                num = num | 62;
            }

            else if (chinese[i + j] == '/')
            {
                num = num | 63;
            }

            else
            {
                num = num >> 2;
                count_bits -= 2;
            }
        }

        while (count_bits != 0)
        {
            count_bits -= 8;
            decoded[k++] = (num >> count_bits) & 255;
        }
    }

    decoded[k] = '\0';

    return decoded;
}