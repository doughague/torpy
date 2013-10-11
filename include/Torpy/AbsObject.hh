/** \file      AbsObject.hh 
    \brief     Header for AbsObject class.
    \author    Doug Hague
    \date      03.10.2013
    \copyright See License.txt
*/
#ifndef TP_ABSOBJECT_HH
#define TP_ABSOBJECT_HH

#include "Torpy/Common.hh"

namespace Torpy {

/** \class AbsObject
    \brief An abstract object.
*/
class AbsObject {
public:
  AbsObject(const char* classType = "AbsObject");
  AbsObject(const AbsObject& other, const char* /*newName = ""*/);
  virtual AbsObject* clone(const char* /*newName = ""*/) const = 0;
  virtual AbsObject& operator=(const AbsObject& rhs);
  inline virtual ~AbsObject() { }

  // class type
  const char* classType() const;
  bool isA(const char* classType) const;

  // general contents
  virtual bool isEmpty() const = 0;
  virtual void clear() = 0;

  // equality
  bool isSame(const AbsObject& other) const;
  bool isSameClass(const AbsObject& other) const;
  virtual bool isEqual(const AbsObject& other) const;
  bool operator==(const AbsObject& rhs) const;
  bool operator!=(const AbsObject& rhs) const;

  // Comparisons
  virtual bool isSortable() const;
  virtual int compare(const AbsObject& other) const;
  bool operator<(const AbsObject& other) const;
  bool operator<=(const AbsObject& other) const;
  bool operator>(const AbsObject& other) const;
  bool operator>=(const AbsObject& other) const;

protected:
  void setClassType(const char* classType);

private:
  //! Class Type (type-name of derived c++ class)
  string mClassType;
};

} // end namespace Torpy

#endif // end TP_ABSOBJECT_HH
