#include <iostream>
#include <ostream>
#include <string>
#include <vector>

class String_Search {
  private:
    std::string text = "";
    std::string pattern = "";
    std::vector<int> prefix_val;
    std::vector<int> KMP_index;

  public:
    //function to get text and pattern from the file
    String_Search(std::string text, std::string pattern);

    //function to run string search
    // std::vector<int> Basic();
    // function to run Boyer Moore string search

    // function to run KMP string search
    void KMP();

    //helper function for kmp
    void prefix();

    // function to output running times
     std::vector<float> timeFunction();

    // function for outputing results of KMP
    void KMP_result(float time);

    // function to output if the pattern was found
};


