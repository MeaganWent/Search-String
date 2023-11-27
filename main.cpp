/*
**String Search II**
^^^

**_Implement algorithms_**
  - knuth-morris-pratt
  - boyer-moore

**_Benchmark all algorithms recording their runtime_**

- generate plots of running time of multiple sizes
*/
#include "string_search.h"
#include <iostream>
#include <string>

int main(int argc,char*argv[]){
  // get file names from user
  std::string text_name(argv[1]);
  std::string pattern_name(argv[2]);

  //function to get text and pattern from the file and store in Class vars
  String_Search search(text_name, pattern_name);

  // function for preprocessing for KMP
  search.prefix();

  //function to run string search
  search.BM();
  std::vector<float> BM_timeStamps;
  BM_timeStamps = search.timeFunction();
  // std::vector<int> Basic_indexes = search.Basic();
  search.BM_results(BM_timeStamps[0]);

  // function to search string called in time function
  std::vector<float> timeStamps;
  timeStamps = search.timeFunction();

  search.KMP_results(timeStamps[0]);

  // function to output running times

  // function to output if the pattern was found


}
