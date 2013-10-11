/** \file      Parameter.hh 
    \brief     Header for Parameter
    \author    Doug Hague
    \date      03.10.2013
    \copyright See License.txt
*/
#ifndef TP_PARAMETER_HH
#define TP_PARAMETER_HH

#include "Torpy/Named.hh"  // mother class

namespace Torpy {

/** \class Parameter 
    \brief For holding parameter information.
*/
class Parameter : public Named { 
public:
  Parameter(const char* name = "", const char* title = "",
	    double value = 0., double error = 0.,
	    double min = 0., double max = 0.);
  Parameter(const Parameter& other, const char* newName = "");
  virtual AbsObject* clone(const char* newName = "") const;
  virtual Parameter& operator=(const Parameter& rhs);
  inline virtual ~Parameter() { }

  // abstract
  bool isEmpty() const;
  void clear();
  bool isEqual(const AbsObject& other) const;

  // set / get
  inline void setValue(double value){ mValue = value; }
  inline double value() const { return mValue; }
  inline void setError(double error){ mError = error; }
  inline double error() const { return mError; }
  inline void setMin(double min){ mMin = min; }
  inline double min() const { return mMin; }
  inline void setMax(double max){ mMax = max; }
  inline double max() const { return mMax; }
  void set(double value, double error, double min, double max);
  void setRange(double min, double max);
  void range(double& min, double& max);

  // utilities
  inline bool isFree() const { return mMin != mMax; }
  inline bool isFixed() const { return !isFree(); }

private:
  double mValue;  //!< value
  double mError;  //!< error
  double mMin;    //!< minimum range
  double mMax;    //!< maximum range
};

} // end namespace Torpy

#endif // TP_PARAMETER_HH
