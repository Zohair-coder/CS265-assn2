// Zohair ul Hasan
// Date: 11/19/2020
// ========================
// Assignment - C Messages
// ========================
// Takes a string, either from stdin or from
// a text file separated by newlines.
// Outputs OK or FAIL after checking if the
// string meets the criteria for one of the
// following tests: aldo, bar, calma, dol
// USAGE: ./fsm [file-name]

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

    // check if an argument was passed
    // if so, check if the file exists
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
    size_t buffer = 0;

    while ((msg_len = getline(&current_message, &buffer, fin)) != -1)
    {
        current_message[msg_len - 1] = '\0'; // remove the "\n" character and replace it with NULL terminator
        msg_len--;                           // adjust message length after removing \n
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

// checks if the string is a valid Aldo
// return 1 if true, 0 if false
int isValidAldo(char *msg, int len)
{
    if (*msg != 'A')
    {
        return 0;
    }

    for (int i = 1; i < len - 1; i++) // check string from second character to second-last character
    {
        if (!isdigit(*(msg + i)))
        {
            return 0;
        }
    }

    // check if last character is not F or the length of the string is not 2
    // if last character is F and string length is 2, the string would be AF which does not satisfy our requirements
    // because we need at least one digit between A and F
    if (*(msg + len - 1) != 'F' || len == 2)
    {
        return 0;
    }

    return 1;
}

// checks if the string is a valid Bar
// return 1 if true, 0 if false
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

    if (*msg == 'B' && len == 1) // if B is the only character in the string
    {
        return 1;
    }

    for (int i = 1; i < len; i++) // check second character to last character in the string
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

    if (*(msg + len - 1) != 'G' || len == 2) // if last character is not G, or if the string is BG
    {
        return 0;
    }
    return 1;
}

// checks if the string is a valid Calma
// return 1 if true, 0 if false
int isValidCalma(char *msg, int len)
{
    int isR;
    int isT;
    int cnt = 0;

    if (*msg != 'C')
    {
        return 0;
    }

    if (*msg == 'C' && len == 1) // if C is the only character in the string
    {
        return 1;
    }

    for (int i = 1; i < len; i++) // check second character to last character.
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

    if (cnt % 2 != 0) // if T appears an even number of times
    {
        return 0;
    }

    return 1;
}

// checks if the string is a valid Dol
// return 1 if true, 0 if false
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

    if (!isValidAldo(msg + 3, len - 3) && !isValidCalma(msg + 3, len - 3)) // length needs to be adjusted since the first three characters of the string aren't being sent
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