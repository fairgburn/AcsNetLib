/*-----------------------------------------------------
    CFoxProBuffer.cpp
    [AcsCppLib.NET.dll]

    definitions for the FoxPro interface

    Brandon Fairburn 9/6/2017
-------------------------------------------------------*/

#include "CFoxProBuffer.h"
#include "util.h"



// C# namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace FoxPro_NET;
using namespace database::structs;

// header namespace
using namespace AcsNetLib::FoxPro;

using std::vector;

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
}


/*-----------------------------*/
//  Public functions
/*-----------------------------*/

void CFoxProBuffer::Open()
{
    // call Open() on the C# instance
    FoxProBuffer^ fp = NET_POINTER(FoxProBuffer, NET_HANDLE(__NET_HEAP__FoxProBuffer));
    fp->Open();

    // get the C# fields
    for each (Field^ field in fp->Fields)
    {
        // convert .NET fields to native CFoxProField and store them
        char* name = util::ManagedStringToCharArray(field->Name);
        CFoxProField f(name, field->Type, field->Offset, field->Length);
        _fields.push_back(f);

    }

    // get the C# records
    for each (Record^ rec in fp->Records)
    {
        // same as above: converting .NET type to native type
        // records have a pointer back to the .NET record
        void* ptr = GCHandle::ToIntPtr(GCHandle::Alloc(rec)).ToPointer();
        CFoxProRecord r(ptr);
        _records.push_back(r);
    }
}


void CFoxProBuffer::Save()
{
    FoxProBuffer^ fp = NET_POINTER(FoxProBuffer, NET_HANDLE(__NET_HEAP__FoxProBuffer));
    fp->Save();
}


vector<CFoxProField> CFoxProBuffer::GetFields()
{
    return _fields;
}


vector<CFoxProRecord> CFoxProBuffer::GetRecords()
{
    return _records;
}