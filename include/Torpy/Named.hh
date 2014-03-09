/** \file      Named.hh
\brief     Header for Named class.
\author    Doug Hague
\date      22.06.2013
\copyright See License.txt
*/
#ifndef TP_NAMED_HH
#define TP_NAMED_HH

#include "AbsObject.hh" // abstract object

namespace Torpy {

/** \class Named
 \brief A named class.
 */
class Named : public AbsObject {
public:
    Named(const char* name = "", const char* title = "");
    Named(const Named& other, const char* newName = "");
    virtual AbsObject* clone(const char* newName = "") const;
    virtual Named& operator=(const Named& rhs);
    inline virtual ~Named() { }
    
    virtual bool isEmpty() const;
    virtual void clear();
    virtual bool isEqual(const AbsObject& other) const;
    
    inline bool hasName() const { return (mName != ""); }
    inline const char* name() const { return mName.c_str(); }
    inline void setName(const char* name){ mName = name; }
    inline bool hasTitle() const { return (mTitle != ""); }
    inline const char* title() const { return mTitle.c_str(); }
    inline void setTitle(const char* title){ mTitle = title; }
    void setNameTitle(const char* name, const char* title);
    
protected:
    Named(const char* classType,
          const char* name = "", const char* title = "");
    
private:
    //! Name
    string mName;
    //! Title
    string mTitle;
};

} // end namespace Torpy

#endif // end TP_NAMED_HH
