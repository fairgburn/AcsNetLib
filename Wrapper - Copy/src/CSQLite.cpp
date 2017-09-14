#include <string>

#include "stdafx.h"
#include "CSQLite.h"

using namespace SQLite_NET;
using namespace System;
using namespace System::Runtime::InteropServices;

namespace AcsNetLibCpp
{
    namespace SQL
    {
        //________________________________________________________
        // Constructor
        //  allocate memory on .NET heap for SQLite functionality
        //________________________________________________________
        CSQLite::CSQLite(char* file)
        {
            // convert char* to .NET string
            String^ _net_file = gcnew String(file);

            // instantiate the .NET object
            SQLiteDatabase^ db = gcnew SQLiteDatabase(_net_file);

            // pin .NET object (protect it from garbage collector) and store its address
            __NET_HEAP__SQLiteDatabase = GCHandle::ToIntPtr(GCHandle::Alloc(db)).ToPointer();
        }


        //_____________________________________________________________
        // Destructor
        //  release the SQLiteDatabase object to the garbage collector
        //_____________________________________________________________
        CSQLite::~CSQLite()
        {
            GCHandle _net_handle = GCHandle::FromIntPtr(IntPtr(__NET_HEAP__SQLiteDatabase));
            _net_handle.Free();
        }


        //_______________________________________________________
        //
        // C++ Wrapper
        //  expose methods from the C# class to native C++ code
        //_______________________________________________________


        // call C# Open()
        int CSQLite::Open()
        {
            GCHandle h = GCHandle::FromIntPtr(IntPtr(__NET_HEAP__SQLiteDatabase));
            SQLiteDatabase^ db = safe_cast<SQLiteDatabase^>(h.Target);
            return db->Open();
        }

        // call C# Close()
        void CSQLite::Close()
        {
            GCHandle h = GCHandle::FromIntPtr(IntPtr(__NET_HEAP__SQLiteDatabase));
            SQLiteDatabase^ db = safe_cast<SQLiteDatabase^>(h.Target);
            db->Close();
        }

        // call C# Execute
        int CSQLite::Execute(char* query)
        {
            // convert char* to .NET string
            String^ _net_str = gcnew String(query);

            GCHandle h = GCHandle::FromIntPtr(IntPtr(__NET_HEAP__SQLiteDatabase));
            SQLiteDatabase^ db = safe_cast<SQLiteDatabase^>(h.Target);
            return db->Execute(_net_str);
        }
    }
}