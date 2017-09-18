#pragma once
#pragma once

#include <gcroot.h>
#include "FoxPro.NET.h"

using namespace System;
using namespace System::Collections::Generic;

namespace ManagedWrappers
{

	class ManagedRecordList : public IRecord
	{
	protected:
		~ManagedRecordList();

		// handle to parent C# list
		gcroot<CSNS::FoxProBuffer^> _buffer;

	public:
		// factory method to create the list
		ManagedRecordList(CSNS::FoxProBuffer^);

		// get a specific record
		IRecord* GetAt(int index);
		IRecord* operator[] (int index);

		void Add(IRecord* record);
		int Count();
	};

}