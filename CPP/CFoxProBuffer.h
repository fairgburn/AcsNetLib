/*------------------------------------------------------------------
    CFoxProBuffer.h
    [AcsCppLib.NET.dll]

    provide means for reading/writing a FoxPro file

    Brandon Fairburn 9/6/2017
------------------------------------------------------------------*/

#pragma once

// building DLL or using it?
#ifdef INSIDE_MANAGED_CODE
    #define DECLSPECIFIER __declspec(dllexport)
    #define EXPIMP_TEMPLATE
#else
    #define DECLSPECIFIER __declspec(dllimport)
    #define EXPIMP_TEMPLATE extern
#endif

#include "CFoxProField.h"
#include "CFoxProRecord.h"

namespace AcsNetLib
{
    namespace FoxPro
    {
        

        /*-----------------*/
        // main class
        /*-----------------*/

        class DECLSPECIFIER CFoxProBuffer
        {
        // constructor / destructor
        public:
            CFoxProBuffer(char* inputFile);
            ~CFoxProBuffer();

        // interface to C# class
        public:
            void Open();
            void Save();
            //void Update(CFoxProRecord rec, char* field, char* val);

            CFoxProField* GetFields();
            CFoxProRecord* GetRecords();


        // internal
        private:
            // address of C# class in .NET heap
            void* __NET_HEAP__FoxProBuffer;


            CFoxProField* _fields;
            CFoxProRecord* _records;
        };



    }
}