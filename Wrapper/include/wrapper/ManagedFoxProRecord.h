#pragma once

#include <gcroot.h>
#include "FoxPro.NET.h"

using namespace System;

namespace ManagedWrappers
{

    class ManagedFoxProRecord : public IRecord
    {
    protected:
        ~ManagedFoxProRecord();

        // handle to parent C# buffer
        gcroot<CSNS::Record^> _record;

        // which record in buffer we're looking at
        int _index;

        // native char array for GetCompleteRecord()
        unsigned char* _blob;
        bool _delBlob; // flag to delete blob (unmanaged memory allocation)

        // handle for new record (only used if creating a new record)
        bool _new = false;
        gcroot<CSNS::Record^> _newRecord;

    public:
        // use factory model to create new records
		//static IRecord* CreateRecord(CSNS::FoxProBuffer^ buf, int index);

        ManagedFoxProRecord(CSNS::Record^);

		int Length();

		char* Get(int index);
		char* Get(char* field);
        void Set(char* field, char* new_value);

        void GetBlob(unsigned char* dest);
        unsigned char* GetCompleteRecord();
        void SetBlob(const char* blob);


		void SetDeleted(bool);
		bool IsDeleted();
    };

}