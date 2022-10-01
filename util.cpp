#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  set<string> w;
  int count = 0; //keep track of how many punctuations there are
  string temp;
  int start = 0; //keep track of where to start for substring 
  for(unsigned int i=0; i<rawWords.size(); i++){
      if(!isalpha(rawWords[i])){
          temp = rawWords.substr(start,count);
          if(temp.size() >=2){
            temp = convToLower(temp);
            w.insert(temp);
          }
          start = i+1;
          count = 0;
      }
      else if(i == rawWords.size()-1){
        temp = rawWords.substr(start,count+1);
        temp = convToLower(temp);
        w.insert(temp);
      }
      else{
        count++;
      }
      
  }
  return w;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

//testing parseStringToWords()
/*int main(int argc, char* argv[]){

    set<string> test = parseStringToWords("h'uhuh'ok.weird");
    for (auto it = test.begin(); it !=test.end(); ++it)
    {
        cout << *it << endl;
    }


    return 0;
}*/