#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBERS 100

// Function prototypes
void generateRandomNumbers(int *array, int size);
void sortArray(int *array, int size);
void displayArray(const int *array, int size);
int binarySearch(const int *array, int size, int target);

int main() {
    int numbers[MAX_NUMBERS];
    int size;
    int target;
    int foundIndex;

    printf("Enter the number of elements (1-%d): ", MAX_NUMBERS);
    scanf("%d", &size);

    if (size < 1 || size > MAX_NUMBERS) {
        printf("Invalid size. Please enter a number between 1 and %d.\n", MAX_NUMBERS);
        return 1;
    }

    generateRandomNumbers(numbers, size);

    printf("Unsorted array:\n");
    displayArray(numbers, size);

    sortArray(numbers, size);

    printf("\nSorted array:\n");
    displayArray(numbers, size);

    printf("\nEnter a number to search: ");
    scanf("%d", &target);

    foundIndex = binarySearch(numbers, size, target);

    if (foundIndex != -1) {
        printf("\nNumber %d found at index %d (0-based index).\n", target, foundIndex);
    } else {
        printf("\nNumber %d not found in the array.\n", target);
    }

    return 0;
}

void generateRandomNumbers(int *array, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000; // Random numbers between 0 and 999
    }
}

void sortArray(int *array, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void displayArray(const int *array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int binarySearch(const int *array, int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (array[mid] == target) {
            return mid;
        } else if (array[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}
