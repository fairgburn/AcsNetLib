#include <gcroot.h>
#include <string.h>
#include "util.h"
#include "FoxPro.NET.h"
#include "ManagedRecordList.h"
#include "ManagedFoxProRecord.h"

using namespace System;
using namespace System::Collections::Generic;
using ManagedWrappers::ManagedRecordList;
using ManagedWrappers::ManagedFoxProRecord;

ManagedRecordList::~ManagedRecordList()
{
	delete this;
}

// factory method to create the list
ManagedRecordList::ManagedRecordList(CSNS::FoxProBuffer^) : _list(list) {}

// get a specific record
ManagedFoxProRecord* ManagedRecordList::GetAt(int index)
{
	CSNS::Record^ rec = gcnew CSNS::Record();
	return new ManagedFoxProRecord(rec);
	auto x = _list->Count;
}
IRecord* ManagedRecordList::operator[] (int index)
{

}

void Add(IRecord* record);
int Count();

