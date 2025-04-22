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
bool helper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int day, int workers, map<Worker_T, int>& freq);

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
  sched.resize(avail.size(), vector<Worker_T>(dailyNeed, INVALID_ID));
  map<Worker_T, int> freq;
  return helper(avail, dailyNeed, maxShifts, sched, 0, 0, freq);



}
bool helper(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, int day, int workers, map<Worker_T, int>& freq) {
  if (day >= avail.size() && workers == 0) {
    return true;
  }
  for (unsigned int i = 0; i < avail[day].size(); i++) {
    if (avail[day][i]) {
      if (freq[i] < maxShifts) {
        bool assigned = false;
        for (unsigned int j = 0; j < workers; j++) {
          if (sched[day][j] == i) {
            assigned = true;
            break;
          }
        }
        if (assigned) continue;
        if (!assigned) {
          sched[day][workers] = i;
          freq[i]++;
        }
        if (workers + 1 == dailyNeed) {
          if (helper(avail, dailyNeed, maxShifts, sched, day + 1, 0, freq)) return true;
        }
        else {
          if (helper(avail, dailyNeed, maxShifts, sched, day, workers + 1, freq)) return true;
        }
        freq[i]--;
        sched[day][workers] = INVALID_ID;
      }
    }
  }
  return false;
}


