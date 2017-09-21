#pragma once

#include <gcroot.h>
#include "FoxPro.NET.h"

using namespace System;

namespace ManagedWrappers
{
	class ManagedFoxProRecord : public IRecord
    {
    protected:

        // handle to parent C# buffer
        gcroot<CSNS::Record^> _record;

        // which record in buffer we're looking at
        int _index;

        // native char array for GetCompleteRecord()
        unsigned char* _blob;
        bool _delBlob; // flag to delete blob (unmanaged memory allocation)

    public:
        // Constructor: wrap a given C# record
        ManagedFoxProRecord(CSNS::Record^);
		~ManagedFoxProRecord();

        // library access only:
        // get the C# record (used by ManagedFoxProBuffer::AddRecord() )
        gcroot<CSNS::Record^> GetCSRecord();

		int Length();

		char* Get(int index);
		char* Get(char* field);
        void Set(char* field, char* new_value);

        void GetBlob(unsigned char* dest);
        unsigned char* GetCompleteRecord();
        void SetCompleteRecord(unsigned char* blob);


		void SetDeleted(bool);
		bool IsDeleted();
    };

	// pointer typedef for code readability
	typedef ManagedFoxProRecord* ManagedRecordPtr;

}