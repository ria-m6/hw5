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

    //count how many of each letter we must still place 
    int need[26] = {0};
    for (char c : floating) {
      need[c - 'a']++;
    }

    //scanning every dictionary word once
    for (const string& w : dict) {
      if ((int)w.size() != n) continue;  // wrong length

      //check fixed (green) letters
      bool ok = true;
      for (int i = 0; i < n; ++i) {
        if (in[i] != '-' && w[i] != in[i]) {
          ok = false;
          break;
        }
      }
      if (!ok) continue;

      //count up letters in this candidate
      int have[26] = {0};
      for (char c : w) {
        have[c - 'a']++;
      }

      //ensure we meet the floating requirements
      for (int i = 0; i < 26; ++i) {
        if (have[i] < need[i]) {
          ok = false;
          break;
        }
      }
      if (!ok){
        continue;
      } 

      //if we reach here then w matches both fixed and floating constraints
      results.insert(w);
    }

    return results;
  
}

// Define any helper functions here
