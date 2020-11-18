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
    }
    free(buffer);
}

char *decodeTheThing(char textToDecode[], int len_str)
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

            if (textToDecode[i + j] != '=')
            {
                num = num << 6;
                count_bits += 6;
            }
            if (textToDecode[i + j] >= 'A' && textToDecode[i + j] <= 'Z')
            {
                num = num | (textToDecode[i + j] - 'A');
            }
            else if (textToDecode[i + j] >= 'a' && textToDecode[i + j] <= 'z')
            {
                num = num | (textToDecode[i + j] - 'a' + 26);
            }
            else if (textToDecode[i + j] >= '0' && textToDecode[i + j] <= '9')
            {
                num = num | (textToDecode[i + j] - '0' + 52);
            }
            else if (textToDecode[i + j] == '+')
            {
                num = num | 62;
            }
            else if (textToDecode[i + j] == '/')
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