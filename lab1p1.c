#include <stdio.h>
#include <stdlib.h>

// Gets input for program.
void getInput(float *dataSet, int dataSetSize) {
    printf("Enter the data for the data set:\n\n");
    for (int i = 0; i < dataSetSize; i++) {
        scanf("%f", &dataSet[i]); // Changed the format specifier to %f to read float values
    }
}

// Called from in getChoice, computes the desired choice via switch-case.
void doChoice(float *dataSet, int dataSetSize, int choice) {
    float value = 0.0;
    switch (choice) {
        case 1:
            for (int i = 0; i < dataSetSize; i++) {
                value += dataSet[i];
            }
            printf("\nSum of all values: %.2f\n\n", value);
            break;
        case 2:
            for (int i = 0; i < dataSetSize; i++) {
                value += dataSet[i];
            }
            value = value / dataSetSize;
            printf("\nAverage of all values: %.2f\n\n", value);
            break;
        case 3:
            value = dataSet[0];
            for (int i = 1; i < dataSetSize; i++) {
                if (dataSet[i] > value) {
                    value = dataSet[i];
                }
            }
            printf("\nMaximum value: %.2f\n\n", value);
            break;
        case 4:
            value = dataSet[0];
            for (int i = 1; i < dataSetSize; i++) {
                if (dataSet[i] < value) {
                    value = dataSet[i];
                }
            }
            printf("\nMinimum value: %.2f\n\n", value);
            break;
        case 5:
            printf("Data set:\n");
            for (int i = 0; i < dataSetSize; i++) {
                value = dataSet[i];
                printf("%.2f\n\n", value);
            }
            break;
        default:
            break;
    }
}

// Gets choice from user input, calls doChoice to run choice.
void getChoice(float *dataSet, int dataSetSize) {
    int choice;
    do {
        printf("\nEnter a number for one of the following choices\n");
        printf("1) Calculate the sum of all the values.\n");
        printf("2) Calculate the average of all the values.\n");
        printf("3) Find the maximum value.\n");
        printf("4) Find the minimum value.\n");
        printf("5) Print the values in the data set.\n");
        printf("6) Exit the program.\n\n");
        scanf("%d", &choice);
        doChoice(dataSet, dataSetSize, choice);
    } while (choice != 6);
}

// Main method to declare set and size, then call methods.
int main() {
    float dataSet[7];
    int dataSetSize = 7;

    getInput(dataSet, dataSetSize);
    getChoice(dataSet, dataSetSize);

    return 0;
}