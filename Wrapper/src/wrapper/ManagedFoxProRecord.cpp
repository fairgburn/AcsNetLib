#include <gcroot.h>

#include "FoxPro.NET.h"
#include "ManagedFoxProRecord.h"

using namespace System;




	class ManagedFoxProRecord : public IRecord
	{
	protected:
		ManagedFoxProRecord(CSNS::Record^ record) : _record(record) {}
		~ManagedFoxProRecord();

		// handle to C# record
		gcroot<CSNS::Record^> _record;
	public:
		// use factory model to create new records
		static IRecord* CreateRecord(CSNS::Record^);

		int Length();
		int Length();
		char* GetString(int index);
		char* GetString(char* field);
		void Set(char* field, char* new_value);
		CFoxProRecord Copy(); // returns new copy of this record

		void SetDeleted(bool);
		bool IsDeleted();
	};