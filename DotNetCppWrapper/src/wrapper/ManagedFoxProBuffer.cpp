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

 //-------------------------------------------------------------------------------
// protected contructor/destructor 
// force creation by CreateBuffer() for memory safety
//
ManagedFoxProBuffer::ManagedFoxProBuffer(FoxProBuffer^ buf) : _buffer(buf)
{
	// determine size of _records; always a power of 2
	// start at 2^0 (1), increase exponent (left shift) until all C# records will fit
	int num_records = NumRecords();

	_records_size = 1;
	while (_records_size <= num_records)
		_records_size <<= 1;

	// initialize array of record wrappers
	_records = new ManagedRecordPtr[_records_size];
	for (int i = 0; i < _records_size; i++)
	{
		// create a new wrapper for each existing record in C#
		// initialize extra elements to nullptr
		//   - _records_size is guaranteed to be bigger than value we get from NumRecords(),
		//     so there will definitely be extra elements
		_records[i] = (i < num_records) ? new ManagedFoxProRecord(_buffer->Records[i]) : nullptr;
	}
}

ManagedFoxProBuffer::~ManagedFoxProBuffer()
{
	// clean the record wrappers
	if (_records != nullptr)
	{
		// deallocate the individual pointers
		for (int i = 0; i < _records_size; i++) {
			ManagedRecordPtr rec = _records[i];
			if (rec != nullptr)
				delete rec;
		}

		// deallocate pointer array
		delete[] _records;
	}

	// buffer is always dynamically allocated, so delete it too
	delete this;
}
//-------------------------------------------------------------------------------


/*--------------------
* private methods
*--------------------*/

// grow record pointer array (powers of 2)
void ManagedFoxProBuffer::GrowRecordPtrArray()
{
	if (_records == nullptr) return;

	// double array size and allocate memory for larger array
	int new_size = _records_size << 1;
	ManagedRecordPtr* new_array = new ManagedRecordPtr[new_size];

	// store existing pointers, set extra elements to nullptr
	for (int i = 0; i < new_size; i++) {
		new_array[i] = (i < _records_size) ? _records[i] : nullptr;
	}

	// move _records pointer to the new array, update _records_size
	delete[] _records;
	_records = new_array;
	_records_size = new_size;
}

// shrink record pointer array (powers of 2)
void ManagedFoxProBuffer::ShrinkRecordPtrArray()
{
	if (_records == nullptr) return;

	// same algorithm as above, but with opposite goal
	int new_size = _records_size >> 1;

}


/*------------------------------------------------------------------------------
* public methods (implementation of CFoxProBuffer interface from FoxPro.NET.h)
*------------------------------------------------------------------------------*/

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

	// new way: return pointer to ManagedFoxProRecord that is managed internally by the wrapper
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