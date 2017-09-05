/*------------------------------------------------------------------
	CFoxProBuffer.h

	Interface for wrapping C# FoxProBuffer to native C++
------------------------------------------------------------------*/

#pragma once

#ifdef INSIDE_MANAGED_CODE
#    define DECLSPECIFIER __declspec(dllexport)
#    define EXPIMP_TEMPLATE
#else
#    define DECLSPECIFIER __declspec(dllimport)
#    define EXPIMP_TEMPLATE extern
#endif

#include <map>
#include <vector>

namespace AcsNetLib
{
	namespace FoxPro
	{
		/*---------------------*/
		// FoxPro structures
		/*---------------------*/

		struct DECLSPECIFIER SField
		{
			char* Name;
			char Type;
			int Offset, Length;

			SField(char* name, char type, int offset, int length)
			{
				this->Name = name;
				this->Type = type;
				this->Offset = offset;
				this->Length = length;
			}
		};

		struct DECLSPECIFIER SRecord
		{
			int ID;

			int Length();
			char* Get(char* field);
			void Set(char* field, char* val);
		};

		/*-----------------*/
		// main class
		/*-----------------*/

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
			void Update(SRecord rec, char* field, char* val);

			std::vector<SField> GetFields();
			std::vector<SRecord> GetRecords();


		// internal
		private:
			// address of C# class in .NET heap
			void* __NET_HEAP__FoxProBuffer;
		};

		
		
	}
}