using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using database.structs;
using extensions;

namespace database
{
    public class FoxProBuffer
    {
        private string _filePath;
        private byte[] _data;
        private List<Field> _fields;
        private List<Record> _records;

        private int _firstRecord;
        private int _numRecords;
        private int _recordLength;


        /** constructor: save path to DBF **/
        public FoxProBuffer(string file)
        {
            _filePath = file;
        }


        /*****************************/


        //-------------------------------------
        // Open: store file data in _data array
        public void Open()
        {
            _data = System.IO.File.ReadAllBytes(_filePath);
            _fields = GetFieldsFromDBF(_data);
            _records = GetRecordsFromDBF(_data, _fields.ToArray());
        }

        //------------------------------
        // write buffer to disk
        public void Save()
        {
            int cursor = _firstRecord;

            // iterate through each record
            foreach (var rec in Records)
            {
                // individual field data from record
                foreach (var field in Fields)
                {
                    // data: rec[field.Name]
                    var data = rec[field.Name];
                    for (int i = 0; i < field.Length; i++)
                    {
                        _data[cursor + i + field.Offset] = data[i];
                    }
                }
                cursor += _recordLength;
            }
            System.IO.File.WriteAllBytes("test.dbf", _data);
        }

        //-------------------------------
        // Update a record
        public void Update(Record rec, string field, string val)
        {
            rec.Set(field, val);
        }

        //___________________________
        // access records from DBF
        public List<Record> Records => _records;

        //_____________________________
        // access fields from DBF
        public List<Field> Fields => _fields;




        /*--------------------------*/
        // helper methods
        /*--------------------------*/

        //------------------------------------------------------
        // get the fields from the DBF 
        private List<Field> GetFieldsFromDBF(byte[] data)
        {
            // store the fields in a list while we read them
            List<Field> fields = new List<Field>();

            // read the field subrecords (info to fill Field structure)
            for (int cursor = 32; data[cursor] != 0x0D; cursor += 32)
            {
                var name = data.SubRange(cursor, 10).ToUTF8().ToLower();
                var type = (char)data[cursor + 11];
                var offset = data.SubRange(cursor + 12, 4).ToInt();
                var length = data[cursor + 16];

                // push this field to the list
                fields.Add(new Field(name, type, offset, length));

            }

            // return fields as array
            return fields;
        }

        //------------------------------------------------------
        // get the records from the DBF
        private List<Record> GetRecordsFromDBF(byte[] data, Field[] fields = null)
        {
            if (fields == null) fields = GetFieldsFromDBF(data).ToArray();

            // info about records from DBF header
            _firstRecord = data.SubRange(8, 2).ToInt();
            _numRecords = data.SubRange(4, 4).ToInt();
            _recordLength = data.SubRange(10, 2).ToInt();

            // move cursor to first record
            int cursor = _firstRecord;

            // load all the records to a list
            List<Record> records = new List<Record>();

            // loop for each record
            for (int i = 0; i < _numRecords; i++)
            {
                // record we're about to assemble
                Record rec = new Record(fields.Length);

                // loop for each field
                foreach (var field in fields)
                {
                    // index of the first byte of the record
                    int start = cursor + field.Offset;

                    // store the data for this field as a byte array
                    rec[field.Name.ToLower()] = data.SubRange(start, field.Length);
                    
                }

                // append the record to the list and move cursor to the next record
                records.Add(rec);
                cursor += _recordLength;
            }

            // return the list of records as an array
            return records;
        }

    }
}
