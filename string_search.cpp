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

}

//function to run basic string search
void String_Search::Basic(){
    bool check;
    for(int i = 0; i < text.size(); i++){
        check = true;
        for(int j = 0; j < pattern.size(); j++){
            if(pattern[j] != text[i + j]){
                check = false;
                break;
            }
        }
        if(check == true) {
            this->Basic_index.push_back(i);
        }
    }
}

// function to run Boyer Moore string search
    // NOT COMPLETED -- I HAVE TO ADD COMMENTS. 

void String_Search::BM() {
    this->BM_index.push_back(-1);
    int badchar[256];
    int i; 
    for (i = 0; i < 256; i++) 
        badchar[i] = -1; 
    
    for (i = 0; i < pattern.size(); i++) 
        badchar[(int) pattern[i]] = i; 
     
    int s = 0;   
    while(s <= (text.size() - pattern.size())) 
    { 
        int j = pattern.size() - 1; 
 
        while(j >= 0 && pattern[j] == text[s + j]) 
            j--; 
 
        if (j < 0) 
        { 
            std::cout << "pattern occurs at shift = " <<  s << std::endl; 
            this->BM_index.push_back(s + pattern.size()); 
            s += (s + pattern.size() < text.size())? pattern.size()-badchar[text[s + pattern.size()]] : 1; 
 
        }
        else
            s += std::max(1, j - badchar[text[s + j]]); 
    } 
}

// function to run KMP string search
void String_Search::KMP() {
    prefix();
    
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
std::vector<float> String_Search::timeFunction(){
    std::ofstream outFile;
    vector<float> total_time;

   unsigned long starTime, endTime;
   outFile.open("output.txt");

    //call funtions
        
    // string search 
       
    //BM search
    starTime = clock();
    BM();
    endTime = clock();
    float BM_time = (float)(endTime - starTime) / CLOCKS_PER_SEC;
    total_time.push_back(BM_time);

    //KMP search 
    starTime = clock();
    KMP();
    endTime = clock();
    float KMP_time = (float)(endTime - starTime) / CLOCKS_PER_SEC;
    total_time.push_back(KMP_time);
    //end point

    //get the runtime
    float runtime =1.0 * (endTime - starTime) / CLOCKS_PER_SEC; 
    total_time.push_back(runtime);
    //float output = 1.0 * (c_end - c_start);
    //total_time.push_back(output);

    //print the the comparison of the runtimes
    outFile << "TotalBM runtime: " << std::fixed << std::setprecision(6) << BM_time << "seconds" << std::endl;
    outFile << "KMP runtime: " << std::fixed << std::setprecision(6) << KMP_time << " seconds" << std::endl;
    //outFile << "Total runtime: " << std::fixed << std::setprecision(6) << runtime << " seconds" << std::endl;
    

    outFile.close();
    return total_time;
    
    
}
// function to output Basic String Search results
void String_Search::Basic_results(float time) {
    std::ofstream file;

    file.open("Basic-Results.txt");
    
    // file heading
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
