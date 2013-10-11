/** \file      Exception.hh 
    \brief     Header for exception handler
    \author    Doug Hague
    \date      24.07.2013
    \copyright See License.txt
*/
#ifndef TP_EXCEPTION_HH
#define TP_EXCEPTION_HH

#include "Torpy/Common.hh"      // commons for Torpy
#include <exception>            // std::exception
#include <stdexcept>            // std::out_of_range

// common exceptions
using std::out_of_range;

namespace Torpy {

/** \class Exception
    \brief Exception handling class.
*/
class Exception : public std::exception {

public:
  /** Constructor. */
  inline Exception(const string& message)
  : exception(),
    mMessage(message) 
  {}

  /** Copy constructor. */
  inline Exception(const Exception& other)
  : exception(other),
    mMessage(other.mMessage)
  {}

  /** Assignemnt operator. */
  inline Exception& operator=(const Exception& rhs)
  {
    exception::operator=(rhs);
    mMessage = rhs.mMessage;
    return *this;
  }

  /** Destructor. */
  inline virtual ~Exception() throw() { }

  /** The message associated with the exception. */
  inline const char* what() const throw() 
  { 
    return mMessage.c_str(); 
  }

private:
  string mMessage;
};

} // end namespace Torpy

#endif // TP_EXCEPTION_HH
