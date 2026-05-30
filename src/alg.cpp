// Copyright 2021 NNTU-CS
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) return;
  std::string word;
  char ch;
  while (file.get(ch)) {
      if ((ch >= 'A' && ch <= 'Z') ||
          (ch >= 'a' && ch <= 'z')) {
          word += std::tolower(ch);
      } else {
          if (!word.empty()) {
              tree.insert(word);
              word.clear();
          }
      }
  }
  if (!word.empty()) {
      tree.insert(word);
  }
  file.close();
}
void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int> > words =
        tree.getWords();
    std::sort(words.begin(), words.end(),
        [](const std::pair<std::string, int>& a,
           const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });
    std::ofstream out("result/freq.txt");
    for (const auto& item : words) {
        std::cout << item.first
                  << " "
                  << item.second
                  << std::endl;
        out << item.first
            << " "
            << item.second
            << std::endl;
    }
    out.close();
}
