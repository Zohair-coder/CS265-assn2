#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isValidAldo(char *msg, int len);
int isValidBar(char *msg, int len);
int isValidCalma(char *msg, int len);
int isValidDol(char *msg, int len);
void printOK(char *msg);
void printFAIL(char *msg);

int main(int argc, char **argv)
{
    FILE *fin = stdin;
    int is_valid_aldo = 0;
    int is_valid_bar = 0;
    int is_valid_calma = 0;
    int is_valid_dol = 0;
    size_t buffer = 0;

    if (argc > 1)
    {
        fin = fopen(argv[1], "r");
        if (fin == NULL)
        {
            fprintf(stderr, "Couldn't open %s for reading.  Exiting. ", argv[1]);
            exit(1);
        }
    }

    char *current_message = NULL;
    size_t msg_len = 0;

    while ((msg_len = getline(&current_message, &buffer, fin)) != -1)
    {
        current_message[msg_len - 1] = '\0';
        msg_len--;
        is_valid_aldo = isValidAldo(current_message, msg_len);
        is_valid_bar = isValidBar(current_message, msg_len);
        is_valid_calma = isValidCalma(current_message, msg_len);
        is_valid_dol = isValidDol(current_message, msg_len);

        if (is_valid_aldo || is_valid_bar || is_valid_calma || is_valid_dol)
        {
            printOK(current_message);
        }
        else
        {
            printFAIL(current_message);
        }
    }
    free(current_message);
    current_message = NULL;
    fclose(fin);
}

// checks if the string is a valid Aldo.
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

    if (*(msg + len - 1) != 'F' || len == 2)
    {
        return 0;
    }

    return 1;
}

// checks if the string is a valid Bar.
int isValidBar(char *msg, int len)
{
    int isPreviousG;
    int isPreviousPreviousH;
    int isH;
    int isG;
    int isX;

    if (*msg != 'B')
    {
        return 0;
    }

    if (*msg == 'B' && len == 1)
    {
        return 1;
    }

    for (int i = 1; i < len; i++)
    {
        isH = *(msg + i) == 'H';
        isG = *(msg + i) == 'G';
        isX = *(msg + i) == 'X';

        if (!isH && !isG && !isX)
        {
            return 0;
        }
        if (isX)
        {
            isPreviousG = *(msg + i - 1) == 'G';
            isPreviousPreviousH = *(msg + i - 2) == 'H';
            if (!isPreviousG || !isPreviousPreviousH)
            {
                return 0;
            }
        }
    }

    if (*(msg + len - 1) != 'G' || len == 2)
    {
        return 0;
    }
    return 1;
}

// checks if the string is a valid Calma.
int isValidCalma(char *msg, int len)
{
    int isR;
    int isT;
    int cnt = 0;

    if (*msg != 'C')
    {
        return 0;
    }

    if (*msg == 'C' && len == 1)
    {
        return 1;
    }

    for (int i = 1; i < len; i++)
    {
        isR = *(msg + i) == 'R';
        isT = *(msg + i) == 'T';

        if (!isR && !isT)
        {
            return 0;
        }

        if (isT)
        {
            cnt++;
        }
    }

    if (cnt % 2 != 0)
    {
        return 0;
    }

    return 1;
}

// checks if the string is a valid Dol.
int isValidDol(char *msg, int len)
{
    if (*msg != 'D')
    {
        return 0;
    }

    if (!isdigit(*(msg + 1)) && !isdigit(*(msg + 2)))
    {
        return 0;
    }

    if (!isValidAldo(msg + 3, len - 3) && !isValidCalma(msg + 3, len - 3))
    {
        return 0;
    }

    return 1;
}

// prints an OK message in green when called
void printOK(char *msg)
{
    printf("%s \033[0;32mOK\033[0m\n", msg);
}

// prints a FAIL message in red when called
void printFAIL(char *msg)
{
    printf("%s \033[0;31mFAIL\033[0m\n", msg);
}