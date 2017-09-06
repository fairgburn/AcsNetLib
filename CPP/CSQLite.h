/*------------------------------------------------------------------
    CSQLite.h

    Interface for wrapping C# SQLiteDatabase to native C++
------------------------------------------------------------------*/


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


        // internal
        private:
            // address of C# class instance in .NET heap
            void* __NET_HEAP__SQLiteDatabase;

        };
    }
}