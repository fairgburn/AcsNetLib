/*------------------------------------------------------------------
    CSQLite.h

    Interface for wrapping C# SQLiteDatabase to native C++
------------------------------------------------------------------*/


#pragma once

#ifdef INSIDE_MANAGED_CODE
#    define DLL __declspec(dllexport)
#    define EXP_IMP
#else
#    define DLL __declspec(dllimport)
#    define EXP_IMP extern
#endif

#include <string>
namespace AcsNetLib
{
    namespace SQL
    {
        //_________________________________
        // CSQLite
        class DLL CSQLite
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