#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *inputString(FILE *fp, size_t *len, size_t size);
int isValidAldo(char *msg, int len);
int isValidBar(char *msg, int len);
int isValidCalma(char *msg, int len);
int isValidDol(char *msg, int len);
void printOK(char *msg);
void printFAIL(char *msg);

int main(int argc, char **argv)
{
    FILE *fin = stdin;
    size_t *msg_len = (size_t *)malloc(sizeof(size_t));
    int is_valid_aldo = 0;
    int is_valid_bar = 0;
    int is_valid_calma = 0;
    int is_valid_dol = 0;

    if (argc > 1)
    {
        fin = fopen(argv[1], "r");
        if (fin == NULL)
        {
            fprintf(stderr, "Couldn't open %s for reading.  Exiting. ", argv[1]);
            exit(1);
        }
    }

    char *current_message = inputString(fin, msg_len, 10);
    while (*current_message != '\0')
    {
        // printf("Current Message: %s\nLength: %i\n", current_message, *msg_len);
        // printf("First character of current message: %c\n", *current_message);
        // printf("Second character of current message: %c\n\n", *(current_message + 1));
        is_valid_aldo = 0;
        is_valid_bar = 0;
        is_valid_calma = 0;
        is_valid_dol = 0;

        is_valid_aldo = isValidAldo(current_message, *msg_len);
        is_valid_bar = isValidBar(current_message, *msg_len);
        is_valid_calma = isValidCalma(current_message, *msg_len);
        is_valid_dol = isValidDol(current_message, *msg_len);

        if (is_valid_aldo || is_valid_bar || is_valid_calma || is_valid_dol)
        {
            printOK(current_message);
        }
        else
        {
            printFAIL(current_message);
        }

        current_message = inputString(fin, msg_len, 10);
    }
}

char *inputString(FILE *fp, size_t *len, size_t size)
{
    //The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    *len = 0;
    str = realloc(NULL, sizeof(char) * size); //size is start size
    if (!str)
        return str;

    while (EOF != (ch = fgetc(fp)) && ch != '\n')
    {
        str[(*len)++] = ch;
        if (*len == size)
        {
            str = realloc(str, sizeof(char) * (size += 16));
            if (!str)
                return str;
        }
    }
    str[*len++] = '\0';

    return realloc(str, sizeof(char) * (*len));
}

int isValidAldo(char *msg, int len)
{
    if (*msg != 'A')
    {
        return 0;
    }

    for (int i = 1; i < len - 1; i++)
    {
        if (!isdigit(*(msg + i)))
        {
            return 0;
        }
    }

    if (*(msg + len - 1) != 'F')
    {
        return 0;
    }

    return 1;
}

int isValidBar(char *msg, int len)
{
    return 0;
}

int isValidCalma(char *msg, int len)
{
    return 0;
}

int isValidDol(char *msg, int len)
{
    return 0;
}

void printOK(char *msg)
{
    printf("%s OK\n", msg);
}
void printFAIL(char *msg)
{
    printf("%s FAIL \n", msg);
}