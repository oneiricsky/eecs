#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <iostream>

using namespace std;


class wordList {
  private:
    map<string, int> wordCount;

    array<string, 5> filterList = {
      "gutenbergorg",
      "wwwgutenbergorg",
      "wwwgutenbergorgcontact",
      "wwwgutenbergorgdonate",
      "wwwgutenbergorglicense"
    };

    vector<string> cleanWords(const vector<string>& words) {
      vector<string> cleanedWords;
      for (const string& word : words) {
        string cleanedWord;
        for (char c : word) {
          // Check if in alphabet
          if (isalpha(c)) {
            cleanedWord += tolower(c); // lower all letters
          }
        }
        // If the word ended up empty, ignore it
        if (!cleanedWord.empty() && find(filterList.begin(), filterList.end(), cleanedWord) == filterList.end()) {  
              cleanedWords.push_back(cleanedWord);
            }
      }
      return cleanedWords;
    }

    map<string, int> countWords(vector<string> words) {
      map<string, int> wordCount;
      for (const string& word : words) {
        wordCount[word]++;
      }
      return wordCount; 
    }

    vector<string> sortWords(const vector<string>& words) {
      vector<string> sortedWords = words;
      sort(sortedWords.begin(), sortedWords.end());
      return sortedWords;
    } 

  public:
    wordList(ifstream file) {
      if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        return;
      }
      vector<string> words;
      string word;
      // Only add unique words to the vector
      while (file >> word) {
        words.push_back(word);
      }
      words = cleanWords(words);
      wordCount = countWords(words);  
      file.close();
    }
    map<string, int> getWordCount() const { return wordCount; }
};