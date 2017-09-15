#pragma once

#include <gcroot.h>
#include "FoxPro.NET.h"

using namespace System;

namespace ManagedWrappers
{

    class ManagedFoxProRecord : public IRecord
    {
    protected:
        ManagedFoxProRecord(CSNS::Record^ record);
        ~ManagedFoxProRecord();

        // handle to C# record
        gcroot<CSNS::Record^> _record;
    public:
        // use factory model to create new records
		static IRecord* CreateRecord(CSNS::Record^);

		int Length();
		char* Get(int index);
		char* Get(char* field);
		void Set(char* field, char* new_value);
		CFoxProRecord* Copy(); // returns new copy of this record

		void SetDeleted(bool);
		bool IsDeleted();

        // return handle to C# record
        gcroot<CSNS::Record^> GetHandle();
    };

}