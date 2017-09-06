/*---------------------------------------------------
    CFoxProRecord.cpp
    AcsCppLib.NET.dll

    definitions for FoxPro record data structure

    Brandon Fairburn 9/6/2017
-----------------------------------------------------*/

#include "CFoxProBuffer.h"
#include "util.h"

// shortcut for getting a pointer to the actual .NET object with the data
#define _RECORD NET_POINTER(Record, NET_HANDLE(__NET_HEAP__Record))

// C# namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace FoxPro_NET;
using namespace database::structs;

// header namespace
using namespace AcsNetLib::FoxPro;


/*-----------------------------*/
// constructor / desctructor 
/*-----------------------------*/

CFoxProRecord::CFoxProRecord(void* ptr)
{
    __NET_HEAP__Record = ptr;
}


CFoxProRecord::~CFoxProRecord()
{
    NET_HANDLE(__NET_HEAP__Record).Free();
}


/*-----------------------------*/
//  Public functions
/*-----------------------------*/

int CFoxProRecord::Length()
{
    Record^ rec = _RECORD;
    return rec->Length;
}


char* CFoxProRecord::Get(char* field)
{
    Record^ rec = _RECORD;
    String^ data = rec->GetString(gcnew String(field));

    return util::ManagedStringToCharArray(data);
}


void CFoxProRecord::Set(char* field, char* new_value)
{
    Record^ rec = _RECORD;
    String^ f = util::CharArrayToManagedString(field);
    String^ v = util::CharArrayToManagedString(new_value);

    rec->Set(f, v);
}