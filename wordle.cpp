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
void backtrack(size_t pos,
  string& cur,
  int blanks_left,
  string rem_floasts,
  const set<string>& dict,
  set<string>& results
);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
  set<string> results;
  int blanks=0;
  for (char ch:in){
    if (ch=='-'){
      blanks++;
    }
  }
  string current=in;
  backtrack(0,current,blanks,floating,dict,results);
  return results;

}

// Define any helper functions here

void backtrack(size_t pos,
  string& cur,
  int blanks_left,
  string rem_floats,
  const set<string>& dict,
  set<string>& results
){
  if (pos==cur.size()){
    if (rem_floats.empty() && dict.count(cur)){
      results.insert(cur);
    }
    return;
  }
  if (cur[pos]!='-'){
    backtrack(pos+1,cur,blanks_left,rem_floats,dict,results);
    return;
  }
  for (char c='a';c<='z';c++){
    string next_floats=rem_floats;
    auto it=next_floats.find(c);
    if (it!=string::npos){
      next_floats.erase(it,1);
    }
    else if(blanks_left<=(int)rem_floats.size()){
      continue;
    }

    cur[pos]=c;
    backtrack(pos+1,cur,blanks_left-1,next_floats,dict,results);

  }
  cur[pos]='-';
}



    // Add your code here
    // set<string> results;
    // int n=in.size();

    // //how many times the floating letters will appear
    // map<char,int> flCount;
    // for (char c:floating){
    //   flCount[c]++;
    // }

    // for (auto const& w:dict){
    //   if ((int)w.size()!=n){
    //     continue;
    //   }

    //     bool allLower = true;
    //     for (char ch : w) {
    //       if (ch < 'a' || ch > 'z') {
    //         allLower = false;
    //         break;
    //       }
    //     }
    //     if (!allLower)
    //       continue;

    //   bool ok=true;
    //   for (int i=0;i<n;i++){
    //     if (in[i]!='-'&&in[i]!=w[i]){
    //       ok=false;
    //       break;
    //     }
    //   }
    //   if (ok==false){
    //     continue;
    //   }
    //   if (floating.empty()) {
    //     results.insert(w);
    //     continue;
    //   }


    //   map<char,int> blankCount;
    //   for (int i=0;i<n;i++){
    //     if (in[i]=='-')
    //       blankCount[w[i]]++;
    //   }

    //   for (const auto& pair : flCount) {
    //     char c = pair.first;
    //     int required = pair.second;
    //     if (blankCount[c]<required){
    //       ok=false;
    //       break;
    //     }
    //   }

    //   if (ok==false){
    //     continue;
    //   }

    //   results.insert(w);

    // }
    // return results;