/*---------------------------------------------------
    CRecordList class

	wrapper for the Records list in C# library
----------------------------------------------------*/

#include "FoxPro.NET.h"
#include "util.h"

// shortcut for getting a pointer to the actual .NET object with the data
#define _LIST NET_POINTER(List<Record^>, NET_HANDLE(__NET_HEAP__List))

// C# namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

// header namespace
using namespace AcsNetLib::FoxPro;




CRecordList::CRecordList(void* ptr)
{
    __NET_HEAP__List = ptr;
}


CFoxProRecord CRecordList::GetAt(int index)
{
	List<Record^>^ list = _LIST;
	Record^ rec = list[index];
	void* recPtr = NET_ALLOC_GETPTR(rec);

	CFoxProRecord r;
	r._set_ptr(recPtr);

	return r;
}


void CRecordList::Add(CFoxProRecord record)
{
	// get .NET pointers to list and record
	List<Record^>^ list = _LIST;
	Record^ rec = NET_POINTER(Record, NET_HANDLE(record._get_ptr()));

	// add it
	list->Add(rec);
}