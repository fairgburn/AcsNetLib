#include <stdio.h>
#include "FoxPro.NET.h"

using namespace AcsNetLib::FoxPro;

int main()
{
    // create buffer and grab a few records
    CFoxProBuffer fpBuffer("C:\\Users\\bfairburn\\workspace\\VS2017\\AcsNetLib\\_build\\tests\\T_cpp_native\\Debug\\sys.dbf");
    CFoxProRecord rec = fpBuffer.GetRecords().GetAt(0);

    // verify we're looking at the right file
    /*char* name1 = rec[0].Get("descr");
    char* name2 = rec[1].Get("descr");
    char* name3 = rec[2].Get("descr");*/

    // Making a new record (be sure to use this instead of making your own)
    // RecordFactory() - create a new record with guaranteed memory safety
    CFoxProRecord new_record = fpBuffer.RecordFactory();

    // set all the fields; for example:
    new_record.Set("maxlen", "120");

    char* name = new_record.Get("descr");


    getchar();
}