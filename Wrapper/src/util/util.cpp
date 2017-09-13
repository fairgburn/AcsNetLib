/*---------------------------------------------------------------
    util.cpp
    
    Utility functions for internal AcsNetLib use (definitions)

    Brandon Fairburn 9/6/2017
-----------------------------------------------------------------*/
#ifdef INSIDE_MANAGED_CODE

#include "util.h"

//--- convert a .NET managed string to native char* ---//
char* util::ManagedStringToCharArray(String^ s)
{
    void* ptr = Marshal::StringToHGlobalAnsi(s).ToPointer();
    return static_cast<char*>(ptr);
}


//--- convert char* to .NET managed string ---//
String^ util::CharArrayToManagedString(char* charry)
{
    return gcnew String(charry);
}



#endif