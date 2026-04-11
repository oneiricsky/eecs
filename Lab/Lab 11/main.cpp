#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

// Global counters
long long compare_counter = 0;
long long move_counter = 0;

//------------------------------------------------------------------
// Initialize data array with random values
//------------------------------------------------------------------
void create_random_data(int data[], int count, int range) {
  // Put specified count of random numbers into data array
  for (int index = 0; index < count; index++)
    data[index] = rand() % range;
}

//------------------------------------------------------------------
// Initialize data array with mostly sorted values
//------------------------------------------------------------------
void create_mostly_sorted_data(int data[], int count, int swaps) {
  // Put sorted data values into array
  for (int index = 0; index < count; index++)
    data[index] = index;

  // Shuffle data by swapping random pairs of values
  for (int index = 0; index < swaps; index++) {
    int pos1 = rand() % count;
    int pos2 = rand() % count;
    int temp = data[pos1];
    data[pos1] = data[pos2];
    data[pos2] = temp;
  }
}

//----------------------------------------------------------------
// Insertion sort algorithm
//----------------------------------------------------------------
void insertion_sort(int data[], int low, int high) {
  // Insert each element of unsorted list into sorted list
  for (int unsorted = low + 1; unsorted <= high; unsorted++) {
    // Select unsorted value to be inserted
    int value = data[unsorted];
    int posn = unsorted;

    // Make room for new data value
    while ((posn > 0) && (data[posn - 1] > value)) {
      // increment the compare_counter whenever you compare one of the data
      // elements to another variable
      data[posn] = data[posn - 1];
      posn--;
      compare_counter++;
    }

    // Put new value into array
    data[posn] = value;
    move_counter++;
  }
}

//----------------------------------------------------------------
// Partition function used by Quicksort.
//----------------------------------------------------------------
void partition(int data[], int low, int high, int &mid) {
  int pivot = data[high];
  int left = low;
  int right = high;

  while (left < right) {
    // Scan left to right
    while ((left < right) && (data[left] < pivot)) {
      compare_counter++;
      left++;
    }
    compare_counter++; // the comparison that stopped the left scan

    // Scan right to left
    while ((left < right) && (data[right] >= pivot)) {
      compare_counter++;
      right--;
    }
    compare_counter++; // the comparison that stopped the right scan

    int temp = data[left];
    data[left] = data[right];
    data[right] = temp;
    move_counter += 3; // 3-way swap
  }

  mid = left;
  data[high] = data[mid];
  data[mid] = pivot;
  move_counter += 2; // pivot swap
}
//----------------------------------------------------------------
// Recursive Quicksort algorithm using basic partition function.
//----------------------------------------------------------------
void quick_sort(int data[], int low, int high) {
  // Check terminating condition
  if (low < high) {
    // Partition data into two parts
    int mid = 0;
    partition(data, low, high, mid);

    // Recursive calls to sort array
    quick_sort(data, low, mid - 1);
    quick_sort(data, mid + 1, high);
  }
}

//----------------------------------------------------------------
// Mergesort using secondary storage for data merging.
//----------------------------------------------------------------
void merge_sort(int data[], int low, int high) {
  // Check terminating condition
  int range = high - low + 1;
  if (range > 1) {
    // Divide the array and sort both halves
    int mid = (low + high) / 2;
    merge_sort(data, low, mid);
    merge_sort(data, mid + 1, high);

    // Create temporary array for merged data
    int *copy = new int[range];

    // Initialize array indices
    int index1 = low;
    int index2 = mid + 1;
    int index = 0;

    // Merge smallest data elements into copy array
    while (index1 <= mid && index2 <= high) {
      compare_counter++;
      if (data[index1] < data[index2])
        copy[index++] = data[index1++];
      else
        copy[index++] = data[index2++];
      move_counter++;
    }

    // Copy any remaining entries from the first half
    while (index1 <= mid)
      copy[index++] = data[index1++];

    // Copy any remaining entries from the second half
    while (index2 <= high)
      copy[index++] = data[index2++];

    // Copy data back from the temporary array
    for (index = 0; index < range; index++) {
      data[low + index] = copy[index];
      move_counter++;
    }
    delete[] copy;
  }
}

//----------------------------------------------------------------
/*
Create a new project in your IDE and cut and paste the functions
"create_random_data", "create_mostly_sorted_data", "insertion_sort",
"merge_sort" and "quick_sort" from below into your program. Now create a main
program that creates an array of 1000 integers, and calls one of the data
initialization functions and one of the sorting functions to make sure
everything is compiling and running.
*/
int main() {
  int sizes[] = {10, 100, 1000};
  for (int i : sizes) {
    vector<int> data(i);

    cout << "Sorting " << i << " integers:" << endl;
    cout << "-----------------------------" << endl;

    // --- Insertion Sort ---
    cout << "Insertion Sort " << endl;
    compare_counter = 0;
    move_counter = 0;
    create_random_data(data.data(), i, i);
    insertion_sort(data.data(), 0, i - 1);
    cout << "Random - Compares: " << compare_counter
         << " | Moves: " << move_counter << endl;

    compare_counter = 0;
    move_counter = 0;
    create_mostly_sorted_data(data.data(), i, i / 10);
    insertion_sort(data.data(), 0, i - 1);
    cout << "Mostly Sorted - Compares: " << compare_counter
         << " | Moves: " << move_counter << endl;

    compare_counter = 0;
    move_counter = 0;
    create_mostly_sorted_data(data.data(), i, 0);
    insertion_sort(data.data(), 0, i - 1);
    cout << "Sorted - Compares: " << compare_counter
         << " | Moves: " << move_counter << endl;
    cout << endl;
    cout << "==================================================" << endl;
    // --- Merge Sort ---
    cout << "Merge Sort " << endl;
    compare_counter = 0;
    move_counter = 0;
    create_random_data(data.data(), i, i);
    merge_sort(data.data(), 0, i - 1);
    cout << "Random - Compares: " << compare_counter
         << " | Moves: " << move_counter << endl;

    compare_counter = 0;
    move_counter = 0;
    create_mostly_sorted_data(data.data(), i, i / 10);
    merge_sort(data.data(), 0, i - 1);
    cout << "Mostly Sorted - Compares: " << compare_counter
         << " | Moves: " << move_counter << endl;

    compare_counter = 0;
    move_counter = 0;
    create_mostly_sorted_data(data.data(), i, 0);
    merge_sort(data.data(), 0, i - 1);
    cout << "Sorted - Compares: " << compare_counter
         << " | Moves: " << move_counter << endl;
    cout << endl;
    cout << "==================================================" << endl;

    // --- Quick Sort ---
    cout << "Quick Sort " << endl;
    compare_counter = 0;
    move_counter = 0;
    create_random_data(data.data(), i, i);
    quick_sort(data.data(), 0, i - 1);
    cout << "Random - Compares: " << compare_counter
         << " | Moves: " << move_counter << endl;

    compare_counter = 0;
    move_counter = 0;
    create_mostly_sorted_data(data.data(), i, i / 10);
    quick_sort(data.data(), 0, i - 1);
    cout << "Mostly Sorted - Compares: " << compare_counter
         << " | Moves: " << move_counter << endl;

    compare_counter = 0;
    move_counter = 0;
    create_mostly_sorted_data(data.data(), i, 0);
    quick_sort(data.data(), 0, i - 1);
    cout << "Sorted - Compares: " << compare_counter
         << " | Moves: " << move_counter << endl;
    cout << endl;
  }
  return 0;
}