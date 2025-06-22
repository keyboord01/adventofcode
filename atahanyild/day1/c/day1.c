
#include <_stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM_PER_LINE 10000


int leftNums[MAX_NUM_PER_LINE], rightNums[MAX_NUM_PER_LINE], arrSize = 0;

void bubbleSort(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    for (int j = i; j < size; j++) {
      if (arr[i] > arr[j]) {
        int temp = arr[j];
        arr[j] = arr[i];
        arr[i] = temp;
      }
    }
  }
}

void findSimScore() {
  int sim = 0;
  for (int i = 0; i < arrSize; i++) {
    for (int j = 0; j < arrSize; j++) {
      if (leftNums[i] == rightNums[j]) {
        sim += leftNums[i];
      }
    }
  }

  printf("Similarity Score: %d\n", sim);
}

void calculateDiff() {
  int sumOfDiff = 0;
  for (int i = 0; i < arrSize; i++) {
    int diff = leftNums[i] - rightNums[i];
    sumOfDiff += diff < 0 ? -diff : diff;
  }
  printf("Sum of differences: %d", sumOfDiff);
}

int main() {
  FILE *fptr = fopen("input.txt", "r");
  size_t size = 256;
  char *line = NULL;
  ssize_t nread;


  while ((nread = getline(&line, &size, fptr)) != -1) {
    {
      char *num = strtok(line, "   ");
      leftNums[arrSize] = atoi(num);
      num = strtok(NULL, "   ");
      rightNums[arrSize] = atoi(num);
      arrSize++;
    }
  }

  findSimScore();

  bubbleSort(leftNums, arrSize);
  bubbleSort(rightNums, arrSize);
  calculateDiff();
}
