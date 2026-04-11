//-----------------------------------------------------------
//  Purpose:    Header file for the HashTable class.
//  Author:     John Gauch
//-----------------------------------------------------------

#include <iostream>
using namespace std;
const int NONE = 0;
const int EMPTY = -1;
const int DELETED = -2;

//-----------------------------------------------------------
// Define the HashTable class interface
//-----------------------------------------------------------
class HashTable {
public:
  // Constructors
  HashTable(int size);
  HashTable(const HashTable &ht);
  ~HashTable();

  // Methods
  bool Insert(int key, int value);
  bool Search(int key, int &value);
  bool Delete(int key);
  void Print();
  int collision;

private:
  // Private methods
  int Hash(int key);
  int Hash2(int index);

  // Private data
  int Size;
  int *Value;
  int *Key;
};
//-----------------------------------------------------------
//  Purpose:    Implementation of HashTable class.
//  Author:     John Gauch
//-----------------------------------------------------------
//-----------------------------------------------------------
// Constructor
//-----------------------------------------------------------
HashTable::HashTable(int size) {
  Size = size;
  Value = new int[Size];
  Key = new int[Size];
  collision = 0;

  for (int index = 0; index < Size; index++) {
    Value[index] = NONE;
    Key[index] = EMPTY;
  }
}

//-----------------------------------------------------------
// Copy constructor
//-----------------------------------------------------------
HashTable::HashTable(const HashTable &ht) {
  Size = ht.Size;
  Value = new int[Size];
  Key = new int[Size];

  for (int index = 0; index < Size; index++) {
    Value[index] = ht.Value[index];
    Key[index] = ht.Key[index];
  }
}

//-----------------------------------------------------------
// Destructor
//-----------------------------------------------------------
HashTable::~HashTable() {
  delete[] Value;
  delete[] Key;
}

//-----------------------------------------------------------
// Insert method
//-----------------------------------------------------------
bool HashTable::Insert(int key, int value) {
  // Find desired key
  int index = Hash(key);
  int checked = 0;

  while ((Key[index] != key) && (Key[index] != EMPTY && (checked < Size))) {
    index = Hash2(index);
    checked++;
  }

  // Table is full, insertion failed
  if (checked == Size) {
    cout << "Insert failed: table is full\n";
    return false;
  }
  // Insert value into hash table
  Value[index] = value;
  Key[index] = key;
  return true;
}

//-----------------------------------------------------------
// Search method
//-----------------------------------------------------------
bool HashTable::Search(int key, int &value) {
  // Find desired key
  int index = Hash(key);
  while ((Key[index] != key) && (Key[index] != EMPTY))
    index = Hash2(index);

  // Return value from hash table
  if (Key[index] == key)
    value = Value[index];
  return (Key[index] == key);
}

//-----------------------------------------------------------
// Delete method
//-----------------------------------------------------------
bool HashTable::Delete(int key) {
  // Find desired key
  int index = Hash(key);
  while ((Key[index] != key) && (Key[index] != EMPTY))
    index = Hash2(index);

  // Delete value from hash table
  if (Key[index] == key) {
    Value[index] = NONE;
    Key[index] = DELETED;
    return true;
  }
  return false;
}

//-----------------------------------------------------------
// Primary hash function
//-----------------------------------------------------------
int HashTable::Hash(int key) {
  return key % Size;
}

//-----------------------------------------------------------
// Secondary hash function
//-----------------------------------------------------------
int HashTable::Hash2(int index) {
  // cout << "Collision handled at index " << index << "\n";
  collision++;
  return (index + 1) % Size;
}
//-----------------------------------------------------------
// Print function for debugging
//-----------------------------------------------------------
void HashTable::Print() {
  cout << "Index\t" << "Value\t" << "Key\n";
  for (int index = 0; index < Size; index++)
    cout << index << "\t" << Value[index] << "\t" << Key[index] << "\n";
}

//-----------------------------------------------------------
// Main program.
//-----------------------------------------------------------
int main() {
  srandom(time(NULL));

  int counts[] = {5, 10, 15, 20, 25, 30, 35};
  int numExperiments = 7;

  cout << "SIZE=40, MAX=1000\n";
  cout << "COUNT\tCollisions\n";

  for (int i = 0; i < numExperiments; i++) {
    int COUNT = counts[i];
    HashTable ht(40);

    for (int j = 0; j < COUNT; j++)
      ht.Insert(random() % 1000, random() % 1000);

    cout << COUNT << "\t" << ht.collision << "\n";
  }

  return 0;
}