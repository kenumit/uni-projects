#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

void generateRawData(int* a, int n);
void insertSort(int* a, int n);
void binaryInsert(int* a, int n);
void showdata(int* a, int n);
void bubble(int* a, int n);
void quick(int* a, int n);
int pivot(int* a, int low, int high, int* move, int* comp);
void quickSort(int* a, int low, int high, int* move, int* comp);
void selectSort(int* a, int n);
void heapSort(int* a, int n);
void heapAdjust(int* a, int n, int index, int* move, int* comp);
void Merge(int* a, int n);
void mergeSort(int* arr, int l, int r, int* move, int* comp);
void merging(int* arr, int l, int m, int r, int* move, int* comp);

int main() {
    int* a, problemSize;
    printf("Please input size of problem: ");
    scanf("%d", &problemSize);
    while (problemSize > 0) {
        a = (int*)malloc((problemSize + 1) * sizeof(int));
        generateRawData(a, problemSize);
        insertSort(a, problemSize);
        binaryInsert(a, problemSize);
        bubble(a, problemSize);
        quick(a, problemSize);
        selectSort(a, problemSize);
        heapSort(a, problemSize);
        //mergeSort(a,1,problemSize);
        Merge(a, problemSize);
        printf("\nPlease input size of problem: ");
        scanf("%d", &problemSize);
        free(a);
    }

}

void generateRawData(int* a, int n) {
    //Intialized n random integers and assign it to array a
    int i;
    srand(time(0));
    for (i = 1; i <= n; i++) {
        //a[i]=i; //for ordered element, to show best case
        a[i] = rand();
        //a[i]=n-1;//for revesered ordered element.
    }
}
void showData(int* a, int n) {
    //additional function that will show the data in format of 15 integers for each line
    //this function was useful to help developing the algorithm and checked whether the sort is succesfull or not.
    int i, j = 0;
    for (int i = 1; i <= n; i++) {
        printf("%-6d", a[i]);
        j++;
        if (j % 15 == 0)
            printf("\n");
    }
    printf("\n");
}

void insertSort(int* a, int n) {
    //Declare needed variables for sorting algorithm, variables to count move and compare, and new pointer integer.
    int i, j, move = 0, comp = 0, * b;
    //allocate memory size of array of integer of size n+1.
    b = (int*)malloc((n + 1) * sizeof(int));
    //copy the raw data array to the new array. The sorting algorithm will perform in this new array.
    memcpy(b, a, (n + 1) * sizeof(int));

    //Sorting Algorithm
    for (i = 2; i <= n; i++) {
        comp++;
        if (b[i] < b[i - 1]) {
            b[0] = b[i];
            move++;
            for (j = i - 1;; j--) {
                comp++;
                if (b[j] > b[0]) {
                    b[j + 1] = b[j];
                    move++;
                }
                else
                    break;
            }
            b[j + 1] = b[0];
            move++;
        }
    }
    //finsihed Sorting

    printf("\nDirect insert sort needs %d times of comparisons, %d times of moves.\n", comp, move);
    //showData(b,n);
    free(b);
}

void binaryInsert(int* a, int n) {
    //Declare needed variables for sorting algorithm, variables to count move and compare, and new pointer integer.
    int i, j, low, high, mid, * b;
    int move = 0, comp = 0;
    //allocate memory size of array of integer of size n+1.
    b = (int*)malloc((n + 1) * sizeof(int));
    //copy the raw data array to the new array. The sorting algorithm will perform in this new array.
    memcpy(b, a, (n + 1) * sizeof(int));

    //Sorting Algotihm
    for (i = 2; i <= n; i++) {
        comp++;
        if (b[i] < b[i - 1]) {
            b[0] = b[i];
            move++;
            low = 1;
            high = i - 1;
            while (low <= high) {
                comp++;
                mid = (low + high) / 2;
                if (b[mid] == b[0]) {
                    low = mid;
                    break;
                }
                else if (b[mid] < b[0])
                    low = mid + 1;
                else
                    high = mid - 1;
            }
            for (j = i - 1; j >= low; j--) {
                move++;
                b[j + 1] = b[j];
            }
            b[low] = b[0];
            move++;
        }
    }
    //Sorting finished.

    printf("\nBinary insert sort needs %d times of comparisons, %d times of moves.\n", comp, move);
    //showData(b,n);
    free(b);
}

void bubble(int* a, int n) {
    //Declare needed variables for sorting algorithm, variables to count move and compare, and new pointer integer.
    int i = n, j, t, * b, lastIndex = 1;
    int move = 0, comp = 0;
    //allocate memory size of array of integer of size n+1.
    b = (int*)malloc((n + 1) * sizeof(int));
    //copy the raw data array to the new array. The sorting algorithm will perform in this new array.
    memcpy(b, a, (n + 1) * sizeof(int));

    //Sorting Algorithm
    while (i > 1) {
        lastIndex = 1;
        for (j = 1; j < i; j++) {
            comp++;
            if (b[j] > b[j + 1]) {
                move = move + 3;
                t = b[j];
                b[j] = b[j + 1];
                b[j + 1] = t;
                lastIndex = j;
            }
        }
        i = lastIndex;
    }
    //finished sorting

    printf("\nBubble sort needs %d times of comparisons, %d times of moves.\n", comp, move);
    //showData(b,n);
    free(b);
}

void quick(int* a, int n) {
    //Declare needed variables for sorting algorithm, variables to count move and compare, and new pointer integer.
    int i, * b;
    int move = 0, comp = 0;

    //allocate memory size of array of integer of size n+1.
    b = (int*)malloc((n + 1) * sizeof(int));
    //copy the raw data array to the new array. The sorting algorithm will perform in this new array.
    memcpy(b, a, (n + 1) * sizeof(int));
    quickSort(b, 1, n, &move, &comp);
    printf("\nQuick sort needs %d times of comparisons, %d times of moves.\n", comp, move);
    //showData(b,n);
    free(b);
}
int pivot(int* a, int low, int high, int* move, int* comp) {
    //Declare needed variables for finding pivot
    a[0] = a[low];
    (*move)++;
    while (low < high) {
        while (low < high && a[high] >= a[0]) {
            (*comp)++;
            high--;
        }
        a[low] = a[high];
        (*move)++;
        while (low < high && a[low] <= a[0]) {
            (*comp)++;
            low++;
        }
        a[high] = a[low];
        (*move)++;
    }
    a[low] = a[0];
    (*move)++;
    return low;
}
void quickSort(int* a, int low, int high, int* move, int* comp) {
    //Declare needed variables for sorting algorithm.
    int pos;
    if (low < high) {
        pos = pivot(a, low, high, move, comp);
        quickSort(a, low, pos - 1, move, comp);
        quickSort(a, pos + 1, high, move, comp);
    }
}

void selectSort(int* a, int n) {
    //Declare needed variables for sorting algorithm, variables to count move and compare, and new pointer integer.
    int i, j, p, t, * b;
    int move = 0, comp = 0;
    //allocate memory size of array of integer of size n+1.
    b = (int*)malloc((n + 1) * sizeof(int));
    //copy the raw data array to the new array. The sorting algorithm will perform in this new array.
    memcpy(b, a, (n + 1) * sizeof(int));

    //Sorting Algorithm
    for (i = 1; i < n; i++) {
        p = i;
        for (j = i + 1; j <= n; j++) {
            comp++;
            if (b[j] < b[p])
                p = j;
        }
        if (p != i) {
            move = move + 3;
            t = b[p];
            b[p] = b[i];
            b[i] = t;
        }
    }
    //finished sorting
    printf("\nSelect sort needs %d times of comparisons, %d times of moves.\n", comp, move);
    //showData(b,n);
    free(b);
}

void heapSort(int* a, int n) {
    //Declare needed variables for sorting algorithm, variables to count move and compare, and new pointer integer.
    int i, j, * b;
    int move = 0, comp = 0;
    //allocate memory size of array of integer of size n+1.
    b = (int*)malloc((n + 1) * sizeof(int));
    //copy the raw data array to the new array. The sorting algorithm will perform in this new array.
    memcpy(b, a, (n + 1) * sizeof(int));

    //Sorting Algorithm
    for (i = n / 2; i >= 1; i--) {// to create the max heap
        heapAdjust(b, n, i, &move, &comp);
    }
    for (i = 1; i < n; i++) {
        move = move + 3;//checkagain
        b[0] = b[1];
        b[1] = b[n - i + 1];
        b[n - i + 1] = b[0];
        heapAdjust(b, n - i, 1, &move, &comp);
    }
    //finished sorting
    printf("\nHeap sort needs %d times of comparisons, %d times of moves.\n", comp, move);
    //showData(b,n);
    free(b);
}
void heapAdjust(int* a, int n, int index, int* move, int* comp) {
    //Declare needed variables for sort in Max heap format.
    int i, j;
    a[0] = a[index];
    (*move)++;
    i = index;
    j = 2 * i;//larger child index
    while (j <= n) {
        (*comp)++;
        if (j + 1 <= n && a[j + 1] > a[j])
            j++;
        if (a[j] > a[0]) {
            a[i] = a[j];
            (*move)++;
            i = j;
            j = 2 * i;
        }
        else
            break;
    }
    a[i] = a[0];
    (*move)++;
}

void Merge(int* a, int n) {
    //Declare needed variables for sorting algorithm, variables to count move and compare, and new pointer integer.
    int* b, * t, low, mid, high;
    int move = 0, comp = 0;
    //allocate memory size of array of integer of size n+1.
    b = (int*)malloc((n + 1) * sizeof(int));
    //copy the raw data array to the new array. The sorting algorithm will perform in this new array.
    memcpy(b, a, (n + 1) * sizeof(int));

    //Sorting Algorithm
    mergeSort(b, 1, n, &move, &comp);
    //finished sorting

    printf("\nMerge sort needs %d times of comparisons, %d times of moves.\n", comp, move);
    //showData(b,n);
    free(b);

}

void mergeSort(int* arr, int l, int r, int* move, int* comp)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, move, comp);
        mergeSort(arr, m + 1, r, move, comp);

        merging(arr, l, m, r, move, comp);
    }
}
void merging(int* arr, int l, int m, int r, int* move, int* comp)
{
    //Declare needed variables for sorting algorithm
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    //create temp arrays 
    int L[n1], R[n2];

    //Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        (*move)++;

    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
        (*move)++;
    }

    //Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        (*comp)++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            (*move)++;
            i++;
        }
        else {
            arr[k] = R[j];
            (*move)++;
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any 
    while (i < n1) {
        arr[k] = L[i];
        (*move)++;
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any 
    while (j < n2) {
        arr[k] = R[j];
        (*move)++;
        j++;
        k++;
    }
}
