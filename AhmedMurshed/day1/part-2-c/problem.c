#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void similarityCalc(int leftArray[], int rightArray[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (leftArray[i] == rightArray[j])
            {
                sum += leftArray[i];
            }
        }
    }
    printf("%d ", sum);
}

int main()
{
    FILE *fptr;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int numarrleft[10000];
    int numarrright[10000];

    fptr = fopen("input.txt", "r");
    if (fptr == NULL)
    {
        return 1;
    }

    int i = 0;
    while ((read = getline(&line, &len, fptr)) != -1)
    {
        char *num = strtok(line, "   ");
        numarrleft[i] = atoi(num);
        num = strtok(NULL, "   ");
        numarrright[i] = atoi(num);
        i++;
    }
    similarityCalc(numarrleft, numarrright, i);

    fclose(fptr);
    return 0;
}