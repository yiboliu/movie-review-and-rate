////////////////////////////////////////////////////////////////////////////////
// File Name:      a2.cpp
//
// Author:         Gerald
// CS email:       gerald@cs.wisc.edu
//
// Description:    The source file for a2.
//
// IMPORTANT NOTE: THIS IS THE ONLY FILE THAT YOU SHOULD MODIFY FOR A2.
//                 You SHOULD NOT MODIFY any of the following:
//                   1. Name of the functions/methods.
//                   2. The number and type of parameters of the functions.
//                   3. Return type of the functions.
////////////////////////////////////////////////////////////////////////////////

#include "a2.hpp"
#include "trim.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;
void cleanData(std::ifstream &inFile, std::ofstream &outFile,
               std::unordered_set<std::string> &stopwords) {
    // TODO: Implement this method.
    // # of lines of code in Gerald's implementation: 13
    // Do the following operations on each review before
    // storing it to the output file:

    string line;
    while(getline(inFile, line)){
      //   1. Replace hyphens with spaces.
      replaceHyphensWithSpaces(line);
      //   2. Split the line of text into individual words.
      vector<string> words;
      splitLine(line, words);
      //   3. Remove the punctuation marks from the words.
      vector<string> NewWords;
      removePunctuation(words, NewWords);
      //   4. Remove the trailing and the leading whitespaces in each word.
      removeWhiteSpaces(NewWords);
      //   5. Remove the empty words.
      removeEmptyWords(NewWords);
      //   6. Remove words with just one character in them. You should NOT remove
      //      numbers in this step because if you do so, you'll lose the ratings.
      removeSingleLetterWords(NewWords);
      //   7. Remove stopwords.
      removeStopWords(NewWords, stopwords);
      //  Write the cleaned words to output file.
      for (size_t i = 0; i < NewWords.size(); ++i) outFile << NewWords[i] << " ";
      outFile << endl;
    }
}

void fillDictionary(std::ifstream &newInFile,
                    std::unordered_map<std::string, std::pair<long, long>> &dict) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 20
    string line;
    int rate;
    while(getline(newInFile, line)){
      rate = atoi(&(line.at(0)));
      line.erase(0,2);
      size_t pos = 0;
      std::string token;
      std::string delimiter = " ";
      while ((pos = line.find(delimiter)) != std::string::npos) {
        token = line.substr(0, pos);
        auto it = dict.find(token);
        if(it != dict.end()){
          it->second.first += rate;
          it->second.second++;
        }
        else{
          dict[token] = make_pair((long) rate, 1);
        }
        line.erase(0, pos + delimiter.length());
      }
    }
}


void fillStopWords(std::ifstream &inFile,
                   std::unordered_set<std::string> &stopwords) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    string line;
    while (getline(inFile, line)) {
      stopwords.insert(line);
    }
}

void rateReviews(std::ifstream &testFile,
                 std::unordered_map<std::string, std::pair<long, long>> &dict,
                 std::ofstream &ratingsFile) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 20
    string line;
    while(getline(testFile, line)){
      double rate = 0;
      if(line.length() == 0){
        rate = 2;
      }
      else{
        size_t pos = 0;
        string token;
        string delimiter = " ";
        int count = 0;
        while ((pos = line.find(delimiter)) != std::string::npos) {
          token = line.substr(0, pos);
          auto it = dict.find(token);
          if(it==dict.end()){
            rate += 2;
          }
          else{
            rate += (it->second.first * 1.0 / it->second.second * 1.0);
          }
          count++;
          line.erase(0, pos + delimiter.length());
        }
        rate /= (count*1.0);
      }
      ratingsFile << fixed << setprecision(2) << rate << endl;
    }
}

void removeEmptyWords(std::vector<std::string> &tokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    for(auto it = tokens.begin(); it != tokens.end();){
      if((*it).length() == 0) it = tokens.erase(it);
      else ++it;
    }
}

void removePunctuation(std::vector<std::string> &inTokens,
                       std::vector<std::string> &outTokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 10
    for(auto it = inTokens.begin(); it != inTokens.end(); ++it){
      string token = *it;
      for(int i = 0; i < token.length(); i++){
        if(ispunct(token.at(i))){
          token.erase(i, 1);
          i--;
        }
      }
      outTokens.push_back(token);
    }
}

void removeSingleLetterWords(std::vector<std::string> &tokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    auto it = tokens.begin();
    while(it != tokens.end()){
      if((*it).length()==1 && !isdigit((*it).at(0))){
        tokens.erase(it);
      }
      else ++it;
    }
}

void removeStopWords(std::vector<std::string> &tokens,
                     std::unordered_set<std::string> &stopwords) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    auto it = tokens.begin();
    while(it != tokens.end()){
      if(find(stopwords.begin(), stopwords.end(), (*it))!=stopwords.end()){
        tokens.erase(it);
      }
      else ++it;
    }
}

void removeWhiteSpaces(std::vector<std::string> &tokens) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    // You may want to use the trim() method from the trim.*pp files in a2.
    for (size_t i = 0; i < tokens.size(); ++i) {
		    string text = tokens[i];
        tokens[i] = trim(text);
	  }
}

void replaceHyphensWithSpaces(std::string &line) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 5
    replace(line.begin(), line.end(), '-', ' ');
}

void splitLine(std::string &line, std::vector<std::string> &words) {
    // TODO: Implement this method.
    // approximate # of lines of code in Gerald's implementation: < 10
    size_t pos = 0;
    string token;
    string delimiter = " ";
    while ((pos = line.find(delimiter)) != string::npos) {
      token = line.substr(0, pos);
      words.push_back(token);
      line.erase(0, pos + delimiter.length());
    }
    words.push_back(line);
}
