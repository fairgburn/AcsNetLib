#pragma once
/*------------------------------------------------------------------
    CFoxProBuffer.h
    [AcsCppLib.NET.dll]

    declare interfaces for:
	 - CFoxProBuffer
	 - CFoxProField
	 - CFoxProRecord

    Brandon Fairburn 9/6/2017
------------------------------------------------------------------*/

// building DLL or using it?
#ifdef INSIDE_MANAGED_CODE
	#define DLL __declspec(dllexport)
    #define EXP_IMP
    
    // library internal
	#define CSNS AcsLib::FoxPro                      // C# namespace
#else
    #define DLL __declspec(dllimport)
    #define EXP_IMP extern
#endif

namespace AcsNetLib
{
    namespace FoxPro
    {
		// forward declarations
		struct CFoxProField;
		struct CFoxProRecord;
		struct CRecordList;
		typedef CFoxProField* FieldArray;

		/*--------------------------------------------------------------*/
        // interface to AcsLib.FoxPro.FoxProBuffer (C# library)
		/*--------------------------------------------------------------*/
        struct DLL CFoxProBuffer
        {   
			virtual void Open() = 0;
			virtual void Close() = 0;
            virtual void Save() = 0;
            virtual void SaveAs(char* outputFile) = 0;

			// save in destructor if AutoSave is true
			virtual void SetAutoSave(bool) = 0;
			
			// accessing records
			// IMPORTANT: buffer must be dereferenced to access records with the bracket overload
			//   example:   CFoxProRecord* first_rec = (*myBuffer)[0] // correct
			//              CFoxProRecord* first_rec = myBuffer[0]    // incorrect (won't compile)
			// these two do the same thing... just providing different options
			virtual CFoxProRecord* GetRecord(int index) = 0;
			virtual CFoxProRecord* operator[] (int index) = 0;

            virtual void AddRecord(CFoxProRecord* record) = 0;
            virtual void RemoveRecord(int index) = 0;

            //virtual FieldArray GetFields() = 0;
            //virtual CRecordList* GetRecords() = 0;

            // generate a new record in C# and return a pointer to its wrapper
            virtual CFoxProRecord* CreateNewRecord() = 0;

            virtual int NumFields() = 0;
            virtual int NumRecords() = 0;
        };

        // Library function: create a new buffer wrapper
		// defined in ManagedFoxProBuffer.cpp 
		// (wrapper classes are defined in src/wrapper/ and include/wrapper/ )
        DLL CFoxProBuffer* CreateFoxProBuffer(char* dbfFile);

		/*______________________________________________________________*/
		/*______________________________________________________________*/


        /*----------------------------------------------------------*/
        // interface to AcsLib.FoxPro.Record (C# library)
        /*----------------------------------------------------------*/
        struct DLL CFoxProRecord
        {
        public:

            virtual int Length() = 0;

            // get/set DBF data as ASCII string
            virtual char* Get(int index) = 0;
            virtual char* Get(char* field) = 0;
            virtual void Set(char* field, char* new_value) = 0;

            // get/set DBF data as one blob of bytes
            virtual unsigned char* GetCompleteRecord() = 0;
            virtual void SetCompleteRecord(unsigned char* blob) = 0;

            // 'deleted' flag access
            virtual void SetDeleted(bool) = 0; // set the deleted flag true or false
            virtual bool IsDeleted() = 0;      // check the flag

        };

        /*__________________________________________________________*/
        /*__________________________________________________________*/


		/*-------------------------------------------------------------------*/
		// data structure for FoxPro fields
		/*-------------------------------------------------------------------*/
		struct DLL CFoxProField
		{
		public:
			char* Name;
			char Type;
			int Offset, Length;

			CFoxProField(char* name, char type, int offset, int length);
			CFoxProField() {}
			~CFoxProField();
		};
		/*___________________________________________________________________*/
		/*___________________________________________________________________*/


		// shorthand typedefs for FoxPro interfaces
		typedef CFoxProBuffer IBuffer;
		typedef CFoxProRecord IRecord;

		typedef CFoxProBuffer* IBufferPtr;
		typedef CFoxProRecord* IRecordPtr;
    }


	
}