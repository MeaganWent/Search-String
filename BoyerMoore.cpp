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
// and https://favtutor.com/blogs/boyer-moore-algorithm
 
// The preprocessing function for Boyer Moore's bad character heuristic 
// Reference code give by https://www.geeksforgeeks.org/boyer-moore-algorithm-for-pattern-searching/
void badCharHeuristic(std::string str, int size, int badchar[256]) 
{ 
    int i; 
 
    // Initialize all occurrences as -1 
    for (i = 0; i < 256; i++) 
        badchar[i] = -1; 
 
    // Fill the actual value of last occurrence 
    // of a character 
    for (i = 0; i < size; i++) 
        badchar[(int) str[i]] = i; 
} 
 
void search( std::string input, std::string pattern) 
{
    int badchar[256];
    badCharHeuristic(pattern, pattern.size(), badchar); 
 
    int s = 0;   
    while(s <= (input.size() - pattern.size())) 
    { 
        int j = pattern.size() - 1; 
 
        while(j >= 0 && pattern[j] == input[s + j]) 
            j--; 
 
        if (j < 0) 
        { 
            std::cout << "pattern occurs at shift = " <<  s << std::endl; 
            s += (s + pattern.size() < input.size())? pattern.size()-badchar[input[s + pattern.size()]] : 1; 
 
        }
        else
            s += std::max(1, j - badchar[input[s + j]]); 
    } 
} 
 
/* Driver code */
int main() 
{ 
    std::string txt= "ABAAABCD"; 
    std::string pat = "ABC"; 
    search(txt, pat); 
    return 0; 
} 
