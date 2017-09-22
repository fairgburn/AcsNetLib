#pragma once

#include <gcroot.h>
#include "FoxPro.NET.h"
#include "ManagedFoxProRecord.h"

namespace ManagedWrappers
{

    class ManagedFoxProBuffer : public AcsNetLib::FoxPro::IBuffer
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
		//   - allocated when buffer is created, and when records are added/removed
		//
		// keep an int to track the size of the array
		ManagedRecordPtr* _records;
		int _records_size;


	/*--------------------
	* private methods
	*--------------------*/
	private:

		// resize the array of record wrappers (_records)
		// keep size a power of 2
		//   - grow the array by left-shifting the size
		//   - shrink the array by right-shifting the size
		// (for efficiency and to avoid making a separate data structure)
		//
		void GrowRecordPtrArray();
		void ShrinkRecordPtrArray();
		// example
		// (assume original size is 8, and the array is full):
		/*
		     AddRecord(my_new_record); // _records_size is 8 and the array is already full
		         // AddRecord() will see this and call GrowRecordPtrArray()
		         // _records_size is now 16
		*/


		// initialize/refresh the array of record pointers (_records)
		//
		// if _records == nullptr, then allocate it and a wrapper for each C# record
		// else, update tracked pointers
		void UpdateRecordPtrArray();
		
	/*------------------------------------------------------------------------------
	* public methods (implementation of CFoxProBuffer interface from FoxPro.NET.h)
	*------------------------------------------------------------------------------*/
    public:
        // create native buffer instances (needed because the constructor takes a non-native parameter)
        static AcsNetLib::FoxPro::IBufferPtr CreateBuffer(char* dbfFile);

        void Open();
        void Close();
        void Save();
        void SaveAs(char* outputFile);

		AcsNetLib::FoxPro::IRecordPtr GetRecord(int index);
		AcsNetLib::FoxPro::IRecordPtr operator[] (int index);

        void AddRecord(AcsNetLib::FoxPro::IRecordPtr record);
        void RemoveRecord(int index);
		AcsNetLib::FoxPro::IRecordPtr CreateNewRecord();

        int NumFields();
        int NumRecords();
		
    };
}