/** \file      Stopwatch.cxx 
    \brief     Source for Stopwatch class.
    \author    Doug Hague
    \date      23.07.2013
    \copyright See License.txt
*/
#include <ctime>
#include "Torpy/Stopwatch.hh"

namespace Torpy {

//_____________________________________________________________________________
/** Constructor. */
Stopwatch::Stopwatch() 
  : mState(Undefined),
    mStartTime(Now()),
    mStopTime(Now()),
    mDuration(0.),
    mCounter(0)
{
  start();
}  

//_____________________________________________________________________________
/** Copy constructor. */
Stopwatch::Stopwatch(const Stopwatch& other) 
{
  mState     = other.mState;
  mStartTime = other.mStartTime;
  mStopTime  = other.mStopTime;
  mDuration  = other.mDuration;
  mCounter   = other.mCounter;
}

//_____________________________________________________________________________
/** Assignment operator. */
Stopwatch& Stopwatch::operator=(const Stopwatch& rhs)
{
  mState     = rhs.mState;
  mStartTime = rhs.mStartTime;
  mStopTime  = rhs.mStopTime;
  mDuration  = rhs.mDuration;
  mCounter   = rhs.mCounter;
  return *this;
}

//______________________________________________________________________________
/** Start the stopwatch. 

    If reset is true then reset the stopwatch before
    starting it (including the stopwatch counter).
    Use false to continue timing after a stop() without
    resetting the stopwatch.
*/
void Stopwatch::start(bool reset)
{
  if(reset){
    mState     = Undefined;
    mDuration  = 0;
    mCounter   = 0;
  }

  if(mState != Running)
    mStartTime = Now();

  mState = Running;
  mCounter++;
}

//______________________________________________________________________________
/** Stop the stopwatch. */
void Stopwatch::stop()
{
  mStopTime = Now();
  if(mState == Running)
    mDuration += (mStopTime - mStartTime);
  mState = Stopped;
}

//______________________________________________________________________________
/** Resume a stopped stopwatch. 

    The stopwatch continues counting from the last
    start() onwards (this is like the laptimer function). 
*/
void Stopwatch::lap()
{
  if(mState == Stopped)
    mDuration -= (mStopTime - mStartTime);
  mState = Running;
}

//______________________________________________________________________________
/** Stop the stopwatch (if it is running) and return the realtime 
    (in seconds) passed between the start and stop events. 
*/
double Stopwatch::time()
{
  if(mState == Running) 
    stop();
  return mDuration;
}

//______________________________________________________________________________
/** const Stop the stopwatch (if it is running) and return the realtime 
    (in seconds) passed between the start and stop events. 
*/
double Stopwatch::time() const
{
  return const_cast<Stopwatch*>(this)->time();
}

//______________________________________________________________________________
/** Print the real time passed between the start and stop events to a string. */
string Stopwatch::timeString() const
{
  // get the time (const)
  double realt = const_cast<Stopwatch*>(this)->time();
  int  hours = int(realt / 3600);
  realt -= hours * 3600;
  int min   = int(realt / 60);
  realt -= min * 60;
  // int sec   = int(realt);
  if(realt < 0) realt = 0.;

  // write to formatted c-string
  char* srealt = new char[64];
  sprintf(srealt, "%d:%02d:%02.3f", hours, min, realt);
  // write to string
  string rts(srealt);
  // clean & return
  delete [] srealt;
  return rts;
}

//______________________________________________________________________________
/** Reset the time to time; default = 0. */
void Stopwatch::reset(double time) 
{ 
  stop(); 
  mDuration = time; 
}

//______________________________________________________________________________
/** Print the the real time passed between the start and stop events. */
void Stopwatch::print(std::ostream& os) const
{
  os << timeString().c_str();
}

//______________________________________________________________________________
/** Private static method returning system realtime. */
double Stopwatch::Now()
{
  return double(clock())/CLOCKS_PER_SEC;
}

} // end namespace Torpy
