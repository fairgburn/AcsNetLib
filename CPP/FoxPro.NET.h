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
    #define DECLSPECIFIER __declspec(dllexport)
    #define EXPIMP_TEMPLATE
#else
    #define DECLSPECIFIER __declspec(dllimport)
    #define EXPIMP_TEMPLATE extern
#endif

namespace AcsNetLib
{
    namespace FoxPro
    {
		// forward declarations
		class CFoxProField;
		class CFoxProRecord;

		

		/*--------------------------------------------------------------*/
        // main interface for FoxPro manipulation
		/*--------------------------------------------------------------*/
        class DECLSPECIFIER CFoxProBuffer
        {
        // constructor / destructor
        public:
            CFoxProBuffer(char* inputFile);
            ~CFoxProBuffer();

        // interface to C# class
        public:
            void Open();
            void Save();
            //void Update(CFoxProRecord rec, char* field, char* val);

            CFoxProField* GetFields();
            CFoxProRecord* GetRecords();


        // internal
        private:
            // address of C# class in .NET heap
            void* __NET_HEAP__FoxProBuffer;


            CFoxProField* _fields;
            CFoxProRecord* _records;
        };
		/*______________________________________________________________*/
		/*______________________________________________________________*/



		/*-------------------------------------------------------------------*/
		// data structure for FoxPro fields
		/*-------------------------------------------------------------------*/
		class DECLSPECIFIER CFoxProField
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



		/*----------------------------------------------------------*/
		// data structure for FoxPro records
		/*----------------------------------------------------------*/
		class DECLSPECIFIER CFoxProRecord
		{
		public:
			// constructor with pointer to .NET Record instance
			CFoxProRecord(void* pointer);
			CFoxProRecord() {}
			~CFoxProRecord();

			int Length();
			char* Get(char* field);
			void Set(char* field, char* new_value);

			// DO NOT use this; internal DLL use only
			void _set_ptr(void* ptr);

		private:
			// pointer to object in .NET heap
			void* __NET_HEAP__Record;
		};
		/*__________________________________________________________*/
		/*__________________________________________________________*/

    }
}