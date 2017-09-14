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
	#include <gcroot.h>
	#define DLL __declspec(dllexport)
    #define EXPIMP_TEMPLATE
#else
    #define DLL __declspec(dllimport)
    #define EXPIMP_TEMPLATE extern
#endif

namespace AcsNetLibCpp
{
    namespace FoxPro
    {
		// forward declarations
		class CFoxProField;
		class CFoxProRecord;
		class CRecordList;
		typedef CFoxProField* FieldArray;


		
		/*--------------------------------------------------------------*/
        // main interface for FoxPro manipulation
		/*--------------------------------------------------------------*/

		// forward declarations
		class CFoxProRecord;
		class CFoxProField;
		class CRecordList;
		typedef CFoxProField* FieldArray;

        class DLL CFoxProBuffer
        {
        // constructor / destructor
        public:
            CFoxProBuffer(char* inputFile);
            ~CFoxProBuffer();

        // interface to C# class
        public:
            void Open();
            void Close();
            void Save();
            void SaveAs(char* outputFile);

			void AddRecord(CFoxProRecord record);
			void Remove(int index);

            FieldArray GetFields();
            CRecordList* GetRecords();

            // let C# create and manage a new record so we know the size and
            // memory is handled properly (internally, record items are byte arrays that
            // must be exactly the right size every time or the file will be corrupted)
            // Parameter: the character with which to fill a record item (default to space ' ')
            CFoxProRecord RecordFactory(char defaultChar = ' ');

			int NumFields();
			int NumRecords();


        // internal
        private:
            // address of C# class in .NET heap
			#ifdef INSIDE_MANAGED_CODE
            gcroot<AcsLib::FoxPro::FoxProBuffer^> _ptr;
			#endif


            FieldArray _fields;
			CRecordList* _records;

        };
		/*______________________________________________________________*/
		/*______________________________________________________________*/



        /*----------------------------------------------------------*/
        // data structure for FoxPro records
        /*----------------------------------------------------------*/
        class DLL CFoxProRecord
        {
        public:
            // constructor with pointer to .NET Record instance
            CFoxProRecord(void* pointer);
            CFoxProRecord() {}
            ~CFoxProRecord();

            int Length();
            char* GetString(int index);
            char* GetString(char* field);
            void Set(char* field, char* new_value);
			CFoxProRecord Copy(); // returns new copy of this record

            // 'deleted' flag access
            void SetDeleted(bool); // set the deleted flag true or false
            bool IsDeleted();      // check the flag

            // DO NOT use this; internal DLL use only
			#ifdef INSIDE_MANAGED_CODE
            void _set_ptr(void* ptr);
			void* _get_ptr();
			#endif

        private:
            // pointer to object in .NET heap
            void* _ptr;

        };
        /*__________________________________________________________*/
        /*__________________________________________________________*/


		/*----------------------------------------------------------*/
		// list of CFoxProRecords
		//  - wrapper back to C# list
		/*----------------------------------------------------------*/
		class DLL CRecordList
		{
		public:
			// constructor / destructor
			CRecordList(void* ptr);
			CRecordList() {}
			~CRecordList() {};

			// access
			CFoxProRecord GetAt(int index);
			void Add(CFoxProRecord record);
            int Length();

			#ifdef INSIDE_MANAGED_CODE
			void _set_ptr(void* ptr);
			void* _get_ptr();
			#endif
			


		private:
			void* _ptr;
		};
		/*__________________________________________________________*/
		/*__________________________________________________________*/


		/*-------------------------------------------------------------------*/
		// data structure for FoxPro fields
		/*-------------------------------------------------------------------*/
		class DLL CFoxProField
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