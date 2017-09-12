/*---------------------------------------------------
    RecordIterator
    usage:
        
        CFoxProBuffer fp("C:\path\to\file.dbf");
        Iterator it = fp.Iterator();
        do {
            

----------------------------------------------------*/

#include "include/RecordList.h"

using namespace AcsNetLib::FoxPro;

RecordIterator::RecordIterator(CFoxProRecord* rec)
{
    _data = rec;
}




