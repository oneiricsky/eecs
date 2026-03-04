#include <iostream>
#include <fstream>
#include "wordList.h"

using namespace std;

int main() {
  wordList book1(ifstream("books/alice-in-wonderland.txt"));

  cout << "Unique words in the file:" << endl;
  for (const auto& entry: book1.getWordCount()) {
    cout << entry.first << " (Count: " << entry.second << ")" << endl;
  }
  return 0;
}