/*__________________________________________________________________
	CSQLite.h
	
	Interface for wrapping 

__________________________________________________________________*/


#pragma once

#ifdef INSIDE_MANAGED_CODE
#    define DECLSPECIFIER __declspec(dllexport)
#    define EXPIMP_TEMPLATE
#else
#    define DECLSPECIFIER __declspec(dllimport)
#    define EXPIMP_TEMPLATE extern
#endif

#include <string>
namespace AcsNetLib
{
	void ShowErrorMessageAndExit(char* msg);
	namespace SQL
	{
		//_________________________________
		// CSQLite
		class DECLSPECIFIER CSQLite
		{

			// constructor / destructor
		public:
			CSQLite(char* file);
			virtual ~CSQLite();


			// C++ interface to C# SQLite class
		public:
			int Open();
			void Close();
			// SQLiteDataReader ExecuteReader(string query)
			int Execute(char* query);
			//void ExecuteBatch(std::string commands);


			/*********************/

			SQLIterator GetFirstRow();
			SQLReader ExecuteReader(char*);
			/***********************/


		// internal
		private:
			// address of C# class instance in .NET heap
			void* __NET_HEAP__SQLiteDatabase;

		};

		/*------------------------------*/
		class SQLException
		{
		public:
			SQLException(char* msg);
			char* GetMessage();
		};

		class SQLReader
		{
		public:
			SQLReader() {}
			SQLIterator GetFirst();
		};
		class SQLIterator
		{
		public:
			SQLIterator() {}
			bool HasNext() { return true; }
			void MoveNext() {}
			int GetInt(char*);
			char* GetString(char*);
		};
	}
}