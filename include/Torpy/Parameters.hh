/** \file      Parameters.hh 
    \brief     Header for Parameters class
    \author    Doug Hague
    \date      03.10.2013
    \copyright See License.txt
*/
#ifndef TP_PARAMETERS_HH
#define TP_PARAMETERS_HH

#include "Torpy/Parameter.hh"

namespace Torpy {

/** \typedef std::map<string,Parameter> Parameters_t 
    \brief A std::map of Parameter's. 
*/
typedef map<string,Parameter> Parameters_t;

/** \typedef Parameters_t::iterator parIter 
    \brief An iterator over a std::vector of Parameter's. 
*/
typedef Parameters_t::iterator parIter;

/** \typedef Parameters_t::iterator parCIter 
    \brief A const iterator over a std::vector of Parameter's. 
*/
typedef Parameters_t::const_iterator parCIter;

/** \class Parameters
    \brief A collection (std::map) of Parameter's.
*/
class Parameters : public AbsObject {
public:
  Parameters();
  Parameters(const Parameters& other, const char* newName = "");
  virtual AbsObject* clone(const char* newName = "") const;
  virtual Parameters& operator=(const Parameters& rhs);
  inline virtual ~Parameters() { }

  // abstract
  bool isEmpty() const;
  void clear();
  bool isEqual(const AbsObject& other) const;

  //! Number of parameters in collection.
  inline size_t size() const { return mPars.size(); }

  // set / get
  bool add(const Parameter& parameter);
  bool erase(string parName);
  bool set(const Parameter& parameter);
  const Parameter& parameter(string parName) const;
  const Parameter& operator[](string parName) const;
  Parameter& parameter(string parName);

  // iterators
  inline parIter begin(){ return mPars.begin(); }
  inline parIter end(){ return mPars.end(); }
  inline const parCIter begin() const { return mPars.begin(); }
  inline const parCIter end() const { return mPars.end(); }

  // search
  bool contains(string parName) const;
  bool contains(const Parameter& parameter) const;

protected:
  Parameter& operator[](string parName);

private:
  //! Map of parameters
  Parameters_t mPars;
};

} // end namespace Torpy

#endif // TP_PARAMETERS_HH
