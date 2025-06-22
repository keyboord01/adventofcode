#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubbleSort(int array[], int size)
{

    for (int step = 0; step < size - 1; ++step)
    {

        for (int i = 0; i < size - step - 1; ++i)
        {

            if (array[i] > array[i + 1])
            {

                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}
void calculateDiff(int leftArray[], int rightArray[], int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        int diff = leftArray[i] - rightArray[i];
        sum += (diff < 0 ? -diff : diff);
    }
    printf("%d", sum);
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
    bubbleSort(numarrleft, i);
    bubbleSort(numarrright, i);

    calculateDiff(numarrleft, numarrright, i);

    fclose(fptr);
    return 0;
}