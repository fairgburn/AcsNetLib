using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using AcsLib.FoxPro;

namespace T_csharp
{
    class Program
    {
        static void Main(string[] args)
        {
            FoxProBuffer fp = new FoxProBuffer("sys.dbf");
            Record r1 = fp.RecordFactory();
            Record r2 = fp.RecordFactory();

            r1.Set("descr", "aaa");
            r2.Set("descr", "bbb");

            fp.Records.Add(r1);
            fp.Records.Add(r2);

            fp.SaveAs("out.dbf");
            fp.Close();
            return;
        }
    }
}
