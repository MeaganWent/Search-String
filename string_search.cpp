#include "string_search.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>


//function to get text and pattern from the file

//function to run string search
// PseudoCode
// Function StringSearch::Basic(str, answer)
    // Initiate Variable count = 0
    // For the length of the str (i)
        // For the length of the answer (j)
            // If the answer at j is not equal to the str at j
                // Break
            // If we are at the end of the loop and never broke out
                // Increment counter
    // Return counter

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
      // end of the pattern is reached so the match was found
      if(j = pattern.length()){
        found = true;
      }
      j++;
    }
    // determines if a shift should be called from lookup or if a match was found
    if(found){
      index.push_back(shift);
      shift += 1;
    } else {
      shift = shift + 1 + prefix_val[last_char];
    }
  }

  // returns all the index(es) where a match was found
  return index;
}

//helper function for kmp to create a vector for looking up num of shifts based on the character
void String_Search::prefix() {
  
  // initialize vector of length pattern to 0's
  for(int i = 0; i < pattern.length(); i++) {
    prefix_val.push_back(0);
  }

  // goes through the pattern to find the number of shifts possible to skip
  int length = 0;
  for(int j = 0; j < pattern.length();j++){
    
    // a shift is possible
    if(pattern[length] == pattern[j]) {
      length += 1;
      prefix_val[j] = length;
    }
    
    // a shift is not possible
    if(pattern[length] != pattern[j] && length != 0) {
      length = prefix_val[length - 1];
    }
  }

}

// function to output running times

// function to output if the pattern was found
