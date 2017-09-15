#include <gcroot.h>
#include <stdio.h>
#include "util.h"
#include "FoxPro.NET.h"
#include "ManagedFoxProRecord.h"

// shorthand for getting this record from buffer
#define _RECORD _buffer->Records[_index]

using namespace System;
using ManagedWrappers::ManagedFoxProRecord;

/*--------------------------------------
* class implementation
* -------------------------------------*/

ManagedFoxProRecord::ManagedFoxProRecord(CSNS::FoxProBuffer^ buf, int index) : _buffer(buf)
{
    _index = index;
}
ManagedFoxProRecord::~ManagedFoxProRecord()
{
    delete this;
}

// use factory model to create new records
IRecord* ManagedFoxProRecord::CreateRecord(CSNS::FoxProBuffer^ buf, int index)
{
    return new ManagedFoxProRecord(buf, index);
}
void ManagedFoxProRecord::SetHandle(CSNS::Record^ rec) : _newRecord(rec) {}
int ManagedFoxProRecord::Length()
{
    return _RECORD->Length;
}
char* ManagedFoxProRecord::Get(int index)
{
    return util::ManagedStringToCharArray(_RECORD->GetString(index));
}
char* ManagedFoxProRecord::Get(char* field)
{
    String^ net_string = gcnew String(field);
    printf("got this: ");
    System::Console::WriteLine(_RECORD->GetString(net_string));
    return util::ManagedStringToCharArray(_RECORD->GetString(net_string));
}
void ManagedFoxProRecord::Set(char* field, char* new_value)
{
    String^ net_field = gcnew String(field);
    String^ net_new_value = gcnew String(new_value);
    _RECORD->Set(net_field, net_new_value);
}
void ManagedFoxProRecord::SetDeleted(bool del)
{
    _RECORD->Deleted = del;
}
bool ManagedFoxProRecord::IsDeleted()
{
    return _RECORD->Deleted;
}