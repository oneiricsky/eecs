//-----------------------------------------------------------
//  Purpose:    This program demonstrates how multiple queues
//              can be used to simulate customer arrivals.
//  Author:     John Gauch
//-----------------------------------------------------------
#include "queue.h"

//-----------------------------------------------------------
// Main program uses the Queue class to simulate customers.
//-----------------------------------------------------------
int main() {
  int NumLines = 3;
  int NumCustomers = 10;
  int CurrentTime = 0;
  Queue *Vendor = new Queue[NumLines];

  // Add customers to different queues
  for (int Customer = 0; Customer < NumCustomers; Customer++) {
    // Generate customer data
    CurrentTime += 5 + random() % 20;
    int NumItems = 1 + random() % 5;

    // Search for shortest queue
    int ShortLine = 0;
    int ShortLength = Vendor[0].GetLength();
    for (int Line = 1; Line < NumLines; Line++) {
      int Length = Vendor[Line].GetLength();
      if (Length < ShortLength) {
        ShortLine = Line;
        ShortLength = Length;
      }
    }

    // Add customer to shortest line
    Vendor[ShortLine].Insert(NumItems);

    // Check each line for a departure with 20% probability
    for (int Line = 0; Line < NumLines; Line++) {
      if (!Vendor[Line].IsEmpty() && (random() % 100 < 20))
        Vendor[Line].Remove();
    }

    // Print all customer lines after each arrival.
    cout << "Time " << CurrentTime << endl;
    for (int Line = 0; Line < NumLines; Line++) {
      cout << "Line " << " ";
      Vendor[Line].Print();
    }
    cout << endl;
  }

  cout << "Begin drain\n..." << endl;
  bool Empty = false;
  while (!Empty) {
    Empty = true;
    for (int Line = 0; Line < NumLines; Line++) {
      if (!Vendor[Line].IsEmpty()) {
        Empty = false;
        if (random() % 100 < 20)
          Vendor[Line].Remove();
        // cout << "Line " << " ";
        // Vendor[Line].Print();
      }
    }
  }

  // Print final customer lines.
  cout << "Final" << endl;
  for (int Line = 0; Line < NumLines; Line++) {
    cout << "Line " << Line << " ";
    Vendor[Line].Print();
  }

  delete[] Vendor;
  cout << endl;
}
