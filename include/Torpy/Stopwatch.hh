/** \file      Stopwatch.hh 
    \brief     Header for Stopwatch class.
    \author    Doug Hague
    \date      23.07.2013
    \copyright See License.txt
*/
#ifndef TP_STOPWATCH_HH
#define TP_STOPWATCH_HH

#include "Torpy/Common.hh"

namespace Torpy {

/** \class Stopwatch
    \brief Class to facilitate elapsed time.
*/
class Stopwatch {
public:
  Stopwatch();
  Stopwatch(const Stopwatch& other);
  Stopwatch& operator=(const Stopwatch& rhs);
  inline virtual ~Stopwatch() { }

  inline int counter() const { return mCounter; }
  double time();
  double time() const;
  string timeString() const;

  void start(bool reset = true);
  void stop();
  void lap();
  void reset(double time = 0);

  void print(ostream& os) const;

private:
  /** \enum eSwState Stopwatch state. */
  enum eSwState { 
    Undefined = 0, //!< undefined state
    Stopped   = 1, //!< stopped state
    Running   = 2  //!< running state
  };

  eSwState mState;       //!< stopwatch state
  double   mStartTime;   //!< wall clock start time
  double   mStopTime;    //!< wall clock stop time
  double   mDuration;    //!< total wall clock time
  int      mCounter;     //!< number of times the stopwatch was started

  static double Now();
};

} // end namespace BlowCh

#endif // end TP_STOPWATCH_HH
