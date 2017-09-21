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
	_records = new ManagedFoxProRecord*[_buffer->Records->Count];
	for (int i = 0; i < _buffer->Records->Count; i++)
	{
		_records[i] = new ManagedFoxProRecord(_buffer->Records[i]);
	}
}
ManagedFoxProBuffer::~ManagedFoxProBuffer()
{
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
    String^ net_string = gcnew String(outputFile);
    _buffer->SaveAs(net_string);
}

IRecord* ManagedFoxProBuffer::GetRecord(int index)
{
    // return ManagedFoxProRecord::CreateRecord(_buffer, index);
    return new ManagedFoxProRecord(_buffer->GetRecord(index));
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


