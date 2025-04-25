#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    int n = in.size();

    //counting how many of each floating letter i have to place
    map<char,int> need;
    for (char c : floating) {
      if (c >= 'a' && c <= 'z'){
        need[c]++;
      }
    }

    //scans each candidate in the dict once
    for (const auto& w : dict) {
      //must be the right length
      if ((int)w.size() != n){
        continue;
      }
        

      //skip any word with nonlowercase letters
      bool pure = true;
      for (char c : w) {
        if (c < 'a' || c > 'z') {
          pure = false;
          break;
        }
      }
      if (!pure){
        continue;
      }

      //enforce the fixed (green) letters
      bool ok = true;
      for (int i = 0; i < n; ++i) {
        if (in[i] != '-' && w[i] != in[i]) {
          ok = false;
          break;
        }
      }
      if (!ok){
        continue;
      }

      //count up this words letters
      map<char,int> have;
      for (char c : w){
        have[c]++;
      }
          

      //enforce that each floating letter appears at least as many times as needed
      for (auto& p : need) {
        char c = p.first;
        int want = p.second;
        if (have[c] < want) {
          ok = false;
          break;
        }
      }
      if (!ok){
        continue;
      }
          

      // passed all checks
      results.insert(w);
    }

    return results;

  
}

// Define any helper functions here
