#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool assignShifts(const AvailabilityMatrix& availability,
    size_t shiftsPerDay,
    size_t maxShifts,
    size_t currentDay,
    size_t shiftSlot,
    DailySchedule& schedule,
    map<Worker_T,int>& remainingShifts
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    const size_t numDays = avail.size();
    const size_t numWorkers=avail[0].size();
    sched.resize(numDays);                                
    for (size_t d = 0; d < numDays; ++d) {
      sched[d].resize(dailyNeed, INVALID_ID);         
    }
    map<Worker_T,int> shiftsLeft;
    for (Worker_T w=0; w<numWorkers;w++){
      shiftsLeft[w]=maxShifts;
    }

    return assignShifts(avail,dailyNeed,maxShifts,0,0,sched,shiftsLeft);

}
bool assignShifts(const AvailabilityMatrix& availability,
    size_t shiftsPerDay,
    size_t maxShifts,
    size_t currentDay,
    size_t shiftSlot,
    DailySchedule& schedule,
    map<Worker_T,int>& remainingShifts
){
    if (currentDay == availability.size()){
      return true;
    }

    for (Worker_T workerId=0;workerId<(Worker_T)availability[currentDay].size();workerId++){
      if (availability[currentDay][workerId]&& remainingShifts[workerId]>0){
        schedule[currentDay][shiftSlot]=workerId;
        remainingShifts[workerId]--;
        size_t nextDay=currentDay + (shiftSlot +1 ==shiftsPerDay ? 1:0);
        size_t nextSlot= (shiftSlot + 1 == shiftsPerDay ? 0 : shiftSlot + 1);

        if (assignShifts(availability,shiftsPerDay,maxShifts,nextDay,nextSlot,schedule,remainingShifts)){
          return true;
        }

        schedule[currentDay][shiftSlot] = INVALID_ID;
        remainingShifts[workerId++];

      }
    }
  return false;

}




   
    // // if (numDays==0){
    // //   return false;
    // // }
    // const size_t numDays = avail.size();
    // const size_t numWorkers=avail[0].size();
    // sched.resize(numDays);                                
    // for (size_t d = 0; d < numDays; ++d) {
    //   sched[d].resize(dailyNeed, INVALID_ID);         
    // }
    // map<Worker_T,int> shiftsLeft;
    // for (Worker_T w=0; w<numWorkers;w++){
    //   shiftsLeft[w]=maxShifts;
    // }

    // vector<vector<int>> nextTry(numDays,vector<int>(dailyNeed,0));
    // size_t day=0;
    // size_t slot=0;
    // while (true){
    //   if (day==numDays){
    //     return true;
    //   }

    //   bool placed=false;
    //   int &i=nextTry[day][slot];
    //   while (i<(int)numWorkers){
    //     Worker_T w=i++;
    //     if (avail[day][w] && shiftsLeft[w]>0){
    //       sched[day][slot]=w;
    //       shiftsLeft[w]--;

    //       if (slot+1==dailyNeed){
    //         day++;
    //         slot=0;
    //       }
    //       else{
    //         slot++;
    //       }

    //       if (day<numDays){
    //         nextTry[day][slot]=0;
    //       }
    //       placed=true;
    //       break;
    //     }
    //   }

    //     if (placed){
    //       continue;
    //     }

    //     if (day==0&&slot==0){
    //       break;
    //     }

    //     if (slot==0){
    //       day--;
    //       slot=dailyNeed-1;
    //     }
    //     else{
    //       slot--;
    //     }

    //     Worker_T prev=sched[day][slot];
    //     sched[day][slot]=INVALID_ID;
    //     shiftsLeft[prev]++;
      

      

    // }
    // return false;
    
