#pragma once

#include "FoxPro.NET.h"

namespace AcsNetLib
{
    namespace FoxPro
    {
        class RecordIterator
        {
        public:
            RecordIterator(CFoxProRecord* rec);
            bool MoveNext();
            CFoxProRecord& operator*();


        private:
            int _index;
            CFoxProRecord* _data;
        };

        struct RecordListNode
        {
            CFoxProRecord* Record;
            RecordListNode* next;
        };

        class CRecordList
        {
        public:
            // constructor / destructor
            CRecordList(void* ptr);
            ~CRecordList();

            // access
            CFoxProRecord* GetFirst();
            bool MoveNext();


        private:
            RecordListNode* _head;
            RecordListNode* _current;

            void* __NET_HEAP__List;

        };
    }
}