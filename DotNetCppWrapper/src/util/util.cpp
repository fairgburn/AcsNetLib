/*---------------------------------------------------------------
    util.cpp
    
    Utility functions for internal AcsNetLib use (definitions)

    Brandon Fairburn 9/6/2017
-----------------------------------------------------------------*/

#include "util.h"

//--- convert a .NET managed string to native char* ---//
char* util::ManagedStringToCharArray(String^ s)
{
    void* ptr = Marshal::StringToHGlobalAnsi(s).ToPointer();
    return static_cast<char*>(ptr);
}
