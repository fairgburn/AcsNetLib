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

namespace AcsNetLib
{
	namespace FoxPro
	{
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
			void Update();

		// internal
		private:
			// address of C# class in .NET heap
			void* __NET_HEAP__FoxProBuffer;
		};

		
		/*---------------------*/
		// FoxPro structures
		/*---------------------*/

		struct Field
		{
			char* Name;
			char Type;
			int Offset, Length;

			Field(char* name, char type, int offset, int length)
			{
				this->Name = name;
				this->Type = type;
				this->Offset = offset;
				this->Length = length;
			}
		};

		struct Record
		{
			std::map<char*, char*> _data;
			
		};
	}
}