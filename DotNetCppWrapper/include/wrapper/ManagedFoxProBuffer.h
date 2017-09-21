#pragma once

#include <gcroot.h>
#include "FoxPro.NET.h"
#include "ManagedFoxProRecord.h"

namespace ManagedWrappers
{

    class ManagedFoxProBuffer : public IBuffer
    {

	/*--------------------
	 * internal data
	 *--------------------*/
    protected:
        ManagedFoxProBuffer(CSNS::FoxProBuffer^ buf);
        ~ManagedFoxProBuffer();

        // handle to C# buffer
        gcroot<CSNS::FoxProBuffer^> _buffer;

		// array of pointers to record wrappers
		// allocated when buffer is created, and when records are added/removed
		ManagedFoxProRecord** _records;

	/*--------------------
	* private methods
	*--------------------*/
	private:

		// initialize the array of record pointers (_records)
		// if _records != nullptr, then delete it and make a new array to wrap the current C# records
		void UpdateRecordPtrArray();
		
	/*----------------------------------------------------------------
	* public methods (implementation of interface from FoxPro.NET.h)
	*----------------------------------------------------------------*/
    public:
        // use factory model to create instances
        static IBuffer* CreateBuffer(char* dbfFile);

        void Open();
        void Close();
        void Save();
        void SaveAs(char* outputFile);

        IRecord* GetRecord(int index);
		IRecord* operator[] (int index);

        void AddRecord(IRecord* record);
        void RemoveRecord(int index);
        IRecord* CreateNewRecord();

        int NumFields();
        int NumRecords();

	
    };
}