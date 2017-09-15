/*------------------------------------------------------------------
    CFoxProBuffer.h
    [AcsCppLib.NET.dll]

    declare interfaces for:
	 - CFoxProBuffer
	 - CFoxProField
	 - CFoxProRecord

    Brandon Fairburn 9/6/2017
------------------------------------------------------------------*/
#pragma once


// building DLL or using it?
#ifdef INSIDE_MANAGED_CODE
	#define DLL __declspec(dllexport)
    #define EXP_IMP
    
    // library internal
    //#include "managed_wrappers/ManagedFoxProBuffer.h"
    #define IBuffer AcsNetLib::FoxPro::CFoxProBuffer // native buffer
    #define IRecord AcsNetLib::FoxPro::CFoxProRecord // native record
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
        // main interface for FoxPro manipulation
		/*--------------------------------------------------------------*/

		// forward declarations
		struct CFoxProRecord;
		struct CFoxProField;
		struct CRecordList;
		typedef CFoxProField* FieldArray;

        struct DLL CFoxProBuffer
        {   
            virtual void Open() = 0;
            virtual void Close() = 0;
            virtual void Save() = 0;
            virtual void SaveAs(char* outputFile) = 0;

            virtual CFoxProRecord* GetRecord(int index) = 0;

            virtual void AddRecord(CFoxProRecord* record) = 0;
            virtual void RemoveRecord(int index) = 0;

            //virtual FieldArray GetFields() = 0;
            //virtual CRecordList* GetRecords() = 0;

            // let C# create and manage a new record so we know the size and
            // memory is handled properly (internally, record items are byte arrays that
            // must be exactly the right size every time or the file will be corrupted)
            // Parameter: the character with which to fill a record item (default to space ' ')
            virtual CFoxProRecord* RecordFactory() = 0;

            virtual int NumFields() = 0;
            virtual int NumRecords() = 0;
        };

        // Library function: create a new buffer
		// defined in ManagedFoxProBuffer.cpp 
        DLL CFoxProBuffer* CreateFoxProBuffer(char* dbfFile);

		/*______________________________________________________________*/
		/*______________________________________________________________*/



        /*----------------------------------------------------------*/
        // data structure for FoxPro records
        /*----------------------------------------------------------*/
        struct DLL CFoxProRecord
        {
        public:

            virtual int Length() = 0;

            // get DBF data as ASCII string
            virtual char* Get(int index) = 0;
            virtual char* Get(char* field) = 0;

            virtual void Set(char* field, char* new_value) = 0;

            // 'deleted' flag access
            virtual void SetDeleted(bool) = 0; // set the deleted flag true or false
            virtual bool IsDeleted() = 0;      // check the flag

        };

        /*__________________________________________________________*/
        /*__________________________________________________________*/


		/*----------------------------------------------------------*/
		// list of CFoxProRecords
		//  - wrapper back to C# list
		/*----------------------------------------------------------*/
		/*class DLL CRecordList
		{
		public:
			// constructor / destructor
			CRecordList(void* ptr);
			CRecordList() {}
			~CRecordList() {};

			// access
			CFoxProRecord* GetAt(int index);
			void Add(CFoxProRecord* record);
            int Length();

			#ifdef INSIDE_MANAGED_CODE
			void _set_ptr(void* ptr);
			void* _get_ptr();
			#endif
			


		private:
			void* _ptr;
		};*/
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



		

    }
}