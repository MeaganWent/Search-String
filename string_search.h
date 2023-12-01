// .h file to create Class and store methods for string searching

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

class String_Search {
  // private methods
  private:
    // vars to store text and pattern to search for
    std::string text = "";
    std::string pattern = "";
  
    std::vector<int> prefix_val;
    std::vector<int> Basic_index;
    std::vector<int> KMP_index;
    std::vector<int> BM_index;

  // public methods
  public:
    //function to get text and pattern from the file
    String_Search(std::string text, std::string pattern);

    // preprocessing methods
    void badCharHeuristic(std::string str, int size, int badchar[256]);
    void prefix();

    //function to run string search
    void Basic();
    // function to run Boyer Moore string search
    void BM();
    // function to run KMP string search
    void KMP();
    
    // function to record running times
    std::vector<float> timeFunction();

    // function for outputting results
    void Basic_results(float time);
    void KMP_results(float time);
    void BM_results(float time);

    void ControlF();
};


