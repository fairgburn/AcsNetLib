#include <stdio.h>
#include "FoxPro.NET.h"

using namespace AcsNetLib::FoxPro;

int main()
{
    // create buffer and get record list
    CFoxProBuffer fpBuffer("sys.dbf");
	CRecordList recordList = fpBuffer.GetRecords();

	// example looping through all records
	// record_list.Length() and fpBuffer.NumRecords() are interchangeable
	for (int i = 0; i < recordList.Length(); i++) {
		CFoxProRecord current_record = recordList.GetAt(i); // will implement record_list[i] soon

		// do something with current_record// BOOKMARK
		if (current_record.Get("maxlen"))
			printf("Line %s is 120 inches wide", current_record.Get("descr"));
	}

	// creating a new record
	// always use this method to make a new record, do not create your own because
	// RecordFactory() sets the length of the data in the new record based on the dbf field data
	// It also can take a char as a parameter to define what char will fill an "empty" record (default: space ' ')
	CFoxProRecord new_record = fpBuffer.RecordFactory();
	// or (to make empty values fill with nulls): fpBuffer.RecordFactory('\0');

	// set data in the record; for example:
	new_record.Set("maxlen", "120"); // maxlen is set to 120, all other values are empty

	// add the record to the buffer
	fpBuffer.AddRecord(new_record);

	// save to the disk
	fpBuffer.Save();

	return 0;
}