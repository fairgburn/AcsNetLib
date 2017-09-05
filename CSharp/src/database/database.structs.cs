/***************** data structures ********************/
// DBF files use fields and records.
// SQL equivalents are columns and rows.
// Extension methods are defined in Extensions.cs

using System.Collections.Generic;
using System.Collections.Specialized;

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
    public struct Record
    {
        private OrderedDictionary _data;

        public int Length => _data.Count;

        // initialize with a number of fields
        public Record(int numberOfFields)
        {
            _data = new OrderedDictionary();
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
			for (int i = 0; i < val.Length; i++)
            {
                new_value[i] = (byte)val[i];
            } // if val is too short, new_value is filled out with 0 (null character)

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