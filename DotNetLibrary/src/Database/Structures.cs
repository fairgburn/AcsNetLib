/***************** data structures ********************/
// DBF files use fields and records.
// SQL equivalents are columns and rows.
// Extension methods are defined in Extensions.cs

using System.Collections.Generic;
using System.Collections.Specialized;
using System.Windows.Forms;
using System.Linq;

using extensions;

namespace AcsLib.Database
{
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
        public Column(FoxPro.Field field)
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

        public Row(FoxPro.Record record, Column[] columns)
        {
            _data = new Dictionary<string, string>();

            /*int i = 0;
            foreach (var col in columns)
            {
                //_data[col.Name] = record[i++];

            }*/
        }

        // allow row[string] indexing
        public string this[string s]
        {
            get { return _data[s]; }
        }

    }
}