using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using AcsLib.FoxPro;

namespace T_csharp
{
    class CSharpTest
    {
        static void Main(string[] args)
        {
            // create buffer and get first two records
            FoxProBuffer fp = new FoxProBuffer("sys.dbf");
            var firstRecord = fp.Records[0];
            var secondRecord = fp.Records[1];

            // get complete record data (byte array in C#, unsigned char* in C++)
            byte[] r1_bytes = firstRecord.GetCompleteRecord();
            byte[] r2_bytes = secondRecord.GetCompleteRecord();

            // change line name in first 2 records to LN1 and LN2, clear out rest of the record (spaces)
            string r1_newdata = "LN1";
            while (r1_newdata.Length < r1_bytes.Length) r1_newdata += ' ';

            string r2_newdata = "LN2";
            while (r2_newdata.Length < r2_bytes.Length) r2_newdata += ' ';

            // set complete record with new data
            // method takes byte array as parameter, so convert the string (see extension method below)
            // (data conversion handled automatically in the C++ wrapper since byte array isn't a native type)
            firstRecord.SetCompleteRecord(r1_newdata.ToByteArray());
            secondRecord.SetCompleteRecord(r2_newdata.ToByteArray());

            // write buffer to test.dbf on disk
            fp.SaveAs("test.dbf");
            
            return;
        }
    }


    // C# allows adding new methods to existing classes without modifying the original class
    // https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/classes-and-structs/extension-methods
    //
    // For example: extending strings with a method to convert themselves to a byte array
    // Overkill for this example, but useful to know
    public static class Extensions
    {
        // extending strings for byte array conversion
        public static byte[] ToByteArray(this string self)
        {
            var bytes = from i in Enumerable.Range(0, self.Length) select (byte)self[i];
            // above line is shorthand for the following:
            //
            // byte[] bytes = new byte[self.Length];
            // for (int i = 0; i < self.Length; i++) {
            //     bytes[i] = (byte)self[i];
            // }
            //
            // ex: "abc" becomes {0x61, 0x62, 0x63}

            return bytes.ToArray();
        }
    }
}