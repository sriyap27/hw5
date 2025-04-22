#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
// curr --> curr string we've built, floating--> available yellow chars, in-->fixed letters, place-->where we are in the string, results-->curr results set to be returned, dict-->same dict from other
void helper(string curr, vector<char> floating, const string& in, int place, set<string>& results, const set<string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> results;
    string curr = "";
    vector<char> flot;
    for (int i = 0; i < floating.size(); i++) {
      flot.push_back(floating[i]);
    }
    helper(curr, flot, in, 0, results, dict);
    return results;

}

// Define any helper functions here
void helper(string curr, vector<char> floating, const string& in, int place, set<string>& results, const set<string>& dict) {
  // after we're done recursively building, checking if it is a valid word
  if (place == in.size()) {
    if (floating.empty() && dict.find(curr) != dict.end()) {
      results.insert(curr);
      //cout << "Added to results" << endl;
    }
    return;
  }
  if (floating.size() > (in.size() - place)) {
    return;
  }
  // if the letter is already found/fixed
  else if (in[place] != '-') {
    curr += in[place];
    helper(curr, floating, in, place + 1, results, dict);
  }
  // otherwise, recursively trying letters
  else {
    // iterating through the floating characters **priority
    for (int i = 0; i < floating.size(); i++) {
      string newStr = curr + floating[i];
      vector<char> temp = floating;
      temp.erase(temp.begin() + i);
      helper(newStr, temp, in, place + 1, results, dict);
    }
    // iterating through the remaining letters
    string letters = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < letters.size(); i++) {
        string newStr = curr + letters[i];
        helper(newStr, floating, in, place + 1, results, dict);
    }
  }
}
