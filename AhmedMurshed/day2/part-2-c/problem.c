#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMS_PER_LINE 101
#define MAX_LINES 1000

int isSafeCheck(int arr[], int count)
{

    int sign = arr[0] - arr[1] < 0 ? 0 : 1;
    for (int j = 0; j < count - 1; j++)
    {
        int diff = arr[j] - arr[j + 1];
        if (!((diff >= 1 && diff <= 3) || (diff >= -3 && diff <= -1)) || (diff < 0 && sign == 1) || (diff > 0 && sign == 0) || diff == 0)
        {
            return 0;
        }
    }
    return 1;
}

void isSafeOrUnsafe(int arr[MAX_LINES][MAX_NUMS_PER_LINE], int line_count, int counts[])
{
    int unSafeCount = 0;
    for (int i = 0; i < line_count; i++)
    {
        int isSafe = isSafeCheck(arr[i], counts[i]);
        if (isSafe)
        {
            continue;
        }

        int canBeSafe = 0;
        for (int k = 0; k < counts[i]; k++)
        {
            int temp[MAX_NUMS_PER_LINE];
            int tempCount = 0;
            for (int j = 0; j < counts[i]; j++)
            {
                if (j != k)
                {
                    temp[tempCount++] = arr[i][j];
                }
            }
            if (isSafeCheck(temp, tempCount))
            {
                canBeSafe = 1;
                break;
            }
        }
        if (!canBeSafe)
            unSafeCount++;
    }
    printf("%d\n", line_count - unSafeCount);
}

int main()
{
    FILE *fptr;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fptr = fopen("input.txt", "r");
    if (fptr == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

    int reports[MAX_LINES][MAX_NUMS_PER_LINE];
    int counts[MAX_LINES];
    int line_count = 0;

    while ((read = getline(&line, &len, fptr)) != -1 && line_count < MAX_LINES)
    {
        int count = 0;
        char *num = strtok(line, " ");
        while (num != NULL && count < MAX_NUMS_PER_LINE)
        {
            reports[line_count][count] = atoi(num);
            count++;
            num = strtok(NULL, " ");
        }
        counts[line_count] = count;
        line_count++;
    }

    isSafeOrUnsafe(reports, line_count, counts);
    free(line);
    fclose(fptr);
    return 0;
}