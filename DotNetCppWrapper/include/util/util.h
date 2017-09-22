#pragma once
/*-----------------------------------------------------------
    util.h

    Utilities for internal AcsNetLib use (header)
     May expand to a separate mini-library if this gets
     too big.

    Brandon Fairburn 9/6/2017
-------------------------------------------------------------*/




// don't need to use this outside the library itself
#ifdef INSIDE_MANAGED_CODE

// macro - delete a pointer and set it to nullptr
#define null_delete(ptr) delete ptr; ptr = nullptr

// namespaces for common useful C# tools
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;


namespace util
{
    
    // convert a .NET managed string to native char*
    char* ManagedStringToCharArray(String^ s);

}



#endif