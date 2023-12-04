#include "string_search.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>
#include <iomanip>

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

    prefix_val.resize(pattern.length(),0);
}

//function to run basic string search
void String_Search::Basic(){
    // Bool var to check if our pattern does not match the text
    bool check;
    // For loop to go over entire text and reset check to true
    for(int i = 0; i < text.size(); i++){
        check = true;
        // For loop to compare each element in the text and pattern
        // If they don't match eachother each iteration break out of the loop
        for(int j = 0; j < pattern.size(); j++){
            if(pattern[j] != text[i + j]){
                check = false;
                break;
            }
        }
        // If check never changed, push the current text index to our vector
        if(check == true) {
            this->Basic_index.push_back(i);
        }
    }
}

// function to run Boyer Moore string search

void String_Search::BM() {
    // Initializing vector to hold indexes in which we found the pattern
    this->BM_index.push_back(-1);

    // Pre-Processing for Bad Character Heuristic
    // Geeks for Geeks source code: https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/
    int badchar[256];
    int i; 
    for (i = 0; i < 256; i++) 
        badchar[i] = -1; 
    
    for (i = 0; i < pattern.size(); i++) 
        badchar[(int) pattern[i]] = i; 
    // End of Pre-Processing

    // Shift count initialized. 
    int s = 0; 
    
    // Loops through all the text file. 
    while(s <= (text.size() - pattern.size())) 
    { 
        // Size of the pattern
        int j = pattern.size() - 1; 

        // Checks to see if text equals the pattern, if so, then it will check pattern with decreasing increments, if 
        // it loops through all of the patten array, then pattern has been found
        while(j >= 0 && pattern[j] == text[s + j]) 
            // deincrement 
            j--; 
         // if j < 0 then that mean we have found the apttern 
        if (j < 0) 
        { 
            // inserts into vector, the index of where the pattern starts 
            this->BM_index.push_back(s); 
            
            // Continues checking for indexes 
            if(s + pattern.size() < text.size()){
                s += pattern.size()-badchar[text[s + pattern.size()]];
            } else {
                s += 1;
            }
        }
        else {
            // Did not find pattern, moving onto next index. 
            // Max takes the greater of the two operators. 
            s += std::max(1, j - badchar[text[s + j]]); 
        }
    } 
}

// used https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/ to check to make sure algorithm achually was KMP
// no code was directly copied but used the link to make sure the search and prefix functions performed as a KMP algorithm should, 
// citing as a source for KMP and prefix functions

// function to run KMP string search
void String_Search::KMP() {
    prefix();
    
    // initialize vars for indexing
    int shift = 0;
    int pattern_idx = 0;
  
    // goes through the entire text but not always by a shift of one
    while(text.size() - shift >= pattern.size() - pattern_idx) {
    
        // checks each character in the pattern to make sure all match
        if(text[shift]==pattern[pattern_idx]) {
            // increment counter
            pattern_idx += 1;
            shift += 1;
        }
      
        // determines if a shift should be called from lookup or if a match was found
        if(pattern_idx == pattern.size()){
            KMP_index.push_back(shift-pattern_idx);
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
    int length = 0;
    int i = 1;

    // goes through the pattern to find the number of shifts possible to skip
    while(i < pattern.length()){

        // a shift is possible
        if(pattern[length] == pattern[i]) {
            length += 1;
            prefix_val[i] = length;
            i += 1;

        // shift is not possible
        }else {
            if(length != 0) {
                length = prefix_val[length - 1];
            } else {
                i++;
            } 
        }
    }
}


// function to get the time stamp of all the search functions and do a graph and output
std::vector<float> String_Search::timeFunction(){
    // create a txt file to store the time stamps
    std::ofstream outFile;

    outFile.open("Runtime.txt");
    
    // file header
    outFile << "Comparing Runtime Efficiency: Basic String Search vs. Boyer-Moore vs. Knuth-Morris-Pratt Algorithms" << std::endl;
    outFile << std::endl;

    // create a vector to store the time stamps
    vector<float> totalTime;

    // create a unsigned long to store the time stamp
   unsigned long starTime, endTime;

    //call funtions
        
    // string search 
    //start timer
    starTime = clock();
    //call function
    Basic();
    //end timer
    endTime = clock();
    //calculate the runtime
    float Basic_time = (float)(endTime - starTime) / CLOCKS_PER_SEC;
    //store the time in the vector
    totalTime.push_back(Basic_time);
    
    //BM search
    //start timer
    starTime = clock();
    //call function
    BM();
    //end timer
    endTime = clock();
    //calculate the runtime
    float BM_time = (float)(endTime - starTime) / CLOCKS_PER_SEC;
    //store the time in the vector
    totalTime.push_back(BM_time);

    //KMP search 
    //start timer
    starTime = clock();
    //call function
    KMP();
    //end timer
    endTime = clock();
    //calculate the runtime
    float KMP_time = (float)(endTime - starTime) / CLOCKS_PER_SEC;
    //store the time in the vector
    totalTime.push_back(KMP_time);


    // write the text size, pattern size and time stamps to the txt file
    outFile << "Text size: " << text.size() << std::endl;
    outFile << "Pattern size: " << pattern.size() << std::endl;
    outFile << std::fixed<< std::setprecision(6) << "Basic search string runtime: "<< totalTime[0] << " seconds."<< std::endl;
    outFile << std::fixed<< std::setprecision(6) << "Boyer Moore runtime: " << totalTime [1] <<" seconds."<<std::endl; 
    outFile << std::fixed<< std::setprecision(6) << "Knuth-Morris-Pratt runtime: " << totalTime[2] << " seconds." << std::endl;
    
    //close the txt file
    outFile.close();

    // return the time stamps
    return totalTime;
}

// function to output Basic String Search results
void String_Search::Basic_results(float time) {
    std::ofstream file;

    file.open("Basic-Results.txt");
    
    // file headingAmerican Standard Code for Information Interchange
    file << "Results for the Basic string search algorithm:" << std::endl;
    file << std::endl;

    // state if pattern was found or not and if so where
    if(Basic_index.size() == 0){
        file << "The pattern " << pattern << " was not found in the text" << std::endl;
    } else if(Basic_index.size() == 1){
        file << "The pattern " << pattern << " was found in the text at index " << Basic_index[0] << std::endl;
    } else {
        file << "The pattern " << pattern << " was found in the text at indexes ";
        for(int i = 0; i < Basic_index.size(); i++){
            file << Basic_index[i] << " ";
        }
        file << std::endl;
    }

    // state runtime
    file << "The runtime for Basic was: " << std::fixed << std::setprecision(6) << time << std::endl;

    file.close();
}

// function to output Boyer Moore results
void String_Search::BM_results(float time) {
    std::ofstream file;

    file.open("BM-Results.txt");
    
    // file heading
    file << "Results for the Boyer Moore string search algorithm:" << std::endl;
    file << std::endl;

    // state if pattern was found or not and if so where
    if(BM_index.size() == 1){
        file << "The pattern " << pattern << " was not found in the text" << std::endl;
    } else {
        file << "The pattern " << pattern << " was found in the text at index(s) ";
        for(int i = 1; i < BM_index.size(); i++){
            file << BM_index[i] << " ";
        }
        file << std::endl;
    }

    // state runtime
    file << "The runtime for BM was: " << std::fixed << std::setprecision(6) << time << std::endl;

    file.close();
}

// function to output KMP results
void String_Search::KMP_results(float time) {
    std::ofstream file;

    file.open("KMP-Results.txt");
    
    // file heading
    file << "Results for the Knutt-Morris-Pratt string search algorithm:" << std::endl;
    file << std::endl;

    // state if pattern was found or not and if so where
    if(KMP_index.size() == 0){
        file << "The pattern " << pattern << " was not found in the text" << std::endl;
    } else if(KMP_index.size() == 1){
        file << "The pattern " << pattern << " was found in the text at index " << KMP_index[0] << std::endl;
    } else {
        file << "The pattern " << pattern << " was found in the text at indexes ";
        for(int i = 0; i < KMP_index.size(); i++){
            file << KMP_index[i] << " ";
        }
        file << std::endl;
    }

    // state runtime
    file << "The runtime for KMP was: " << std::fixed << std::setprecision(6) << time << std::endl;

    file.close();
}

void String_Search::ControlF() {
std::ofstream file;
    file.open("ControlF.txt");
    if(KMP_index.size() > 0 ){
        int Total = 0;
        int patternEnd = pattern.size();
        for(int i = 0; i < text.size(); i++){
            if(KMP_index[Total] == i){
                file << "**";
            }

            if(KMP_index[Total]+ pattern.size() == i){
                file << "**";
                Total ++;
            }

            file << text[i];
        }
    } else {
        for(int i = 0; i < text.size(); i++){
            file << text[i];
        }
    }

    file.close();
}
