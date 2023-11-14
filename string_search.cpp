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
  // goes through entire text but not always by a shift of one
  while(shift < text.length() - pattern.length()) {
    j = shift;
    bool found = false;
    // checks each character in the pattern to make sure all match
    while(text[j] == pattern[j] && j < pattern.length()) {
      last_char = pattern[j];
      // end of pattern is reached so match was found
      if(j = pattern.length()){
        found = true;
      }
      j++;
    }
    if(found){
      index.push_back(shift);
    } else {
      shift = shift + 1 + prefix_val[last_char];
    }
  }
  
  return index;
}

//helper function for kmp to create a vector for looking up num of shifts based on the character
void String_Search::prefix() {
  // goes through each character to get the prefix to see how many shifts can be skipped
  for(int i = 0; i < pattern.length(); i++) {
    
  }

}

// function to output running times

// function to output if the pattern was found
