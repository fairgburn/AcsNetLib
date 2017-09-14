#pragma once

#include <gcroot.h>
#include "FoxPro.NET.h"

namespace ManagedWrappers
{

    class ManagedFoxProBuffer : public IBuffer
    {
    protected:
        ManagedFoxProBuffer(CSNS::FoxProBuffer^ buf) : _buffer(buf) {}
        ~ManagedFoxProBuffer() { delete this; }

        // handle to C# buffer
        gcroot<FoxProBuffer^> _buffer;

    public:
        // use factory model to create instances
        static IBuffer* CreateBuffer(char* dbfFile);

        void Open();
        void Close();
        void Save();
        void SaveAs(char* outputFile);

        void AddRecord(AcsNetLib::FoxPro::CFoxProRecord* record);
        void RemoveRecord(int index);
        CFoxProRecord* RecordFactory(char defaultChar = ' ');

        int NumFields();
        int NumRecords();
    };
}