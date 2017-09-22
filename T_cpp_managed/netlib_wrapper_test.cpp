#include <iostream>
#include <vector>
#include "FoxPro.NET.h"

using namespace std;
using namespace AcsNetLib::FoxPro;

// build this test with CLR support (.NET Framework 4.7) to step through DLL code in debugger

/* 
	(if we can get Winvent compiling with CLR support, we won't need to use the wrapper at all
	because Winvent code would be able to directly use C# classes from the library)

	For example, current way of copying the first record of sys.dbf, changing the line name,
	and adding this new record to the DBF:

	  CFoxProBuffer* buf = CreateFoxProBuffer("file.dbf");
	  CFoxProRecord* new_rec = buf->CreateNewRecord();
	  new_rec->SetCompleteRecord( (*buf)[0]->GetCompleteRecord ); // copies data from first record
	  buf->AddRecord(new_rec);

	  
	Potential usage if Winvent compiles with CLR:

	  // variable type is auto - see note 1
	  auto buf = gcnew FoxProBuffer("file.dbf") { AutoSave = true }; // AutoSave=true - see note 2

	  auto rec = buf->Records[0];


	  // note 1: declaring a variable as
	  // note 2: makes the buffer automatically create a new thread
	  //         to write the buffer to disk every time is it modified. C# handles
	  //         this in parallel so Winvent doesn't have to wait for the disk write
	  //         to finish, but this feature only works with CLR support right now
*/




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
	// same as CFoxProBuffer* buf = ...

	// loop over each record from the DBF
	//   - ProcDyn.dbf records represent a process
	//   - default value for 'auto' field is Y in the file I'm using
	for (int i = 0; i < buf->NumRecords(); i++) {

		// get current record and show auto status
		IRecordPtr rec = buf->GetRecord(i);
		cout << "record " << i << " - auto from DBF: " << rec->Get("auto") << endl;

		// turn auto off for process
		rec->Set("auto", "N");
	}

	// - Save buffer to another file to see result
	// - use buf->Save() instead if you just want to overwrite the original
	buf->SaveAs("ProcDyn - auto changed from Y to N.dbf");
	//buf->Save();
	 
	
	
	getchar();
}