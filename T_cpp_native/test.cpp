#include <stdio.h>
#include "FoxPro.NET.h"

using namespace AcsNetLib::FoxPro;

int main()
{

    CFoxProBuffer fp("sys.dbf");
    fp.SaveAs("out.dbf");

    CRecordList records = fp.GetRecords();
    CFoxProRecord rec[3] = {
        records.GetAt(3),
        records.GetAt(6),
        records.GetAt(9)
    };

    char* name1 = rec[0].Get("descr");

    getchar();
}