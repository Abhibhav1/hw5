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
    int n=in.size();

    //how many times the floating letters will appear
    map<char,int> flCount;
    for (char c:floating){
      flCount[c]++;
    }

    for (auto const& w:dict){
      if ((int)w.size!=n){
        continue;
      }

      bool ok=true;
      for (int i=0;i<n;i++){
        if (in[i]!='-'&&in[i]!=w[i]){
          ok=false;
          break;
        }
      }
      if (ok==false){
        continue;
      }

      map<char,int> blankCount;
      for (int i=0;i<n;i++){
        if (in[i]=='-')
          blankCount[w[i]]++;
      }

      for (auto const& [c,n]:flCount){
        if (blankCount[c]!=n){
          ok=false;
          break;
        }
      }

      if (ok==false){
        continue;
      }

      results.insert(w)

    }
    return results;

}

// Define any helper functions here
