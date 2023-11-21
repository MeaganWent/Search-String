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
    
    // initialize vars for indexing
    int shift = 0;
    int pattern_idx = 0;
  
    // goes through the entire text but not always by a shift of one
    while(shift < text.size()) {
        bool found = false;
    
        // checks each character in the pattern to make sure all match
        if(text[shift]==pattern[pattern_idx] && pattern_idx < pattern.size()) {
            // increment counter
            pattern_idx += 1;
            shift += 1;
        }

        // end of the pattern is reached so the match was found
        if(pattern_idx == pattern.size()){
            found = true;
            cout << shift << endl; //testing for runtime
        }
      
        // determines if a shift should be called from lookup or if a match was found
        if(found){
            KMP_index.push_back(shift);
            pattern_idx = prefix_val[pattern_idx-1];
        } else if(text[shift] != pattern[pattern_idx] && shift < text.size()) {
            // get new index to check for the pattern
            if(pattern_idx != 0) {
                pattern_idx = prefix_val[pattern_idx-1];
            } else {
                // increment shift
                shift += 1;
            }  
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
vector <float> String_Search::timeFunction(){
   unsigned long starTime, endTime;

    //call funtions
        starTime = clock();
        KMP();
        endTime = clock();
    // string search 
        // end 
        //start
    //BM search
        // end
        //start
    //KMP search 
    //KMP();
        //end
    //end point

    //get the runtime
    vector<float> total_time;
    float runtime =1.0 * (endTime - starTime) / CLOCKS_PER_SEC; //why do I need the 1.0 here?
    total_time.push_back(runtime);
    //float output = 1.0 * (c_end - c_start);
    cout << std::fixed << std::setprecision(4) << total_time[0] << endl;
    return total_time;
    
}
// function to output String Search results

// function to output Boyer Moore results

// function to output KMP results
void KMP_results(float time) {
    // file heading
    file << "Results for the Knutt-Morris-Pratt string search algorithm:" << std::endl;

    // state if pattern was found or not and if so where
    if(KMP_index.size() == 0){
        file << "pattern was not found in text" << std::endl;
    } else if(KMP_index.size() == 1){
        file << "pattern was found in text at index " << KMP_index[0] << std::endl;
    } else {
        file << "pattern was found in text at indexes ";
        for(int i = 0; i < KMP_index.size(); i++){
            file << KMP_index[i] << " ";
        }
        file << std::endl;
    }

    // state runtime
    file << "The runtime for KMP was: " << time << std::endl;
        
}

// function to output comparisons
