/*-----------------------------------------------------
    CFoxProBuffer.cpp
    [AcsCppLib.NET.dll]

    definitions for the FoxPro interface

    Brandon Fairburn 9/6/2017
-------------------------------------------------------*/

#include "FoxPro.NET.h"
#include "util.h"

// shortcut for getting pointer to .NET FoxProBuffer
#define _FPBUFFER NET_CAST(FoxProBuffer, NET_HANDLE(_netBuffer))

// C# namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace AcsLib::FoxPro;

// header namespace
using namespace AcsNetLib::FoxPro;

/*-------------------------------------*/
// helper functions (not part of class)
/*-------------------------------------*/

/*RecordArray hfManagedRecordsToNative(List<Record^>^ records)
{
    RecordArray rarr = new CFoxProRecord[records->Count];

    int index = 0;
    for each (Record^ rec in records)
    {
        void* ptr = GCHandle::ToIntPtr(GCHandle::Alloc(rec)).ToPointer();
        rarr[index]._set_ptr(ptr);
    }

    return rarr;
}*/



/*-----------------------------*/
// constructor / destructor 
/*-----------------------------*/

CFoxProBuffer::CFoxProBuffer(char* inputFile)
{
    String^ net_file = gcnew String(inputFile);
    FoxProBuffer^ fp = gcnew FoxProBuffer(net_file);


    // pin the C# buffer
    //##_netBuffer = GCHandle::ToIntPtr(GCHandle::Alloc(fp)).ToPointer();
    _netBuffer = fp;

    // go ahead and open the file
    Open();
}


CFoxProBuffer::~CFoxProBuffer()
{
    //##NET_HANDLE(_netBuffer).Free();

    delete[] _fields;
}


/*-----------------------------*/
//  Public functions
/*-----------------------------*/

void CFoxProBuffer::Open()
{
    ICallb
    // call Open() on the C# instance
    //##fp->Open();
    _netBuffer->Open();

	// pin the C# record list
	//##void* list_ptr = NET_ALLOC_GETPTR(fp->Records);
	//##_records = new CRecordList(list_ptr);
    _recordPtr = _netBuffer->Records;

    // initiate the fields list & get fields from C# instance
    _fields = new CFoxProField[_netBuffer->Fields->Count];
    int index = 0;
    for each (Field^ field in _netBuffer->Fields)
    {
        // convert .NET fields to native CFoxProField and store them
        _fields[index].Name = util::ManagedStringToCharArray(field->Name);
        _fields[index].Type = static_cast<char> (field->Type);
        _fields[index].Length = field->Length;
        _fields[index].Offset = field->Offset;
        index++;
    }
}


void CFoxProBuffer::Close()
{
    //##FoxProBuffer^ fp = _FPBUFFER;
    _netBuffer->Close();
}


void CFoxProBuffer::Save()
{
    //##FoxProBuffer^ fp = _FPBUFFER;
    _netBuffer->Save();
}


void CFoxProBuffer::SaveAs(char* outputFile)
{
    //##FoxProBuffer^ fp = _FPBUFFER;
    String^ net_outputFile = util::CharArrayToManagedString(outputFile);
    _netBuffer->SaveAs(net_outputFile);
}


void CFoxProBuffer::AddRecord(CFoxProRecord record)
{
	//##FoxProBuffer^ fp = _FPBUFFER;
	Record^ rec = NET_CAST(Record, NET_HANDLE(record._get_ptr()));

	_netBuffer->Records->Add(rec);
}


void CFoxProBuffer::Remove(int index)
{
	//FoxProBuffer^ fp = _FPBUFFER;
	_netBuffer->Records->RemoveAt(index);
}


CFoxProField* CFoxProBuffer::GetFields()
{
	return _fields;
}


CRecordList* CFoxProBuffer::GetRecords()
{
	return _records;
	/*FoxProBuffer^ fp = _FPBUFFER;

	// get pointer to the C# buffer's record list
	void* ptr = NET_ALLOC_GETPTR(fp->Records);

	CRecordList rec_list(ptr);
	return rec_list;*/
}


CFoxProRecord CFoxProBuffer::RecordFactory(char defaultChar)
{
    // create a new record in .NET
    FoxProBuffer^ fp = _FPBUFFER;
    Record^ new_record = fp->RecordFactory(defaultChar);
    
    // create/return a new wrapper record
    void* ptr = NET_ALLOC_GETPTR(new_record);
    CFoxProRecord result;
    result._set_ptr(ptr);

    return result;
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
