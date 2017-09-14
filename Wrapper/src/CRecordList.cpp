/*---------------------------------------------------
    CRecordList class

	wrapper for the Records list in C# library
----------------------------------------------------*/

#include "FoxPro.NET.h"
#include "util.h"

// shortcut for getting a pointer to the actual .NET object with the data
#define _LIST NET_CAST(List<Record^>, NET_HANDLE(_ptr))

// C# namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;

// header namespace
using namespace AcsNetLib::FoxPro;

///////////////////////////////////////////////////////////
void println(String^ msg)
{
	System::Console::WriteLine(msg);
}
void println(char* msg) { println(gcnew String(msg)); }
//----------------------------------------------
void print(String^ msg)
{
	System::Console::Write(msg);
}
void print(char* msg) { print(gcnew String(msg)); }
///////////////////////////////////////////////////////////

CRecordList::CRecordList(void* ptr)
{
    _ptr = ptr;
}


CFoxProRecord CRecordList::GetAt(int index)
{
	List<Record^>^ list = _LIST;
	Record^ rec = list[index];
	void* recPtr = NET_ALLOC_GETPTR(rec);

	/*CFoxProRecord* r_new = new CFoxProRecord(recPtr);
	CFoxProRecord result = *r_new;
	delete r_new;*/

	CFoxProRecord result(recPtr);

	return result;
}


void CRecordList::Add(CFoxProRecord record)
{
	// get .NET pointers to list and record
	List<Record^>^ list = _LIST;
	Record^ rec = NET_CAST(Record, NET_HANDLE(record._get_ptr()));

	// add it
	list->Add(rec);
}


int CRecordList::Length()
{
	List<Record^>^ list = _LIST;
	return list->Count;
}

