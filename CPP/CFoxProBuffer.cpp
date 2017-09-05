#include "CFoxProBuffer.h"

#define _NET_HANDLE GCHandle::FromIntPtr(IntPtr(__NET_HEAP__FoxProBuffer))
#define _FPBUFFER(handle) safe_cast<FoxProBuffer^>(handle.Target);

// C# namespaces
using namespace System;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace FoxPro_NET;
using namespace database::structs;

// header namespace
using namespace AcsNetLib::FoxPro;

using std::vector;

/*--------------------*/
// CFoxProBuffer
/*--------------------*/

CFoxProBuffer::CFoxProBuffer(char* inputFile)
{
	String^ _net_file = gcnew String(inputFile);
	FoxProBuffer^ fp = gcnew FoxProBuffer(_net_file);

	// pin the .NET object
	__NET_HEAP__FoxProBuffer = GCHandle::ToIntPtr(GCHandle::Alloc(fp)).ToPointer();
}


CFoxProBuffer::~CFoxProBuffer()
{
	_NET_HANDLE.Free();
}


void CFoxProBuffer::Open()
{
	FoxProBuffer^ fp = _FPBUFFER(_NET_HANDLE);
	fp->Open();
}

void CFoxProBuffer::Save()
{
	FoxProBuffer^ fp = _FPBUFFER(_NET_HANDLE);
	fp->Save();
}

void CFoxProBuffer::Update(SRecord rec, char* field, char* val)
{
	String^ net_field = gcnew String(field);
	String^ net_val = gcnew String(val);
	
	FoxProBuffer^ fp = _FPBUFFER(_NET_HANDLE);

	for (int i = 0; i < fp->Records->Count; i++)
	{
		Record^ r = fp->Records[i];
		if (r->GetHashCode() == rec.ID)
		{
			r->Set(net_field, net_val);
			break;
		}

	}
}

vector<SField> CFoxProBuffer::GetFields()
{
	vector<SField> result;
	FoxProBuffer^ fp = _FPBUFFER(_NET_HANDLE);

	for (int i = 0; i < fp->Fields->Count; i++)
	{
		Field^ net_field = fp->Fields[i];
		SField f("name", net_field->Type, net_field->Offset, net_field->Length);
		result.push_back(f);
	}

	return result;
}

vector<SRecord> CFoxProBuffer::GetRecords()
{
	vector<SRecord> result;
	FoxProBuffer^ fp = _FPBUFFER(_NET_HANDLE);

	for (int i = 0; i < fp->Records->Count; i++)
	{
		Record^ net_record = fp->Records[i];
		SRecord r;
		r.ID = net_record->GetHashCode();
		result.push_back(r);
	}

	return result;
}