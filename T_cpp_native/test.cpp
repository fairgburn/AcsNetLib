#include <stdio.h>
#include <vector>
#include "FoxPro.NET.h"

using namespace AcsNetLib::FoxPro;
using std::vector;

int main()
{
	char* filename = "sys.dbf";
    
    // create buffer and get record list
    CFoxProBuffer* fpBuffer = CreateFoxProBuffer("sys.dbf");
	
    for (int i = 0; i < fpBuffer->NumRecords(); i++) {
        
        //printf("%s\n", fpBuffer->GetRecord(i)->Get("descr"));
    }

    CFoxProRecord* myRecord = fpBuffer->RecordFactory();
    myRecord->Set("descr", "xyzzzzzzz");
    printf("%s\n", myRecord->Get("descr"));
    printf("%s\n", fpBuffer->GetRecord(0)->Get("descr"));
    getchar();

	return 0;
}