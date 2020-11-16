#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    FILE *fin = stdin;

    if (argc > 1)
    {
        fin = fopen(argv[1], "r");
        if (fin == NULL)
        {
            fprintf(stderr, "Couldn't open %s for reading.  Exiting. ", argv[1]);
            exit(1);
        }
    }

    int c = fgetc(fin);
    printf("First character: %c", c);
}
