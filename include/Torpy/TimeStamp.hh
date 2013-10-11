/** \file      TimeStamp.hh 
    \brief     Header for TimeStamp class
    \author    Doug Hague
    \date      03.10.2013
    \copyright See License.txt
*/
#ifndef TP_TIMESTAMP_HH
#define TP_TIMESTAMP_HH

#include <ctime>              // for struct tm, gmtime
#include "Torpy/AbsObject.hh"  // mother class

namespace Torpy {

/** \typedef tm_t 
    Equivalent to struct C/C++ standard library time struct  
    <a href="cplusplus.com/reference/ctime/tm/" >tm</a>.
*/
typedef struct tm tm_t;


/** \class TimeStamp
    \brief Seconds since Jan 1, 1970 00:00:00 UTC.

    This class holds a single integer to be interpreted as 
    "Unix Time Stamp": seconds since Jan 1, 1970 00:00:00 UTC,
    where UTC is "Universal Time, Coordinated".

    In essence, this is a integer with 
    methods which allow setting, getting and conversion consistent 
    with interpreting the integer as seconds UTC.
    Thus, there are methods which allow this class to interact with 
    other TimeStamp objects, a (signed) integer, and 
    <a href="en.wikipedia.org/wiki/ISO_8601" >ISO-8601</a>
    formatted "time-strings", i.e. "1970-01-01T00:00:00+00:00".

    \note This class does not hold sub-second times.
*/
class TimeStamp : public AbsObject {
public:
  TimeStamp(int uts = -1);
  TimeStamp(string isoString);
  TimeStamp(const TimeStamp& other);
  virtual AbsObject* clone(const char* /*newName*/) const;
  virtual TimeStamp& operator=(const TimeStamp& rhs);
  inline virtual ~TimeStamp() { }

  bool isEmpty() const;
  void clear();
  bool isEqual(const AbsObject& other) const;

  inline bool isSortable() const { return true; }
  int compare(const AbsObject& other) const;

  //! Set the UTS value
  inline void set(int uts){ mUts = uts; }
  void set(string isoString);
  void setNow();
  //! Get the UTS value
  inline time_t uts() const { return mUts; }
  string asString(bool includeOffset = true) const;
  string asStringGm() const;
  string asDescription() const;

  // timezone info
  string tzAbbrev() const;
  string tzOffset() const;
  int tzSecondsOffset() const;

  // arithmetic
  double difference(const TimeStamp& other) const;
  TimeStamp& operator+=(int seconds);
  TimeStamp& operator-=(int seconds);
  TimeStamp& operator+=(string tzOffset);
  TimeStamp& operator-=(string tzOffset);

  // static utilities
  static inline unsigned int SecPerMin(){  return 60; }
  static inline unsigned int SecPerHour(){ return 3600; }
  static inline unsigned int SecPerDay(){  return 86400; }
  static inline unsigned int SecPerWeek(){ return 604800; }
  static inline unsigned int SecPerYear(){ return 31536000; }
  static inline double SecToMin(double sec){  return sec/SecPerMin(); }
  static inline double SecToHour(double sec){ return sec/SecPerHour(); }
  static inline double SecToDay(double sec){  return sec/SecPerDay(); }
  static inline double SecToWeek(double sec){ return sec/SecPerWeek(); }
  static inline double SecToYear(double sec){ return sec/SecPerYear(); }
  static inline double MinToSec(double min){   return min *SecPerMin(); }
  static inline double HourToSec(double hour){ return hour*SecPerHour(); }
  static inline double DayToSec(double day){   return day *SecPerDay(); }
  static inline double WeekToSec(double week){ return week*SecPerWeek(); }
  static inline double YearToSec(double year){ return year*SecPerYear(); }
  static bool IsLeapYear(int year);
  static int* DaysInMonths(bool isLeapYear);
  static time_t LkTime(const tm_t& timeInfo);
  static time_t GmTime(const tm_t& timeInfo);
  static tm_t GetTM(int year, int month, int day, int hour, int min, int sec);
  static bool ParseDateTime(string dateTime, tm_t& timeInfo);
  static int ParseTzOffset(string tzoffset);
  static time_t ParseIsoString(string isoString);

protected:
  tm_t* localTimeInfo();
  tm_t* localTimeInfo() const;
  tm_t* gmTimeInfo();
  tm_t* gmTimeInfo() const;

private:
  time_t mUts;  //!< Unix Time Stamp: seconds since Jan 1, 1970 00:00:00 UTC
};

/** Difference in time between t1 and t2 = t1 - t2.
    If t2 describes a time point later than t1, the result is negative.
 */
inline double operator-(const TimeStamp& t1, const TimeStamp& t2){ return t1.difference(t2); }

} // end namespace Torpy

#endif // FAST_TIMESTAMP_HH
