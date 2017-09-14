#pragma once

#include <gcroot.h>
#include "FoxPro.NET.h"


namespace ManagedWrappers
{

    class ManagedFoxProRecord : IRecord
    {
    protected:
        ManagedFoxProRecord(AcsLib::FoxPro::Record^ record);
        ~ManagedFoxProRecord();

        // handle to C# record
        gcroot<AcsLib::FoxPro::Record^> _record;

    public:
        // use factory model to create new records

    };

}