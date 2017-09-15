#include <gcroot.h>
#include <string.h>
#include "util.h"
#include "FoxPro.NET.h"
#include "ManagedFoxProRecord.h"

using namespace System;
using namespace System::Collections::Generic;
using ManagedWrappers::ManagedFoxProRecord;

/*--------------------------------------
* class implementation
* -------------------------------------*/

ManagedFoxProRecord::ManagedFoxProRecord(CSNS::Record^ rec) : _record(rec) {}
ManagedFoxProRecord::~ManagedFoxProRecord()
{
    delete this;
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
    return util::ManagedStringToCharArray(_record->GetString(net_string));
}

void ManagedFoxProRecord::Set(char* field, char* new_value)
{
    String^ net_field = gcnew String(field);
    String^ net_new_value = gcnew String(new_value);
    _record->Set(net_field, net_new_value);
}

void ManagedFoxProRecord::GetBlob(unsigned char* dest)
{
    return;
}

void ManagedFoxProRecord::SetBlob(const char* blob)
{
    auto bList = gcnew List<char>();
    auto str = gcnew String("");
    for (int i = 0; i < strlen(blob); i++) {
        bList->Add(blob[i]);
        str += blob[i];
    }
}

void ManagedFoxProRecord::SetDeleted(bool del)
{
    _record->Deleted = del;
}

bool ManagedFoxProRecord::IsDeleted()
{
    return _record->Deleted;
}