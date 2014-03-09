/** \file      src/lib/Container.cxx
\brief     Source for Container vector of classes.
\author    Doug Hague, Jason Torpy, ciphermagi at http://www.cplusplus.com/forum/general/53717/
\date      06.03.2014
\copyright See License.txt
*/
#include "Torpy/Container.hh"       // this class

namespace Torpy {

    static const string kPrefix = "[BloBB]";
    #define tout cout << kPrefix.c_str() << ">  "

    // default constructors, desctructor, etc not included in example
    
    void Container::newVec(){ // creates new warrior from user input
        
        int sel;
        tout << "Select new entry type (1=Warrior):";
        cin >> sel;
        
        switch(sel){
            case 1: // for Warrior
                Named * pnam; // Define a pointer to the Named class.
                pnam = new VNamed; // create a new child class of type VNamed with a pointer to its parent class Named
                VNamed Named;
                warp->print();
                wars.push_back(warp); // store the pointer in the vector.
                // add 2=manager, 3=stable, 4=weapon
            default:
                tout << "Invalid choice. Enter 1." << endl;
                newVec();
   
        }
        
    
} // end namespace Torpy
