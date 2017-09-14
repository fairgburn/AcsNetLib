#include <stdio.h>
#include <vector>
#include "FoxPro.NET.h"

using namespace AcsNetLib::FoxPro;
using std::vector;

int main()
{
	//char* filename = "C:\\Users\\Brandon\\workspace\\VS2017\\ACS.NET Library\\_build\\tests\\T_cpp_native\\Debug\\sys.dbf";
	char* filename = "sys.dbf";
    // create buffer and get record list
    CFoxProBuffer fpBuffer("sys.dbf");
	CRecordList recordList = fpBuffer.GetRecords();
	//recordList.test();
	
	CFoxProRecord* r1 = recordList.GetAt(0);

	printf("%s\n", r1->GetString("descr"));


	return 0;
}