#include <gcroot.h>
#include <stdio.h>
#include "util.h"
#include "FoxPro.NET.h"
#include "ManagedFoxProRecord.h"

using namespace System;
using ManagedWrappers::ManagedFoxProRecord;

/*--------------------------------------
* class implementation
* -------------------------------------*/

ManagedFoxProRecord::ManagedFoxProRecord(CSNS::Record^ record) : _record(record) {}
ManagedFoxProRecord::~ManagedFoxProRecord()
{
    delete this;
}

// handle to C# record
gcroot<CSNS::Record^> _record;

// use factory model to create new records
IRecord* ManagedFoxProRecord::CreateRecord(CSNS::Record^ record)
{
    return new ManagedFoxProRecord(record);
}

int ManagedFoxProRecord::Length()
{
    return _record->Length;
}
char* ManagedFoxProRecord::Get(int index)
{
    return util::ManagedStringToCharArray(_record->GetString(index));
}
char* ManagedFoxProRecord::Get(char* field)
{
    String^ net_string = gcnew String(field);
    printf("got this: ");
    System::Console::WriteLine(_record->GetString(net_string));
    return util::ManagedStringToCharArray(_record->GetString(net_string));
}
void ManagedFoxProRecord::Set(char* field, char* new_value)
{
    String^ net_field = gcnew String(field);
    String^ net_new_value = gcnew String(new_value);
    _record->Set(net_field, net_new_value);
}
IRecord* ManagedFoxProRecord::Copy()
{
    return new ManagedFoxProRecord(_record->Copy());
}
void ManagedFoxProRecord::SetDeleted(bool del)
{
    _record->Deleted = del;
}
bool ManagedFoxProRecord::IsDeleted()
{
    return _record->Deleted;
}
gcroot<CSNS::Record^> ManagedFoxProRecord::GetHandle()
{
    return _record;
}