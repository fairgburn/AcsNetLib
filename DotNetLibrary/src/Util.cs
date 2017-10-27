/**********************************************************
 * Util.cs
 * 
 * - General utility functions used throughout system
 * 
 **********************************************************/

using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using System.IO;


namespace AcsLib
{
    public static class Util
    {

        //___________________________________________________
        // strip a file name out of a full path
        public static string GetFileFromPath(string path)
        {
            return path.Split('\\').Last();
        }

        //___________________________________________________________________________________________________________
        // given full path to a file, return the directory it's in
        public static string GetDirectoryFromPath(string path)
        {
            string file = GetFileFromPath(path);                        // C:\inv\invdata\file.dbf ==> file.dbf
            return path.Replace("\\" + file, string.Empty); // result ==> C:\inv\invdata (stripped out `\file.dbf`)
        }

    }
}