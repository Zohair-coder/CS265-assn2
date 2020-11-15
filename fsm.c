#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **getInput(int argc, char **argv);

int main(int argc, char **argv)
{
    char **messages;
    messages = getInput(argc, argv);
}

char **getInput(int argc, char **argv)
{
    FILE *fp = NULL;
    char *buff = NULL;
    size_t len = 0;
    char **message;
    char *temp_p;
    size_t cnt = 0;

    if (argc > 1)
    {
        fp = fopen(argv[1], "r");

        if (fp == NULL)
        {
            perror("Can not open input file for reading.\n");
            exit(1);
        }
    }
    else
        fp = stdin;

    while (getline(&buff, &len, fp) > 1)
    {
        buff[strlen(buff) - 1] = '\0'; /* Overwrite the newline */
        // *(message + cnt) = buff;
        temp_p = *(message) + cnt;
        temp_p = (char *)malloc(len * sizeof(char));
        strcpy(temp_p, buff);
        cnt++;
    }

    free(buff); /* No memory leaks! */

    buff = NULL; /* pedantic */
    len = 0;

    return message;
}