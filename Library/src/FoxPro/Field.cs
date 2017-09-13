using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AcsNetLib.FoxPro
{
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
}
