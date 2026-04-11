#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

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

//------------------------------------------------------------------
// Write data array to output file
//------------------------------------------------------------------
void write_data(string name, int data[], int count) {
  // Open output file
  ofstream dout;
  dout.open(name.c_str());
  if (dout.fail())
    cout << "Error: could not open output file\n";

  // Write the data
  dout << count;
  for (int i = 0; i < count; i++) {
    if (i % 20 == 0)
      dout << endl;
    dout << data[i] << " ";
  }

  // Close the file
  dout.close();
}

//-----------------------------------------------------------------
// Bubble sort algorithm
//-----------------------------------------------------------------
void bubble_sort(int data[], int count) {
  int pass = 1;
  int exchange = 1;

  // Bubble largest value to the right N times
  while ((pass < count) && (exchange > 0)) {
    // Scan unsorted part of data array
    exchange = 0;
    for (int index = 0; index < count - pass; index++) {
      // Swap two data values if out of order
      if (data[index] > data[index + 1]) {
        int temp = data[index];
        data[index] = data[index + 1];
        data[index + 1] = temp;
        exchange++;
      }
    }
    pass++;
  }
}

//---------------------------------------------------------------
// Selection sort algorithm
//---------------------------------------------------------------
void selection_sort(int data[], int low, int high) {
  // Put largest unsorted value at end of sorted list
  for (int last = high; last > low; last--) {
    // Find index of largest value in unsorted array
    int largest = low;
    for (int index = low + 1; index <= last; index++)
      if (data[index] > data[largest])
        largest = index;

    // Swap with last element in unsorted array
    int temp = data[last];
    data[last] = data[largest];
    data[largest] = temp;
  }
}

int main() {
  // const int MAX_SIZE = 100;
  // int data[MAX_SIZE];

  // create_random_data(data, MAX_SIZE, 99);
  // write_data("random.txt", data, MAX_SIZE);

  // create_mostly_sorted_data(data, MAX_SIZE, 42);
  // write_data("mostly_sorted.txt", data, MAX_SIZE);

  // Get start time
  clock_t time1 = clock();

  // bubble_sort with N random data values between 0..N-1
  const int N = 70000;
  int data[N];
  create_random_data(data, N, N);
  bubble_sort(data, N);

  // Get end time
  clock_t time2 = clock();
  double run_time = (time2 - time1) / (double)CLOCKS_PER_SEC;
  cout << "bubble_sort with N random data values between 0..N-1: " << run_time
       << " seconds\n";

  // bubble_sort with mostly sorted data (swaps = N/10)
  create_mostly_sorted_data(data, N, N / 10);
  clock_t time3 = clock();
  bubble_sort(data, N);
  clock_t time4 = clock();
  double run_time2 = (time4 - time3) / (double)CLOCKS_PER_SEC;
  cout << "bubble_sort with mostly sorted data (swaps = N/10): " << run_time2
       << " seconds\n";

  // bubble_sort with sorted data (swaps = 0)
  create_mostly_sorted_data(data, N, 0);
  clock_t time5 = clock();
  bubble_sort(data, N);
  clock_t time6 = clock();
  double run_time3 = (time6 - time5) / (double)CLOCKS_PER_SEC;
  cout << "bubble_sort with sorted data (swaps = 0): " << run_time3
       << " seconds\n";

  // selection_sort with random data
  create_random_data(data, N, N);
  clock_t time7 = clock();
  selection_sort(data, 0, N - 1);
  clock_t time8 = clock();
  double run_time4 = (time8 - time7) / (double)CLOCKS_PER_SEC;
  cout << "selection_sort with random data: " << run_time4 << " seconds\n";

  // selection_sort with mostly sorted data (swaps = N/10)
  create_mostly_sorted_data(data, N, N / 10);
  clock_t time9 = clock();
  selection_sort(data, 0, N - 1);
  clock_t time10 = clock();
  double run_time5 = (time10 - time9) / (double)CLOCKS_PER_SEC;
  cout << "selection_sort with mostly sorted data (swaps = N/10): " << run_time5
       << " seconds\n";

  // selection_sort with sorted data (swaps = 0)
  create_mostly_sorted_data(data, N, 0);
  clock_t time11 = clock();
  selection_sort(data, 0, N - 1);
  clock_t time12 = clock();
  double run_time6 = (time12 - time11) / (double)CLOCKS_PER_SEC;
  cout << "selection_sort with sorted data (swaps = 0): " << run_time6
       << " seconds\n";
  return 0;
}