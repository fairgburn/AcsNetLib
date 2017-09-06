/*-------------------------------------------
    CFoxProField.h
    [AcsCppLib.NET.dll]

    data structure for field information
    from a FoxPro file

    Brandon Fairburn 9/6/2017
--------------------------------------------*/

#pragma once

// creating DLL or using it?
#ifdef INSIDE_MANAGED_CODE
    #define DECLSPECIFIER __declspec(dllexport)
    #define EXPIMP_TEMPLATE
#else
    #define DECLSPECIFIER __declspec(dllimport)
    #define EXPIMP_TEMPLATE extern
#endif

namespace AcsNetLib
{
    namespace FoxPro
    {
        class DECLSPECIFIER CFoxProField
        {
        public:
            char* Name;
            char Type;
            int Offset, Length;

            CFoxProField(char* name, char type, int offset, int length);
            ~CFoxProField();
        };
    }
}