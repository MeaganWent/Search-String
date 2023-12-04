This C++11 program implements two efficient string-searching algorithms, Boyer-Moore and Knuth-Morris-Pratt, to determine whether a given pattern occurs in a given text or not. This program also measures and compares the runtimes of these algorithms with a naive string-searching algorithm. In order for the Boyer-Moore functionality to work, the text file as to contain less than 256 different elements or a text file within ACSII stipulations. 

Our implementation of these string searching algorithms is to create a Ctrl+F function which will be seen in the ControlF output file.

The steps to use and run the program are as follows:

  - Write the text you want to search in the text.txt file and the pattern/word you want to find in the pattern.txt file
  
  - Compile the main.cpp and string_search.cpp with g++ in GitHub or a platform of your choice

        g++ -std=c++11 main.cpp string_search.cpp -o string_search
    
  - Run the executable file with /textfile/text_1.txt and /textfile/pattern_1.txt as arguments

        ./string_search text.txt pattern.txt
  - Output files:
    - Basic-Result.txt, KMP-Result.txt, BM-Results.txt: Show the indexs in which the pattern was found, if at all. Also, the time it took to run for their respective algorithm. 
    - Runtime.txt: Compares all three search string alogrithms time results while also providing the length of the text string and the pattern string. 
    - ControlF.txt: Outputs the text file with the pattern "highlighted" by being surrounded by "**". 
