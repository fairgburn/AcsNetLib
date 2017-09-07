/*-----------------------------------------------------
    CFoxProBuffer.cpp
    [AcsCppLib.NET.dll]

    definitions for the FoxPro interface

    Brandon Fairburn 9/6/2017
-------------------------------------------------------*/

#include "FoxPro.NET.h"
#include "util.h"

// shortcut for getting pointer to .NET FoxProBuffer
#define _FPBUFFER NET_POINTER(FoxProBuffer, NET_HANDLE(__NET_HEAP__FoxProBuffer))

// C# namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace FoxPro_NET;
using namespace database::structs;

// header namespace
using namespace AcsNetLib::FoxPro;


/*-----------------------------*/
// constructor / desctructor 
/*-----------------------------*/

CFoxProBuffer::CFoxProBuffer(char* inputFile)
{
    String^ _net_file = gcnew String(inputFile);
    FoxProBuffer^ fp = gcnew FoxProBuffer(_net_file);


    // pin the .NET object
    __NET_HEAP__FoxProBuffer = GCHandle::ToIntPtr(GCHandle::Alloc(fp)).ToPointer();
}


CFoxProBuffer::~CFoxProBuffer()
{
    NET_HANDLE(__NET_HEAP__FoxProBuffer).Free();

    delete[] _fields;
    delete[] _records;
}


/*-----------------------------*/
//  Public functions
/*-----------------------------*/

void CFoxProBuffer::Open()
{
    // call Open() on the C# instance
    FoxProBuffer^ fp = _FPBUFFER;
    fp->Open();

    // initiate the fields list & get fields from C# instance
    _fields = new CFoxProField[fp->Fields->Count];
    int index = 0;
    for each (Field^ field in fp->Fields)
    {
        // convert .NET fields to native CFoxProField and store them
        _fields[index].Name = util::ManagedStringToCharArray(field->Name);
        _fields[index].Type = static_cast<char> (field->Type);
        _fields[index].Length = field->Length;
        _fields[index].Offset = field->Offset;
        index++;

    }

    // initiate records list & get records from C# instance
    _records = new CFoxProRecord[fp->Records->Count];
    index = 0;
    for each (Record^ rec in fp->Records)
    {
        // same as above: converting .NET type to native type
        // records have a pointer back to the .NET record
        void* ptr = GCHandle::ToIntPtr(GCHandle::Alloc(rec)).ToPointer();
        _records[index]._set_ptr(ptr);
		index++;
    }
}


void CFoxProBuffer::Save()
{
    FoxProBuffer^ fp = _FPBUFFER;
    fp->Save();
}


CFoxProField* CFoxProBuffer::GetFields()
{
	return _fields;
}


CFoxProRecord* CFoxProBuffer::GetRecords()
{
	return _records;
}


int CFoxProBuffer::NumFields()
{
	FoxProBuffer^ fp = _FPBUFFER;
	return fp->Fields->Count;
}


int CFoxProBuffer::NumRecords()
{
	FoxProBuffer^ fp = _FPBUFFER;
	return fp->Records->Count;
}