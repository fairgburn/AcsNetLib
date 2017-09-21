#include <gcroot.h>

#include "FoxPro.NET.h"
#include "ManagedFoxProBuffer.h"
#include "ManagedFoxProRecord.h"

using namespace System;
using namespace AcsLib::FoxPro;
using namespace AcsNetLib::FoxPro;
using ManagedWrappers::ManagedFoxProBuffer;
using ManagedWrappers::ManagedFoxProRecord;

// native interface:
// create a buffer in native C++
CFoxProBuffer* AcsNetLib::FoxPro::CreateFoxProBuffer(char* dbfFile)
{
    return ManagedFoxProBuffer::CreateBuffer(dbfFile);
}


/*--------------------------------------
 * class implementation
 * -------------------------------------*/

// protected contructor/destructor 
// force creation by CreateBuffer() for memory safety
ManagedFoxProBuffer::ManagedFoxProBuffer(FoxProBuffer^ buf) : _buffer(buf)
{
	// allocate array of record pointers
	_records = new ManagedRecordPtr[_buffer->Records->Count];
	for (int i = 0; i < _buffer->Records->Count; i++)
	{
		_records[i] = new ManagedFoxProRecord(_buffer->Records[i]);
	}
}
ManagedFoxProBuffer::~ManagedFoxProBuffer()
{
	Console::WriteLine("buffer destructor");
	// clean the record wrappers
	if (_records != nullptr)
	{
		// deallocate the individual pointers
		for (int i = 0; i < _buffer->Records->Count; i++) {
			delete _records[i];
		}

		// deallocate pointer array
		delete[] _records;
	}

	delete this;
}

// use factory model to create instances
CFoxProBuffer* ManagedFoxProBuffer::CreateBuffer(char* dbfFile)
{
    auto net_buffer = gcnew FoxProBuffer(gcnew String(dbfFile));
    return new ManagedFoxProBuffer(net_buffer);
}

void ManagedFoxProBuffer::Open()
{
    _buffer->Open();
}

void ManagedFoxProBuffer::Close()
{
    _buffer->Close();
}

void ManagedFoxProBuffer::Save()
{
    _buffer->Save();
}

void ManagedFoxProBuffer::SaveAs(char* outputFile)
{
    _buffer->SaveAs(gcnew String(outputFile));
}

IRecord* ManagedFoxProBuffer::GetRecord(int index)
{
    // old way: create new record wrapper, let destructor handle deallocation when
	//   it goes out of scope in client code
	//
	// return new ManagedFoxProRecord(_buffer->GetRecord(index));
	//   - have to change so client can hold persistent pointer to a record

	// new way: return pointer to ManagedFoxProRecord that's managed internally by the wrapper
	return _records[index];
}

IRecord* ManagedFoxProBuffer::operator[] (int index)
{
	IRecord* rec = this->GetRecord(index);
	return rec;
}

void ManagedFoxProBuffer::AddRecord(IRecord* record)
{
    // cast the native record interface to managed type, get the C# record from it,
    //  then add the record to C#'s buffer
    auto mfpr = (ManagedFoxProRecord*)record;
    auto csrec = mfpr->GetCSRecord();
    _buffer->AddRecord(csrec);
}

void ManagedFoxProBuffer::RemoveRecord(int index)
{
    _buffer->Records->RemoveAt(index);
}

IRecord* ManagedFoxProBuffer::CreateNewRecord()
{
    Record^ new_record = _buffer->CreateNewRecord(' ');
           
    return new ManagedFoxProRecord(new_record);
}

int ManagedFoxProBuffer::NumFields()
{
    return _buffer->Fields->Count;
}

int ManagedFoxProBuffer::NumRecords()
{
    return _buffer->Records->Count;
}


