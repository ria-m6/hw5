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

    //count how many of each floating letter we need
    map<char,int> need;
    for (char c : floating){
        if (c >= 'a' && c <= 'z')
            need[c]++;
    }

    //for each dict word
    for (const auto& w : dict){
      if ((int)w.size() != n){
        continue;
      }
        

      map<char,int> have;
      bool ok = true;

      //check purity greens, and tally in one pass
      for (int i = 0; i < n; ++i){
        char c = w[i];
        //reject non-lowercase
        if (c < 'a' || c > 'z'){
          ok = false;
          break;
        }
        //reject green slot mismatch
        if (in[i] != '-' && in[i] != c){
          ok = false;
          break;
        }
        //tally letter counts
        have[c]++;
      }
      if (!ok){
        continue;
      }
      

      //enforce floating letters at least count
      for (auto& p : need){
        if (have[p.first] < p.second) {
          ok = false;
          break;
        }
      }
      if (!ok){
        continue;
      }

      results.insert(w);
    }

    return results;
  
}

// Define any helper functions here
