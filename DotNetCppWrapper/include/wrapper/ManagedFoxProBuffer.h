#pragma once

#include <gcroot.h>
#include "FoxPro.NET.h"
#include "ManagedFoxProRecord.h"

namespace ManagedWrappers
{

    class ManagedFoxProBuffer : public IBuffer
    {
    protected:
        ManagedFoxProBuffer(CSNS::FoxProBuffer^ buf);
        ~ManagedFoxProBuffer();

        // handle to C# buffer
        gcroot<CSNS::FoxProBuffer^> _buffer;

		ManagedFoxProRecord** _records;

    public:
        // use factory model to create instances
        static IBuffer* CreateBuffer(char* dbfFile);

        void Open();
        void Close();
        void Save();
        void SaveAs(char* outputFile);

        IRecord* GetRecord(int index);
		IRecord* operator[] (int index);

        void AddRecord(IRecord* record);
        void RemoveRecord(int index);
        IRecord* CreateNewRecord();

        int NumFields();
        int NumRecords();
    };
}