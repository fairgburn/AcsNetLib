/*---------------------------------------------------
    RecordIterator
    usage:
        
        CFoxProBuffer fp("C:\path\to\file.dbf");
        Iterator it = fp.Iterator();
        do {
            

----------------------------------------------------*/

#include "include/CRecordList.h"
#include "util.h"

// shortcut for getting a pointer to the actual .NET object with the data
#define _LIST NET_POINTER(List<String^>, NET_HANDLE(__NET_HEAP__List))

// C# namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace database::structs;

// header namespace
using namespace AcsNetLib::FoxPro;

RecordIterator::RecordIterator(CFoxProRecord* rec)
{
    _data = rec;
}




CRecordList::CRecordList(void* ptr)
{
    __NET_HEAP__List = ptr;
}


  
