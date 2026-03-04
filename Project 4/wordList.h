#ifndef wordList_h
#define wordList_h

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

class wordList {
  private:
    map<string, int> wordCount;

    array<string, 5> filterList;

    vector<string> cleanWords(const vector<string>& words);
    map<string, int> countWords(vector<string> words);
    vector<string> sortWords(const vector<string>& words);

  public:
    wordList(ifstream file);
    map<string, int> getWordCount() const;
};

#endif 