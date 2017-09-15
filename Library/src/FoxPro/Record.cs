using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using extensions;

namespace AcsLib.FoxPro
{
    //__________________________________________________________________
    // data structure for storing info about a record from the DBF
    public class Record
    {
        /*-----------------------
            internal data
        ------------------------*/
        #region internal

        // default constructor
        public Record() { _data = new OrderedDictionary(); }

        // data from DBF
        private OrderedDictionary _data;

        // field info
        private List<Field> _fields;
        public List<Field> Fields
        {
            get { return _fields; }
            set { _fields = value; }
        }

        // byte used to fill empty records and pad client inputs that are too short (default: space)
        // set by FoxProBuffer.RecordFactory()
        public byte DefaultFill { get; set; } = (byte)' ';

        // DBF deleted flag
        public bool Deleted { get; set; } = false;

        // length of record in bytes
        public int Length
        {
            get
            {
                int len = 0;
                foreach (var field in _fields)
                {
                    len += field.Length;
                }
                return len;
            }
        }

        //-------------------------------------------------
        // copy this record using a private contructor
        public Record Copy() { return new Record(_data); }
        private Record(OrderedDictionary d)
        {
            _data = new OrderedDictionary();
            foreach (var key in d.Keys)
            {
                // copy the bytes from original record to clone record
                var original_val = (byte[])d[key];
                var clone_val = (from i in Enumerable.Range(0, original_val.Length)
                                 select original_val[i])
                                 .ToArray();
                _data[key] = clone_val;
            }
        }

        // allow for record[index] notation
        public byte[] this[int i]
        {
            get { return (byte[])_data[i]; }
            set { _data[i] = value; }
        }

        // allow for record[key] notation
        public byte[] this[string s]
        {
            get { return (byte[])_data[s]; }
            set { _data[s] = value; }
        }

        //___________________
        #endregion internal

        /*-------------------------------
         * Get data
         * -----------------------------*/

        // return data as raw byte array (index by order in hashtable or field name)
        public byte[] Get(int index) { return this[index]; }
        public byte[] Get(string fieldName) { return this[fieldName]; }

        // return data as string
        public string GetString(int index) { return this[index].ToUTF8(); }
        public string GetString(string s) { return this[s].ToUTF8(); }

        // return data a single byte array
        public byte[] GetBlob()
        {
            var result = new List<byte>();

            // each byte[] in data
            foreach (var objbytes in _data.Values)
            {
                var bytes = (byte[])objbytes;
                // each individual byte in the field
                foreach (var b in bytes)
                {
                    result.Add(b);
                }
            }

            return result.ToArray();
        }


        /*------------------------------
         * Set data
         * -----------------------------*/

        // modify data in field
        public void Set(string field, string val)
        {
            // create byte array for the new value
            byte[] new_value = new byte[this[field].Length];
            for (int i = 0; i < new_value.Length; i++)
            {
                // copy bytes from string parameter
                // if input is too long, extra bytes are ignored
                // if input is too short, catch the exception 
                try { new_value[i] = (byte)val[i]; }
                catch (System.IndexOutOfRangeException) { break; }
            } // if val is too short, new_value is filled out with 0 (null character)
            

            _data[field] = new_value;
        }

        // modify whole record at once
        public void SetBlob(byte[] blob)
        {
            var new_data = new OrderedDictionary();

            try
            {
                foreach (var field in _fields)
                {
                    new_data[field.Name] =  blob.SubRange(field.Offset, field.Length);
                }

                _data = new_data;
            }

            // if an exception is caught, throw it out to the caller and let them handle it
            catch { throw; }
        }

    }
}
