using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using extensions;

namespace AcsNetLib.FoxPro
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
        public Record()
        {
            _data = new OrderedDictionary();
        }

        // data from DBF
        private OrderedDictionary _data;

        // byte used to fill empty records and pad client inputs that are too short (default: space)
        // set by FoxProBuffer.RecordFactory()
        public byte DefaultFill { get; set; } = (byte)' ';

        public bool Deleted { get; set; } = false;
        public int Length => _data.Count;

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

    }
}
