This project is a part of final assignment in my Data Structure and Algorithm class.

The program supposed Realize direct insertion sort, half insertion sort, bubble sort, quick sort, select sort, heap sort and merge sort. 
The data that going to be sorted supposed to be generated randomly. How big of the data is asked to the user. 
Then the program will output how many comparisons and moves that each algorithm use to sort the data and ask again how big of the data for next iteration of the program, this will keep repeating until the input is zero.

Steps:

1. Prompt for data size
The user will be asked to input an integer which the integer will be used as the size of the raw data that is going to be generated in step 2.

2. Generate raw data
Data is generated randomly by using the rand() and srand() function from stdlib.h library and time() and time.h library.

From this point on the program will automatically in the order of:

1. Direct Insertion sort
2. Half Insertion sort
3. Bubble sort
4. Quick sort
5. Select sort
6. Heap sort
7. Merge sort

After each sort the program will output how many times is the data compared and moved. This will show the general performance of each sort.
