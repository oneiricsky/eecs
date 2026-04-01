#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const array<string, 5> filterList = {
    "gutenbergorg",
    "wwwgutenbergorg",
    "wwwgutenbergorgcontact",
    "wwwgutenbergorgdonate",
    "wwwgutenbergorglicense",
};

struct wordCount {
  vector<string> words;
  vector<int> counts;
};

vector<string> cleanWords(const vector<string> &words) {
  vector<string> cleanedWords;
  for (const string &word : words) {
    string cleanedWord;
    for (char c : word) {
      if (isalpha(c)) {             // check if alphabet
        cleanedWord += tolower(c);  // lower all letters
      }
    }
    if (!cleanedWord.empty() &&
        find(filterList.begin(), filterList.end(), cleanedWord) ==
            filterList.end()) {
      cleanedWords.push_back(cleanedWord);
    }
  }
  return cleanedWords;
}

vector<string> readWords(ifstream &file) {
  vector<string> words;
  string word;
  while (file >> word) {
    words.push_back(word);
  }
  return words;
}

struct wordCount countWords(const vector<string> &words) {
  struct wordCount wc;
  for (const string &word : words) {
    // Find the word in the vector
    auto it = find(wc.words.begin(), wc.words.end(), word);
    if (it != wc.words.end()) {
      // If found, increment the count
      int index = distance(wc.words.begin(), it);
      wc.counts[index]++;
    } else {
      // If not found, add the word and initialize the count
      wc.words.push_back(word);
      wc.counts.push_back(1);
    }
  }
  return wc;
}

vector<string> sortWords(const vector<string> &words) {
  vector<string> sortedWords = words;
  sort(sortedWords.begin(), sortedWords.end());
  return sortedWords;
}

int main() {
  ifstream file("books/alice-in-wonderland.txt");

  cout << "Unique words in the file:" << endl;
  struct wordCount wc = countWords(sortWords(cleanWords(readWords(file))));
  for (int i = 0; i < wc.words.size(); ++i) {
    cout << wc.words[i] << " (Count: " << wc.counts[i] << ")" << endl;
  }
  return 0;
}