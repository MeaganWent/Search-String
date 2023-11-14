#include "string_search.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>


//function to get text and pattern from the file

//function to run string search

// function to run Boyer Moore string search

// function to run KMP string search
std::vector<int> String_Search::KMP() {
  // vector to store an index of the pattern in the text if found
  std::vector<int> index;
  int shift = 0;
  int j = 0;
  char last_char;

  while(shift < text.length() - pattern.length()) {
    j = shift;
    bool found = false;
    while(text[j] == pattern[j] && j < pattern.length()) {
      j++;
      if(j = pattern.length()){
        found = true;
      }
      
    }
    if(found){
      index.push_back(shift);
    } else {
      shift = shift + 1 + prefix_val[last_char];
    }
  }
  
  return index;
};

//helper function for kmp
void String_Search::prefix() {

};

// function to output running times

// function to output if the pattern was found
