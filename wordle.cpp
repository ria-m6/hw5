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
static void fill_helper(string &pattern, int pos, string floating, const set<string> &dict, set<string> & results);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    // making a copy of input pattern
    string pattern =in;
    //start from 0
    fill_helper(pattern, 0, floating, dict, results);

    return results;
  
}

// Define any helper functions here
static void fill_helper(string &pattern, int pos, string floating, const set<string> &dict, set<string> & results){
  int n = pattern.size();
  //if all positions are placed
  if(pos == n){
    //all floating letters must be used
    if(floating.empty() && dict.find(pattern) != dict.end()){
      results.insert(pattern);
    }
    return;
  }

  //if this position is fixed, move on
  if(pattern[pos]!= '-'){
    fill_helper(pattern, pos+1, floating, dict, results);
  } else{
    //Try every possible letter 
    for(char c ='a';c<='z';c++){
      //place letter at curr blank
      pattern[pos] = c;
      //if c is req floating letter, 
      string nextFloating= floating;
      auto it = nextFloating.find(c);
      if(it != string::npos){
        nextFloating.erase(it, 1);
      }
      //recurse to fill next position
      fill_helper(pattern, pos+1, nextFloating, dict, results);
    }

    //restores blank for other branhces
    pattern[pos] = '-';
  }
}