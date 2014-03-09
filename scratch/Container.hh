/** \file      Container.hh
\brief     Header for Container vector.
\author    Doug Hague, Jason Torpy, ciphermagi at http://www.cplusplus.com/forum/general/53717/
\date      06.03.2014
\copyright See License.txt
*/
#ifndef TP_CONTAINER_HH
#define TP_CONTAINER_HH

#include "AbsObject.hh" // abstract object

namespace Torpy {

/** \class Container
 \brief A container vector; for Warrior but should be usable for warrior, stable, managers, weapons.
 */
class Container : public AbsObject {
    vector<AbsObject *> vecs; // vector of pointers to class objects of type Warrior
    vector<AbsObject *>::iterator it; // Iterator to point at pointers to class objects of type Warrior
    void newVec(); // Functions
    void selVec();
    void editVec();
    
public:
    int cmenu();
};

} // end namespace Torpy

#endif // end TP_CONTAINER_HH
