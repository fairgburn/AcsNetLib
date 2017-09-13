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
        private OrderedDictionary _data;

        //-----------------------------
        // copy this record
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

        // default constructor
        public Record() { _data = new OrderedDictionary(); }

        public int Length => _data.Count;
        public bool Deleted = false;

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

        /*-------------------------------
         * Getters
         * -----------------------------*/

        // return data as raw byte array (index by order in hashtable or field name)
        public byte[] Get(int index) { return this[index]; }
        public byte[] Get(string fieldName) { return this[fieldName]; }

        // return data as string
        public string GetString(int index) { return this[index].ToUTF8(); }
        public string GetString(string s) { return this[s].ToUTF8(); }

        // modify data in field
        public void Set(string field, string val)
        {
            byte[] new_value = new byte[this[field].Length];
            try
            {

                for (int i = 0; i < new_value.Length; i++)
                {
                    new_value[i] = (byte)val[i];
                } // if val is too short, new_value is filled out with 0 (null character)
            }

            // check that value isn't too long for the field
            catch (System.IndexOutOfRangeException)
            {
                // input value shorter than field length; take no action
                // results in: new_value[x] equals 0 (null) where x is out of range for val
            }

            _data[field] = new_value;
        }

    }
}
