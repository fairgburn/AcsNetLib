/*----------------------------------------------
    CFoxProRecord.h
    [AcsCppLib.NET.dll]
    
    Data structure for holding a record from
    a FoxPro file

    Brandon Fairburn 9/6/2017
-----------------------------------------------*/

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
        class DECLSPECIFIER CFoxProRecord
        {
        public:
            // constructor with pointer to .NET Record instance
            CFoxProRecord(void* pointer);
            CFoxProRecord() {}
            ~CFoxProRecord();

            int Length();
            char* Get(char* field);
            void Set(char* field, char* new_value);

            // DO NOT use this; internal DLL use only
            void _set_ptr(void* ptr);

        private:
            // pointer to object in .NET heap
            void* __NET_HEAP__Record;
        };
    }
}
