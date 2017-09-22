#include <gcroot.h>
#include <string.h>
#include "util.h"
#include "FoxPro.NET.h"
#include "ManagedFoxProRecord.h"

using namespace System;
using namespace System::Collections::Generic;
using ManagedWrappers::ManagedFoxProRecord;

/*------------------------------------------------------
* class ManagedFoxProRecord

Protected
----------------
	gcroot<CSNS::Record^> _record;
	unsigned char* _blob;

Public
------------------
	ManagedFoxProRecord(CSNS::Record^);
	~ManagedFoxProRecord();

	gcroot<CSNS::Record^> GetCSRecord();

	int Length();

	char* Get(int index);
	char* Get(char* field);
	void Set(char* field, char* new_value);

	void GetBlob(unsigned char* dest);
	unsigned char* GetCompleteRecord();
	void SetCompleteRecord(unsigned char* blob);

	void SetDeleted(bool);
	bool IsDeleted();
------------------------------------------------------*/

//----------------------------------------------------------------------------------------------------
// constructor: set _blob to nullptr until it is told to store data
// destructor: deallocate _blob, unless it is nullptr
//
ManagedFoxProRecord::ManagedFoxProRecord(CSNS::Record^ rec) : _record(rec) { _blob = nullptr; }

ManagedFoxProRecord::~ManagedFoxProRecord()
{
	if (_blob != nullptr) delete[] _blob;
    delete this;
}
//
// note on terminology: "blob" is an abbreviation for "Binary Large OBject" -- in C#,
//   the "blob" is stored as an array of all the binary data from the record
//----------------------------------------------------------------------------------------------------

gcroot<CSNS::Record^> ManagedFoxProRecord::GetCSRecord()
{
    return _record;
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

// replaced by GetCompleteRecord


unsigned char* ManagedFoxProRecord::GetCompleteRecord()
{
	// deallocate _blob if it has already been created
    if (_blob != nullptr)
		delete[] _blob;

	// get the complete record data from C#
	// allocate _blob to the right size for conversion from C# byte array to native C++ array
    auto blob = _record->GetCompleteRecord();
    _blob = new unsigned char[blob->Length + 1];

    // add deleted flag to the complete record data
    _blob[0] = (_record->Deleted) ? '*' : ' ';

    for (int i = 1; i < blob->Length + 1; i++)
    {
        _blob[i] = blob[i-1];
    }

    return _blob;
}

void ManagedFoxProRecord::SetCompleteRecord(unsigned char* blob)
{
    // read deleted flag from input
    this->SetDeleted((blob[0] == '*') ? true : false);

    // build up a list of all the bytes from input
    auto bList = gcnew List<unsigned char>();
    for (int i = 1; i < _record->Length + 1; i++) {
        bList->Add(blob[i]);
    }

    _record->SetCompleteRecord(bList->ToArray());
}

void ManagedFoxProRecord::SetDeleted(bool del)
{
    _record->Deleted = del;
}

bool ManagedFoxProRecord::IsDeleted()
{
    return _record->Deleted;
}