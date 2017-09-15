#pragma once

#include <gcroot.h>
#include "FoxPro.NET.h"

using namespace System;

namespace ManagedWrappers
{

    class ManagedFoxProRecord : public IRecord
    {
    protected:
        ManagedFoxProRecord(CSNS::FoxProBuffer^ record, int index);
        ~ManagedFoxProRecord();

        // handle to parent C# buffer
        gcroot<CSNS::FoxProBuffer^> _buffer;

        // which record in buffer we're looking at
        int _index;

        // handle for new record (only used if creating a new record)
        bool _new = false;
        gcroot<CSNS::Record^> _newRecord;

    public:
        // use factory model to create new records
		static IRecord* CreateRecord(CSNS::FoxProBuffer^ buf, int index);

        // set a handle for new record
        void SetHandle(CSNS::Record^ rec);

		int Length();
		char* Get(int index);
		char* Get(char* field);
		void Set(char* field, char* new_value);

		void SetDeleted(bool);
		bool IsDeleted();
    };

}