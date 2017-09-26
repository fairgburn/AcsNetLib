#include <gcroot.h>
#include <vector>

#include "FoxPro.NET.h"
#include "ManagedFoxProBuffer.h"
#include "ManagedFoxProRecord.h"

#using "AcsLib.NET.dll"

using namespace System;
using namespace AcsNetLib::FoxPro;
using namespace ManagedWrappers;

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
ManagedFoxProBuffer::ManagedFoxProBuffer(CSNS::FoxProBuffer^ buf) : _buffer(buf)
{
	// store a wrapper for each C# record
	for each (CSNS::Record^ rec in _buffer->Records) {
		_vectRecords.push_back(new ManagedFoxProRecord(rec));

	}
}

ManagedFoxProBuffer::~ManagedFoxProBuffer()
{
	// deallocate all record wrappers
	while (!_vectRecords.empty()) {
		IRecordPtr rp = _vectRecords.back();
		_vectRecords.pop_back();
		delete rp;
	}

	// buffer is always dynamically allocated, so delete it too
	delete this;
}
//-------------------------------------------------------------------------------



/*------------------------------------------------------------------------------
* public methods (implementation of CFoxProBuffer interface from FoxPro.NET.h)
*------------------------------------------------------------------------------*/

// use factory model to create instances
CFoxProBuffer* ManagedFoxProBuffer::CreateBuffer(char* dbfFile)
{
    auto net_buffer = gcnew CSNS::FoxProBuffer(gcnew String(dbfFile));
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
}

IRecordPtr ManagedFoxProBuffer::operator[] (int index)
{
	return this->GetRecord(index);
}

void ManagedFoxProBuffer::AddRecord(IRecordPtr record)
{
	// cast the native interface to ManagedRecordPtr
	// safe_cast throws an exception if the cast fails
	auto rec_wrapper = (ManagedRecordPtr)record;

	// get C# record from the wrapper, add it to C# buffer
	_buffer->AddRecord(rec_wrapper->GetCSRecord());

	// also update the wrapper records 
	_vectRecords.push_back(rec_wrapper);
}

void ManagedFoxProBuffer::RemoveRecord(int index)
{
	// removing record from C++ wrapper container (std::vector)
	std::vector<ManagedRecordPtr>::iterator v_iter = _vectRecords.begin();
	std::advance(v_iter, index);
	_vectRecords.erase(v_iter);

	// removing from C# list
    _buffer->Records->RemoveAt(index);
}

IRecordPtr ManagedFoxProBuffer::CreateNewRecord()
{
    CSNS::Record^ new_record = _buffer->CreateNewRecord(' ');
           
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