#include <gcroot.h>
#include <vector>

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
IBufferPtr AcsNetLib::FoxPro::CreateFoxProBuffer(char* dbfFile)
{
    return ManagedFoxProBuffer::CreateBuffer(dbfFile);
}


/*--------------------------------------------------------
 * class ManagedFoxProBuffer

Protected
----------
	ManagedFoxProBuffer(CSNS::FoxProBuffer^ buf);
	~ManagedFoxProBuffer();

	gcroot<CSNS::FoxProBuffer^> _buffer;
	ManagedRecordPtr* _records;
	int _records_size;

Private
---------------
	void GrowRecordPtrArray();
	void ShrinkRecordPtrArray();
	void UpdateRecordPtrArray();

Public
-------------
	static IBuffer* CreateBuffer(char* dbfFile);

	void Open();
	void Close();
	void Save();
	void SaveAs(char* outputFile);

	IRecord* GetRecord(int index);
	IRecord* operator[] (int index);

	void AddRecord(IRecord* record);
	void RemoveRecord(int index);
	IRecord* CreateNewRecord();

	int NumFields();
	int NumRecords();
-------------------------------------------------------------*/

 //------------------------------------------------------------------------------------------------
// protected contructor/destructor 
// force creation by CreateBuffer() since the constructor takes a non-native type as a parameter
//
ManagedFoxProBuffer::ManagedFoxProBuffer(FoxProBuffer^ buf) : _buffer(buf)
{
	// store a wrapper for each C# record
	for each (auto rec in _buffer->Records) {
		_vectRecords.push_back(new ManagedFoxProRecord(rec));
	}

	// determine size of _records; always a power of 2
	// start at 2^0 (1), increase exponent (left shift) until all C# records will fit
	/*int num_records = NumRecords();

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

		
	}*/
}

ManagedFoxProBuffer::~ManagedFoxProBuffer()
{
	// deallocate all record wrappers
	while (!_vectRecords.empty()) {
		IRecordPtr rp = _vectRecords.back();
		_vectRecords.pop_back();
		delete rp;
	}

	// clean the record wrappers
	/*if (_records != nullptr)
	{
		// deallocate the individual pointers
		for (int i = 0; i < _records_size; i++) {
			ManagedRecordPtr rec = _records[i];
			if (rec != nullptr)
				delete rec;
		}

		// deallocate array
		delete[] _records;
	}*/

	// buffer is always dynamically allocated, so delete it too
	delete this;
}
//-------------------------------------------------------------------------------


/*--------------------
* private methods
*--------------------*/

// grow record pointer array (powers of 2)
/*void ManagedFoxProBuffer::GrowRecordPtrArray()
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
// can be dangerous - calling this when less than half the array is nullptr would cause a memory leak
void ManagedFoxProBuffer::ShrinkRecordPtrArray()
{
	if (_records == nullptr) return;

	// opposite of above algorithm
	int new_size = _records_size >> 1;
	auto new_array = new ManagedRecordPtr[new_size];



}*/


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

IRecordPtr ManagedFoxProBuffer::GetRecord(int index)
{
	return _vectRecords[index];

	// old way: create new record wrapper, let destructor handle deallocation when
	//   it goes out of scope in client code
	//
	// return new ManagedFoxProRecord(_buffer->GetRecord(index));
	//   - have to change so client can hold/change a persistent pointer to a record
	//
	// new way: wrapper performs and tracks all memory allocations internally
	
	//return _records[index];

}

IRecordPtr ManagedFoxProBuffer::operator[] (int index)
{
	return this->GetRecord(index);
	//IRecord* rec = this->GetRecord(index);
	//return rec;
}

void ManagedFoxProBuffer::AddRecord(IRecordPtr record)
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

IRecordPtr ManagedFoxProBuffer::CreateNewRecord()
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