#include <iostream>
#include <vector>
#include "FoxPro.NET.h"

using namespace std;
using namespace AcsNetLib::FoxPro;

// build this test with CLR support (.NET Framework 4.7) to step through DLL code in debugger


int main()
{
	//---------------------------------------------------------------------
	// type names starting with a capital 'I' are just shortcut typedefs
	// from FoxPro.NET.h for the actual interfaces:
	/*
		typedef CFoxProBuffer IBuffer;
		typedef CFoxProRecord IRecord;

		typedef CFoxProBuffer* IBufferPtr;
		typedef CFoxProRecord* IRecordPtr;
	*/
	// so for example CFoxProBuffer* and IBufferPtr are interchangeable
	// in any code that's using the AcsNetLib::FoxPro namespace
	//---------------------------------------------------------------------

	IBufferPtr buf = CreateFoxProBuffer("ProcDyn.dbf");
	// same as ` CFoxProBuffer* buf = CreateFoxProBuffer("ProcDyn.dbf"); `

	// loop over each record from the DBF
	//   - ProcDyn.dbf records represent a process
	//   - default value for 'auto' field is Y in the file I'm using
	for (int i = 0; i < buf->NumRecords(); i++) {

		// get current record and show auto status
		IRecordPtr rec = buf->GetRecord(i);
		cout << "record " << i << " - auto from DBF: " << rec->Get("auto") << endl;

		// turn auto off for process
		rec->Set("auto", "N");
		
		// show auto status after rec->Set()
		cout << "record " << i << " - auto value in memory after modification: " << rec->Get("auto") << endl;
	}

	// - Save buffer to another file to see result
	// - use buf->Save() instead if you just want to overwrite the original
	buf->SaveAs("ProcDyn - auto changed from Y to N.dbf");
	//buf->Save();
	 
	
	
	getchar();
}