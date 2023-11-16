/*
This algorithm follows the Boyer-Moore search string which aims to be an effiencent string search. 
This algorithm searches from the start of the looking for string, then will find where that matches up in the string. From there it will take the first misplaced
values and search for its correctly value until it finds the correct values for all given integers.  
*/

!!! NOT COMPLETED !!!
// input - takes in Correct which is the string we're looking for, and Search which is the string we're searching through
// implement badCharHeuristic 
  // all occurrences as -1
  // Fill the actual value of last occurrence of a character

#include <iostream>
#include <string>
#include <algorithm>
 
// The preprocessing function for Boyer Moore's bad character heuristic 
// Reference code give by https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/
// and https://favtutor.com/blogs/boyer-moore-algorithm
void badCharHeuristic(std::string str, int size, int badchar[NO_OF_CHARS]) { 
    int i; 
 
    // Initialize all occurrences as -1 
    for (i = 0; i < NO_OF_CHARS; i++) 
        badchar[i] = -1; 
 
    // Fill the actual value of last occurrence 
    // of a character 
    for (i = 0; i < size; i++) 
        badchar[(int) str[i]] = i; 
} 
 

void search(std::string Search, std::string Find) 
{ 
    int search = Search.size(); 
    int find = Find.size();
 
    int badchar[NO_OF_CHARS]; 

    badCharHeuristic(Find, search, badchar); 
 
    int shift = 0; 
    while(shift <= (find - search)) { 
        int j = search - 1; 

        while(j >= 0 && Find[j] == Search[search + j]) 
            j--; 
 

        if (j < 0) 
        { 
            std::cout << "pattern occurs at shift = " <<  search << std::endl; 
            shift += (shift + search < find)? search-badchar[Search[shift + search]] : 1; 
        } 
 
        else
            shift += max(1, j - badchar[Search[shift + j]]); 
    } 
} 
 

int main() { 
    std::string Search= "ABAAABCD"; 
    std::string Find = "ABC"; 
    search(Search, Find); 
    return 0; 
}
