/** \file      Disability.hh 
    \brief     Header for Disability
    \author    Jason Torpy, Doug Hague
    \date      03.10.2013
    \copyright See License.txt
*/
#ifndef TP_DISABILITY_HH
#define TP_DISABILITY_HH

#include "Torpy/Parameters.hh"  // mother class

namespace Torpy {

/** \class Disability
    \brief For holding warrior attributes.
*/
class Disability : public Parameters { 
public:
  Disability();
  Disability(const Disability& other, const char* /*newName*/);
  virtual AbsObject* clone(const char* /*newName*/) const;
  virtual Disability& operator=(const Disability& rhs);
  inline virtual ~Disability() { }
};

} // end namespace Torpy

#endif // TP_DISABILITY_HH
