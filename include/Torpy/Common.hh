/** \file      Common.hh 
    \brief     Common includes and usings header.
    \author    Doug Hague
    \date      23.07.2013
    \copyright See License.txt
*/
#ifndef TP_COMMON_HH
#define TP_COMMON_HH

// C General Utilities Library; atoi
#include <cstdlib>

// C string tools; strlen
#include <cstring>

// STD file input/output stream objects
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ios_base;

// STD input/output stream objects
#include <iostream>
using std::cout;
using std::cerr;
using std::clog;
using std::endl;
using std::istream;
using std::ostream;

// STD input/output manipulators
#include <iomanip>
using std::setw;

// STD string input/output stream objects
#include <sstream>
using std::stringstream;

// STD string object
#include <string>
using std::string;

// STD utilities
#include <utility>
using std::pair;

// STD vector object
#include <vector>
using std::vector;

// STD map object
#include <map>
using std::map;

// Includes for this library
// #include "yaml-cpp/yaml.h"

#endif // end TP_COMMON_HH
