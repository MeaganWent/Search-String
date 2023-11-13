#include <iostream>
#include <ostream>
#include <string>
#include <vector>

Class String_Search {
  private:
    std::string text;
    std::string pattern;
    std::vector prefix_val;

  public:
    //function to get text and pattern from the file

    //function to run string search

    // function to run Boyer Moore string search

    // function to run KMP string search
    std::vector KMP();

    //helper function for kmp
    void prefix();

    // function to output running times

    // function to output if the pattern was found
};


