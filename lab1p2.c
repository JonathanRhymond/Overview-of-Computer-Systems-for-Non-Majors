#include <stdio.h>
#include <stdlib.h>

//Gets size of array from user
void getDataSize(int *dataSetSizePtr) {
  printf("Enter the size of the data set\n\n");
  scanf("%d", &*dataSetSizePtr);
}

//Allocates memory for array
void allocFloatMemory(float **dataSetPtrPtr, int dataSetSize) {
  *dataSetPtrPtr = calloc(dataSetSize, sizeof(float));
  if(*dataSetPtrPtr == NULL){
    printf("Error: insucifficent memory for data. Terminating...\n");
    exit(0);
  }
}

//Frees allocated memory
void freeAllocFloatMemory(float *dataSetPtr) {
  free(dataSetPtr);
}

//Gets input for program.
void getInput(float *dataSet, int dataSetSize) {
  printf("Enter the data for the data set:\n\n");
  for (int i = 0; i < dataSetSize; i++) {
    scanf("%f", &dataSet[i]);
  }
}

//Called from in getChoice, computes the desired choice via swich-case.
void doChoice(float *dataSet, int dataSetSize, int choice) {
  float value = 0.0;
  switch(choice) {
  case 1:
    for (int i = 0; i < dataSetSize; i++) {
      value += dataSet[i];
    }
    printf("\nSum of all values: %f\n\n", value);
    break;
  case 2:
    for (int i = 0; i < dataSetSize; i++) {
      value += dataSet[i];
    }
    value = value / dataSetSize;
    printf("\nAverage of all values: %f\n\n", value);
    break;
  case 3:
    for (int i = 0; i < dataSetSize; i++) {
      if (dataSet[i]>value) {
	value = dataSet[i];
      }
    }
    printf("\nMaximum value: %f\n\n", value);
    break;
  case 4:
    value = dataSet[0];
    for (int i = 0; i < dataSetSize; i++) {
      if (dataSet[i]<value) {
	value = dataSet[i];
      }
    }
    printf("\nMinimum value: %f\n\n", value);
    break;
  case 5:
    printf("Data set:");
    for (int i = 0; i < dataSetSize; i++) {
      value = dataSet[i];
      printf("\n%f\n\n", value);
    }
    break;
  default:
    freeAllocFloatMemory(dataSet);
    break;
  }
}

//Gets choice from user input, calls doChoice to run choice.
void getChoice(float *dataSet, int dataSetSize) {
  int choice;
  do {
    printf("\nEnter a number for one of the following choices\n");
    printf("1) Calculate the  sum of all the values.\n");
    printf("2) Calculate the average of all the values.\n");
    printf("3) Find the maximum value.\n");
    printf("4) Find the minimum value.\n");
    printf("5) Print the values in the data set.\n");
    printf("6) Exit the program.\n\n");
    scanf("%d",&choice);
    doChoice(dataSet, dataSetSize, choice);
  } while (choice != 6);
}

//main method to delcare set and size, then call methods.
int main () {
  float *dataSetPtr = NULL;
  int dataSetSize = 0;

  getDataSize(&dataSetSize);
  printf("data set size is %d\n", dataSetSize);
  allocFloatMemory(&dataSetPtr, dataSetSize);

  getInput(dataSetPtr, dataSetSize);
  getChoice(dataSetPtr, dataSetSize);

  return 0;
}
