#pragma once

#include <gcroot.h>
#include "FoxPro.NET.h"

namespace ManagedWrappers
{

    class ManagedFoxProBuffer : public IBuffer
    {
    protected:
        ManagedFoxProBuffer(CSNS::FoxProBuffer^ buf);
        ~ManagedFoxProBuffer();

        // handle to C# buffer
        gcroot<CSNS::FoxProBuffer^> _buffer;

    public:
        // use factory model to create instances
        static IBuffer* CreateBuffer(char* dbfFile);

        void Open();
        void Close();
        void Save();
        void SaveAs(char* outputFile);

        IRecord* GetRecord(int index);

        void AddRecord(IRecord* record);
        void RemoveRecord(int index);
        IRecord* RecordFactory();

        int NumFields();
        int NumRecords();
    };
}