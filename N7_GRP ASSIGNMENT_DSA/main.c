                                                                                                                                                                                                                                                                           #include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Binary Search
void binary_search(int arr[], int target, int size) {
    int first = 0;
    int last = size - 1;
    while (first <= last) {
        int midpoint = (first + last) / 2;
        if (arr[midpoint] == target) {
            printf("\nFound at index %d\n", midpoint);
            return;
        } else if (target > arr[midpoint]) {
            first = midpoint + 1;
        } else {
            last = midpoint - 1;
        }
    }
    printf("\nNot found target\n");
}

// Interpolation Search
int recursiveInterpolationSearch(int arr[], int low, int high, int target) {
    if (low <= high && target >= arr[low] && target <= arr[high]) {
        int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);
        if (target == arr[pos])
            return pos;
        else if (target < arr[pos])
            return recursiveInterpolationSearch(arr, low, pos - 1, target);
        else
            return recursiveInterpolationSearch(arr, pos + 1, high, target);
    }
    return -1;
}

// Merge Sort
void merge(int arr[], int start, int mid, int last) {
    int left = mid - start + 1;
    int right = last - mid;
    int leftarr[left];
    int rightarr[right];
    int l = 0, s = start, r = 0;
    while (l < left) {
        leftarr[l] = arr[s];
        l++;
        s++;
    }
    while (r < right) {
        rightarr[r] = arr[s];
        r++;
        s++;
    }
    l = 0;
    r = 0;
    s = start;
    while (l < left && r < right) {
        if (leftarr[l] <= rightarr[r]) {
            arr[s] = leftarr[l];
            s++;
            l++;
        } else {
            arr[s] = rightarr[r];
            s++;
            r++;
        }
    }
    while (r < right) {
        arr[s] = rightarr[r];
        s++;
        r++;
    }
    while (l < left) {
        arr[s] = leftarr[l];
        s++;
        l++;
    }
}

void mergeSortWrapper(int arr[], int size) {
    mergeSort(arr, 0, size - 1);
}

void mergeSort(int arr[], int start, int last) {
    if (start < last) {
        int mid = (start + last) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, last);
        merge(arr, start, mid, last);
    }
}

// Selection Sort
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[min_index] > arr[j]) {
                min_index = j;
            }
        }
        if (min_index != i) {
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
    }
}

// Heap Sort
void heapify(int arr[], int size, int root) {
    int largest = root;
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    while (left < size) {
        if (arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < size && arr[right] > arr[largest]) {
            largest = right;
        }
        if (largest != root) {
            swap(&arr[root], &arr[largest]);
            root = largest;
            left = 2 * root + 1;
            right = 2 * root + 2;
        } else {
            break;
        }
    }
}

void heapSort(int arr[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i);
    }
    for (int i = size - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void measureTime(void (*sortFunc)(int[], int), int arr[], int size, const char* sortName) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    sortFunc(arr, size);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
    printf("Time taken to sort using %s: %.6f microseconds\n", sortName, time_taken);
}

void measureSearchTime(void (*searchFunc)(int[], int, int), int arr[], int size, int target, const char* searchName) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    searchFunc(arr, target, size);

    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
    printf("Time taken to search using %s: %.6f microseconds\n", searchName, time_taken);
}

int main(int argc, char const *argv[]) {
    int *arr;
    int size, target, result, choice, searchChoice;

    printf("Enter Size of array: ");
    scanf("%d", &size);
    arr = malloc(sizeof(int) * size);
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        int randomNum = (rand() % size) + 1;
        int duplicateEle = 0;
        for (int j = 0; j < i; j++) {
            if (arr[j] == randomNum) {
                duplicateEle = 1;
                break;
            }
        }
        if (!duplicateEle) {
            arr[i] = randomNum;
        } else {
            i--;
        }
    }

    printf("The randomly generated elements are:\n");
    printArray(arr, size);

    printf("Choose Sorting Algorithm:\n1. Merge Sort\n2. Selection Sort\n3. Heap Sort\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            measureTime(mergeSortWrapper, arr, size, "Merge Sort");
            break;
        case 2:
            measureTime(selectionSort, arr, size, "Selection Sort");
            break;
        case 3:
            measureTime(heapSort, arr, size, "Heap Sort");
            break;
        default:
            printf("Invalid choice\n");
            free(arr);
            return 1;
    }

    printf("The elements sorted using chosen algorithm are:\n");
    printArray(arr, size);

    printf("Choose Searching Algorithm:\n1. Binary Search\n2. Interpolation Search\n");
    scanf("%d", &searchChoice);

    printf("Enter Target Element: ");
    scanf("%d", &target);

    switch (searchChoice) {
        case 1:
            measureSearchTime(binary_search, arr, size, target, "Binary Search");
            break;
        case 2: {
            struct timespec start, end;
            clock_gettime(CLOCK_MONOTONIC, &start);

            result = recursiveInterpolationSearch(arr, 0, size - 1, target);

            clock_gettime(CLOCK_MONOTONIC, &end);
            double time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
            if (result != -1)
                printf("Element %d found at index %d.\n", target, result);
            else
                printf("Element %d not found in the array.\n", target);
            printf("Time taken to search using Interpolation Search: %.6f microseconds\n", time_taken);
            break;
        }
        default:
            printf("Invalid choice\n");
            free(arr);
            return 1;
    }

    free(arr);
    return 0;
}
