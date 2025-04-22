#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <vector>
#include <unordered_map>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
// curr --> curr string we've built, floating--> available yellow chars, in-->fixed letters, place-->where we are in the string, results-->curr results set to be returned, dict-->same dict from other
void helper(string curr, unordered_map<char, int>& floating, int floating_needed, const string& in, int place, set<string>& results, const set<string>& dict);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> results;
    string curr = in;
    unordered_map<char, int> flot;
    for (int i = 0; i < floating.size(); i++) {
      flot[floating[i]]++;
    }
    helper(curr, flot, floating.length(), in, 0, results, dict);
    return results;

}

// Define any helper functions here
void helper(string curr, unordered_map<char, int>& floating, int floating_needed, const string& in, int place, set<string>& results, const set<string>& dict) {
  // after we're done recursively building, checking if it is a valid word
  if (place == in.size()) {
    if (floating_needed == 0 && dict.find(curr) != dict.end()) {
      results.insert(curr);
      //cout << "Added to results" << endl;
    }
    return;
  }
  if (floating_needed > (in.size() - place)) {
    return;
  }
  // if the letter is already found/fixed
  if (in[place] != '-') {
    helper(curr, floating, floating_needed, in, place + 1, results, dict);
  }
  // otherwise, recursively trying letters
  else {
    // iterating through the floating characters **priority
    for (char guess = 'a'; guess <= 'z'; guess++) {
      bool is_floating = floating.count(guess) && floating[guess] > 0;
      if (is_floating || floating_needed < (int)(in.size() - place)) {
        if (is_floating) {
          floating[guess]--;
          floating_needed--;
        }
        curr[place] = guess;
        helper(curr, floating, floating_needed, in, place + 1, results, dict);
        if (is_floating) {
          floating[guess]++;
          floating_needed++;
        }
      }
    }
  }
}
