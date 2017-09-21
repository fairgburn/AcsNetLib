/*-----------------------------------------------------------
    util.h

    Utility functions for internal AcsNetLib use (header)
     May expand to a separate mini-library if this gets
     too big.

    Brandon Fairburn 9/6/2017
-------------------------------------------------------------*/

#pragma once


// don't need to use this outside the library itself
#ifdef INSIDE_MANAGED_CODE

// shortcuts to access .NET objects
#define NET_HANDLE(pointer) GCHandle::FromIntPtr(IntPtr(pointer))
#define NET_CAST(type, hnd) safe_cast<type^>(hnd.Target);
#define NET_ALLOC_GETPTR(objptr) GCHandle::ToIntPtr(GCHandle::Alloc(objptr)).ToPointer()

// C# namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;


namespace util
{
    
    // convert a .NET managed string to native char*
    char* ManagedStringToCharArray(String^ s);

    // convert char* to .NET managed string
    String^ CharArrayToManagedString(char*);

	// fill an array with a default value
	void FillArray(void* arr, void* value, int arr_size);


}



#endif