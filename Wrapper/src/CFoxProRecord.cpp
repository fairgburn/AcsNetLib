/*---------------------------------------------------
    CFoxProRecord.cpp
    AcsCppLib.NET.dll

    definitions for FoxPro record data structure

    Brandon Fairburn 9/6/2017
-----------------------------------------------------*/

#include "FoxPro.NET.h"
#include "util.h"

// shortcut for getting a pointer to the actual .NET object with the data
#define _RECORD NET_CAST(Record, NET_HANDLE(_ptr))

// C# namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

// header namespace
using namespace AcsNetLib::FoxPro;
using namespace  AcsNetLib::Database;


/*-----------------------------*/
// constructor / destructor 
/*-----------------------------*/

CFoxProRecord::CFoxProRecord(void* ptr)
{
    _ptr = ptr;
}


CFoxProRecord::~CFoxProRecord()
{
    NET_HANDLE(_ptr).Free();
}


/*-----------------------------*/
//  Public functions
/*-----------------------------*/

int CFoxProRecord::Length()
{
    Record^ rec = _RECORD;
    return rec->Length;
    
}


char* CFoxProRecord::GetString(int index)
{
    Record^ rec = _RECORD;
    String^ data = rec->GetString(index);

    return util::ManagedStringToCharArray(data);
}


char* CFoxProRecord::GetString(char* field)
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


CFoxProRecord CFoxProRecord::Copy()
{
	Record^ original = _RECORD;
	Record^ clone = original->Copy();
	void* ptr = GCHandle::ToIntPtr(GCHandle::Alloc(clone)).ToPointer();

	CFoxProRecord r;
	r._set_ptr(ptr);

	return r;
}


void CFoxProRecord::SetDeleted(bool tf)
{
    Record^ rec = _RECORD;
    rec->Deleted = tf;
}


bool CFoxProRecord::IsDeleted()
{
    Record^ rec = _RECORD;
    return rec->Deleted;
}

#ifdef INSIDE_MANAGED_CODE
void CFoxProRecord::_set_ptr(void* ptr)
{
    _ptr = ptr;
}

void* CFoxProRecord::_get_ptr()
{
	return _ptr;
}
#endif
