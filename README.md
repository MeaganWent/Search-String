This is a C++11 program implements two efficient string-searching algorithms, Boyer-Moore and Knuth-Morris-Pratt, to determine whether a given pattern occurs in a given text or not. This can be useful for finding a specific keyword in a large document, similar to the Ctrl+F function. This program also measures and compares the runtimes of these algorithms with a naive string-searching algorithm. The steps to use and run the program are as follows:

  - Write the text you want to search in the text.txt file and the pattern/word you want to find in the pattern.txt file
  
  - Compile the main.cpp and string_search.cpp with g++ in GitHub or a platform of your choice

        g++ -std=c++11 main.cpp string_search.cpp -o string_search
    
  - Run the executable file with text.txt and pattern.txt as arguments

        ./string_search text.txt pattern.txt
    
  - The program will output the index(es) of the occurrence of the pattern in the text, or will indicate that the pattern was not found, as well as the runtimes of the three algorithms
