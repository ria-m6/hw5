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
typedef vector<size_t> ShiftCount;

bool schedule_helper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, ShiftCount& shifts, size_t day, size_t slot);

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

    size_t numDays = avail.size();
    if(dailyNeed == 0){
      return false;
    }
    size_t numWorkers = avail[0].size();

    //initializing schedule with INVALID_ID
    sched.assign(numDays, vector<Worker_T>(dailyNeed, INVALID_ID));
    ShiftCount shifts(numWorkers, 0);

    return schedule_helper(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);

}


//recursive function
bool schedule_helper(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, ShiftCount& shifts, size_t day, size_t slot){
  
  size_t numDays = avail.size();
  size_t numWorkers = avail[0].size();

  //if all the days are scheduled
  if(day == numDays){
    return true;
  }

  //if today's slots are all filled up, then move to the next day
  if(slot == dailyNeed){
    return schedule_helper(avail, dailyNeed, maxShifts, sched, shifts, day+1, 0);
  }

  //try each workers for current day and slot
  for(Worker_T w =0; w<numWorkers; ++w){
    if(!avail[day][w] || shifts[w]>=maxShifts){
      continue;
    }
    //making sure that they havent already been assigned to this day
    bool used = false;
    for(size_t s =0; s<slot; ++s){
      if(sched[day][s]==w){
        used = true;
        break;
      }
    }
    if(used){
      continue;
    }

    //assign the worker way
    sched[day][slot] = w;
    ++shifts[w];

    //recurse to next slot
    if(schedule_helper(avail, dailyNeed, maxShifts, sched, shifts, day, slot+1)){
      return true;
    }

    //Backtrack
    --shifts[w];
    sched[day][slot]=INVALID_ID;
  }
  




  return false;
}

