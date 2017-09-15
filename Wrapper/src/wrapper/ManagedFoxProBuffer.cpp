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
// force creation by CreateBuffer()
ManagedFoxProBuffer::ManagedFoxProBuffer(FoxProBuffer^ buf) : _buffer(buf) {}
ManagedFoxProBuffer::~ManagedFoxProBuffer() { delete this; }

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
    return ManagedFoxProRecord::CreateRecord(_buffer->RecordFactory(' '));
}

void ManagedFoxProBuffer::AddRecord(CFoxProRecord* record)
{
    _buffer->AddRecord(  ((ManagedFoxProRecord*)record)->GetHandle()  );
}

void ManagedFoxProBuffer::RemoveRecord(int index)
{
    _buffer->Records->RemoveAt(index);
}

CFoxProRecord* ManagedFoxProBuffer::RecordFactory()
{
    Record^ new_record = _buffer->RecordFactory(' ');
           
    return ManagedFoxProRecord::CreateRecord(new_record);
}

int ManagedFoxProBuffer::NumFields()
{
    return _buffer->Fields->Count;
}

int ManagedFoxProBuffer::NumRecords()
{
    return _buffer->Records->Count;
}


