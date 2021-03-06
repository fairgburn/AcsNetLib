﻿/*
 * Extensions.cs
 * 
 * General extension methods - see https://docs.microsoft.com/en-us/dotnet/csharp/programming-guide/classes-and-structs/extension-methods
 * 
 */

using System.Collections.Generic;
using System.Linq;

//using AcsLib.Database;

namespace AcsLib.Extensions
{
    public static class Extensions
    {

        /*************** strings **************/
        #region strings

        //_________________________________
        // return file name
        public static string FileName(this string path)
        {
            var file = path.Split('\\').Last();
            var file_split = file.Split('.');
            var name = file_split.First();

            return name;
        }

        //______________________________________
        // return file extension
        public static string FileExtension(this string path)
        {
            var file = path.Split('\\').Last();
            var file_split = file.Split('.');
            var ext = file_split.Last();

            return ext;
        }

        #endregion strings


        /************ byte arrays **************/
        #region byte arrays

        /** get a sub-range from the larger array **/
        public static byte[] SubRange(this byte[] bytes, int start, int count)
        {
            return (from i in Enumerable.Range(start, count) select bytes[i]).ToArray();
        }
        //______________________________________________________


        /** get a UTF-8 string from an array of bytes **/
        public static string ToUTF8(this byte[] bytes)
        {
            return System.Text.Encoding.UTF8.GetString(bytes)
                .Trim()             // ignore leading and trailing whitespace
                .Replace("\0", ""); // remove null chars
        }
        //____________________________________________________________


        /** same as above but don't trim whitespace and nulls **/
        public static string ToUTF8NoTrim(this byte[] bytes)
        {
            return System.Text.Encoding.UTF8.GetString(bytes);
        }

        /** get an int from an array of bytes **/
        public static int ToInt(this byte[] bytes)
        {
            // least significant byte first
            int result = 0;
            for (int i = 0; i < bytes.Length; i++)
            {
                result = result | (bytes[i] << (8 * i));
            }

            return result;
        }
        //_________________________________________________________

        #endregion byte arrays

        // BSF 9/20/2017 - removing SQL extensions until 
        //   everyone upgrades to Visual Studio 2017 because
        //   VS2012 doesn't support current C# code

        /*************** DBF and SQL structures ******************/
        #region database structures 
        ///
        /// DBF Field
        ///


        //_________________________________________________
        // Field to SQL Column
        /*public static Column ToColumn(this AcsLib.FoxPro.Field self)
        {
            return new Column(self);
        }*/

        //_____________________________________________________
        // enumerate columns from an array of fields
        /*public static IEnumerable<Column> ToColumns(this AcsLib.FoxPro.Field[] self)
        {
            foreach (var field in self)
            {
                yield return field.ToColumn();
            }
        }*/


        ///
        /// DBF Record
        ///


        //________________________________________
        // Record to SQL Row
        /*public static Row ToRow(this AcsLib.FoxPro.Record self, Column[] columns)
        {
            return new Row(self, columns);
        }*/


        //________________________________________
        // enumerate rows from array of records
        // receive the columns as a parameter
        /*public static IEnumerable<Row> ToRows(this AcsLib.FoxPro.Record[] self, Column[] columns)
        {
            foreach (var record in self)
            {
                yield return new Row(record, columns);
            }
        }*/

        #endregion database structures

    }
}
