using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using database.structs;
using extensions;

namespace AcsNetLib.FoxPro
{
    public class FoxProBuffer
    {

        /*------------------------------------------
            | internal data and constructor |
        -------------------------------------------*/
        #region Internals

        

        private string _dbfPath;
        private byte[] _data;
        private List<Field> _fields;
        private List<Record> _records;

        private int _firstRecord;
        private int _numRecords;
        private int _recordLength;

        private bool _recover; // flag to save recovery file if client doesn't call Close()
        private string _recoveryDir;
        private string _recoveryFile;


        // constructor: save path to DBF
        public FoxProBuffer(string file)
        {
            _dbfPath = file;

            _recover = true;
            _recoveryDir = $"{System.IO.Directory.GetCurrentDirectory()}\\.recover";
            _recoveryFile = $"{Math.Abs(_dbfPath.GetHashCode())}.fprecover";
            
            Open();
        }

        // finalizer: save recovery file if Close() was not called
        ~FoxProBuffer()
        {
            if (_recover)
            {
                System.IO.Directory.CreateDirectory(_recoveryDir);
                SaveAs($"{_recoveryDir}\\RECOVER_{Util.GetFileFromPath(_dbfPath)}");
            }
        }

        //-- end of class internals --//
        #endregion Internals


        /*-----------------------------------------------------------------
            | public methods (no returns) |
            -------------------------------
              Open()
               - parse the DBF file into field and record data structures

              Close()
               - signal an intentional exit
               - tells the library that we don't need to save a recovery file

              Save()
               - overwrite DBF file with changes

              SaveAs(string fileName)
               - write changes to a new DBF file (useful for testing)
        -------------------------------------------------------------------*/
        #region Public Methods

        //-------------------------------------
        // Open: store file data in _data array
        public void Open()
        {
            // check if a recovery file exists
            if (System.IO.File.Exists($"{_recoveryDir}\\{_recoveryFile}"))
            {

            }

            _data = System.IO.File.ReadAllBytes(_dbfPath);
            _fields = ReadFieldsFromDBF(_data);
            _records = ReadRecordsFromDBF(_data, _fields.ToArray());
        }

        //-------------------------------------------------
        // Close: intentional exit, unset recovery flag
        public void Close()
        {
            _recover = false;
        }

        //----------------------------------------------------------------
        // Save() - save changes to default DBF file
        // SaveAs(string) - client specifies where to save changes
        public void Save()
        {
            WriteBufferToDisk(_dbfPath);
        }

        public void SaveAs(string fileName)
        {
            WriteBufferToDisk(fileName);
        }

        

        //---------------------------------------------------------------
        // Property: access records from DBF
        // allows adding records by doing aBuffer.Records.Add(aRecord)
        public List<Record> Records => _records;

        //-----------------------------------
        // Property: access fields from DBF
        public List<Field> Fields => _fields;

        //-- end of public methods --//
        #endregion Public Methods


        /*------------------------------------------------------------------------------------
            | private methods |
            -------------------
              ReadFieldsFromDBF(byte[] data) => return List<Field>
               - returns a list containing the fields in the DBF

              ReadRecordsFromDBF(byte[] data, Field[] fields = null) => return List<Record>
               - returns a list containing the records in the DBF

              WriteBufferToDisk(string outFile) (no return)
               - writes all record data to 'outFile' on disk
               - used by public methods Save and SaveAs
        ------------------------------------------------------------------------------------*/
        #region Private Methods

        //------------------------------------------------------
        // get the fields from the DBF 
        private List<Field> ReadFieldsFromDBF(byte[] data)
        {
            // store the fields in a list while we read them
            List<Field> fields = new List<Field>();

            // read the field headers (info to fill Field structure)
            // each header is 32 bytes long
            // data[cursor] == 0x0D indicates end of field headers,
            //  so end the loop there
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
        private List<Record> ReadRecordsFromDBF(byte[] data, Field[] fields = null)
        {
            if (fields == null) fields = ReadFieldsFromDBF(data).ToArray();

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
                Record rec = new Record();

                // get the deleted flag
                // true if data[cursor] is an asterisk
                rec.Deleted = (data[cursor] == (byte) '*');

                // loop for each field to build the record structure
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

        //-----------------------------------------------------------------------------
        // save changes to disk
        //  - move record data in memory back to DBF format and write it to the disk
        private void WriteBufferToDisk(string outFile)
        {
            // need to work with a mutable data structure in case records were added/removed
            bool sizeChanged = (_records.Count != _numRecords);
            var dataTable = new Dictionary<int, byte>();
            for (int i = 0; i < _firstRecord; i++)
                dataTable[i] = _data[i];

            // if records were added or removed, update the record count in the DBF
            // DBF stores number of records as a little-endian 32 bit (4 byte) integer
            //  - https://en.wikipedia.org/wiki/Endianness
            if (sizeChanged)
            {
                int start_position = 4;
                int length = 4;
                for (int i = 0; i < length; i++)
                {
                    dataTable[start_position + i] = (byte)(
                        (_records.Count >> (8 * i)) & 0xFF
                        );
                }
                _numRecords = _records.Count;
            }

            // place cursor at first record of DBF
            int cursor = _firstRecord;

            // iterate through each record
            foreach (var rec in Records)
            {
                // set the delete flag
                dataTable[cursor] = (byte) ((rec.Deleted) ? '*' : ' ');

                // individual field data from record
                // Record object is indexed by field name (string)
                foreach (var field in Fields)
                {
                    var data = rec[field.Name];
                    for (int i = 0; i < field.Length; i++)
                    {
                        dataTable[cursor + i + field.Offset] = data[i];
                    }
                }
                cursor += _recordLength;
            }

            // update the internal data model
            _data = dataTable.Values.ToArray();

            // save file; allow client to specify a new output file through SaveAs method
            System.IO.File.WriteAllBytes(outFile, _data);
        }

        //-- end of private methods --//
        #endregion Private Methods

    }
}
