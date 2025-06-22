#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUMS_PER_LINE 101
#define MAX_LINES 1000

void isSafeOrUnsafe(int arr[MAX_LINES][MAX_NUMS_PER_LINE], int line_count, int counts[])
{
    int sign = 1;
    int diff = 0;
    int sum = 0;
    int unSafeCount = 0;
    for (int i = 0; i < line_count; i++)
    {
        for (int j = 0; j < counts[i] - 1; j++)
        {
            diff = arr[i][j] - arr[i][j + 1];
            if (j == 0)
            {
                sign = diff < 0 ? 0 : 1;
            }

            if (!((diff >= 1 && diff <= 3) || (diff >= -3 && diff <= -1)) || (diff < 0 && sign == 1) || (diff > 0 && sign == 0) || diff == 0)
            {
                unSafeCount++;
                break;
            }
        }
    }
    printf("%d \n", 1000 - unSafeCount);
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