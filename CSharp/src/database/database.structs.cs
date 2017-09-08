/***************** data structures ********************/
// DBF files use fields and records.
// SQL equivalents are columns and rows.
// Extension methods are defined in Extensions.cs

using System.Collections.Generic;
using System.Collections.Specialized;
using System.Windows.Forms;

using extensions;

namespace database.structs
{
    ///
    /// DBF data structures
    /// 

    //__________________________________________________________________
    // simple data structure for storing info about a DBF field
    public struct Field
    {
        public string Name;
        public char Type;
        public int Offset, Length;

        public Field(string name, char type, int offset, int length)
        {
            this.Name = name;
            this.Type = type;
            this.Offset = offset;
            this.Length = length;
        }
    }


    //__________________________________________________________________
    // data structure for storing info about a record from the DBF
    public class Record
    {
        private OrderedDictionary _data = new OrderedDictionary();

        public int Length => _data.Count;

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

		// return data as string
		public string GetString(string s)
        {
            return this[s].ToUTF8();
        }

		// return data as int
		public int GetInt(string s)
        {
            return this[s].ToInt();
        }

		// modify data in field
		public void Set(string field, string val)
        {
            byte[] new_value = new byte[this[field].Length];
            try
            {
                for (int i = 0; i < val.Length; i++)
                {
                    new_value[i] = (byte)val[i];
                } // if val is too short, new_value is filled out with 0 (null character)
            }

            // check that value isn't too long for the field
            catch (System.IndexOutOfRangeException)
            {
                var cur_method = System.Reflection.MethodBase.GetCurrentMethod();
                string errmsg = $"FoxPro: exception in Record.Set(\"{field}\", \"{val}\")\n\n" +
                                $"ERROR: value \"{val}\" is too long for field \"{field}\"\n" +
                                "Value was not changed in DBF";

                MessageBox.Show(errmsg, "Exception in AcsLib.NET.dll");
                return;
            }

            _data[field] = new_value;
        }

    }


    /// 
    /// SQL data structures
    /// 

    //__________________________________________________________________
    // DBF field represented as a SQL column
    public struct Column
    {
        public string Name;
        public string Type;

        // init SQL Column from DBF Field
        public Column(Field field)
        {
            this.Name = field.Name;

            switch (field.Type)
            {
                case 'N':
                    this.Type = "int";
                    break;

                default:
                    this.Type = "text";
                    break;
            }
        }

        public Column(string name, string type)
        {
            this.Name = name;
            this.Type = type;
        }
    }

    //__________________________________________________________________
    // DBF record represented as a SQL row
    public struct Row
    {
        private Dictionary<string, string> _data; // key: column name

        public Row(Record record, Column[] columns)
        {
            _data = new Dictionary<string, string>();

            int i = 0;
            foreach (var col in columns)
            {
                //_data[col.Name] = record[i++];

            }
        }

        // allow row[string] indexing
        public string this[string s]
        {
            get { return _data[s]; }
        }

    }
}