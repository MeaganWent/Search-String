#include "string_search.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>

using namespace std;
//function to get text and pattern from the file
String_Search::String_Search(std::string text_file, std::string pattern_file) {
    // store text in Class string
    std::string line;
    ifstream infile;
    infile.open(text_file);

    // get data from file and store it
    while(getline(infile, line)) {
        text += line;
    }
    
    // close the file
    infile.close();

    // store pattern in Class string
    ifstream infile_2;
    infile_2.open(pattern_file);
    
    // get data from the file and store it
    while(getline(infile_2, line)) {
        pattern += line;
    }
    // close the file
    infile_2.close();

}

//function to run string search
// PseudoCode
// Function StringSearch::Basic(str, answer)
    // Create vector indexes
    // For the length of the str (i)
        // For the length of the answer (j)
            // If the answer at j is not equal to the str at j
                // Break
            // If we are at the end of the loop and never broke out
                // Push i to vector
    // Return vector

// function to run Boyer Moore string search

// function to run KMP string search
void String_Search::KMP() {
    
    // vector to store an index of the pattern in the text if found
    int shift = 0;
    int pattern_idx = 0;
    char last_char;
  
    // goes through entire text but not always by a shift of one
    while(shift < text.length() - pattern.length()) {
        pattern_idx = shift;
        bool found = false;
    
        // checks each character in the pattern to make sure all match
        while(text[pattern_idx] == pattern[pattern_idx] && pattern_idx < pattern.length()) {
            last_char = pattern[pattern_idx];
            
            // end of the pattern is reached so the match was found
            if(pattern_idx = pattern.length()){
                found = true;
            }
            // increment counter
            pattern_idx++;
        }
      
        // determines if a shift should be called from lookup or if a match was found
        if(found){
            KMP_index.push_back(shift);
            shift += 1;
        } else {
            shift = shift + 1 + prefix_val[last_char];
        }
    }
}

//helper function for kmp string search to create a vector for looking up num of shifts based on the character
void String_Search::prefix() {
    
    // initialize vector of length pattern to 0's and set length to 0
    prefix_val.resize(pattern.length(),0);
    int length = 0;
    
    // goes through the pattern to find the number of shifts possible to skip
    for(int i = 1; i < pattern.length();i++){

        // a shift is possible
        if(pattern[length] == pattern[i]) {
            length += 1;
            prefix_val[i] = length;

        // shift is not possible
        }else if(pattern[length] != pattern[i] && length != 0) {
            length = prefix_val[length - 1];
            i -= 1;
        }
    }
}

// function to get the time stamp of all the search functions and do a graph and output
float String_Search::timeFunction(){
    //start point
    //call funtions
        // start
    // string search 
        // end 
        //start
    //BM search
        // end
        //start
    //KMP search 
        //end
    //end point

    //get the runtime
    //float output = 1.0 * (c_end - c_start);
    return 0;
}

// function to output running times

// function to output if the pattern was found
