#pragma once

#include "FoxPro.NET.h"

namespace AcsNetLib
{
    namespace FoxPro
    {
        struct RecordListNode
        {
            CFoxProRecord* Record;
            RecordListNode* next;
            //RecordListNode* previous;
        };

        class CRecordList
        {
        public:
            // constructor / destructor
            CRecordList();
            ~CRecordList();

            // access
            CFoxProRecord* GetFirst();
            bool MoveNext();


        private:
            RecordListNode* _head;
            RecordListNode* _current;

        };
    }
}