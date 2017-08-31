/**
 * SQLite class
 * 
 * Represents a connection to a SQLite database file 
 * and provides methods for manipulating it.
 * 
 **/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.SQLite;

namespace SQLite_CS
{
    public class SQLiteDatabase
    {
        /** internal data **/

        private SQLiteConnection _conn;
        private string _database;
        private bool _isOpen = false;


        /** constructor **/

        public SQLiteDatabase(string file)
        {
            _database = file;
        }


        /** API **/


        /* open the connection, create .sqlite file if necessary */
        public void Open()
        {
            if (_isOpen) return;

            // make sure the database file and directory exist
            if (!System.IO.File.Exists(_database))
            {
                System.IO.Directory.CreateDirectory(Util.GetDirectoryFromPath(_database));
                SQLiteConnection.CreateFile(_database);
            }

            var connection_string = $"Data Source={_database};Version=3;";

            _conn = new SQLiteConnection(connection_string);
            _conn.Open();

            _isOpen = true;
        }

        /* close the connection */
        public void Close()
        {
            if (!_isOpen) return;

            _conn.Close();
            _isOpen = false;
        }

        /* execute and get results */
        public SQLiteDataReader ExecuteReader(string q)
        {
            var cmd = new SQLiteCommand(q, _conn);

            return cmd.ExecuteReader();
        }

        /* execute, don't need result set */
        public int Execute(string command)
        {
            //Console.WriteLine(q);
            var cmd = new SQLiteCommand(command, _conn);

            try
            {
                return cmd.ExecuteNonQuery();
            }
            catch (Exception e)
            {
                Console.WriteLine(e);
                return -1;
            }
        }

        /* execute a batch of commands in a transaction */
        public void ExecuteBatch(string[] commands)
        {
            using (var trans = _conn.BeginTransaction())
            {
                try
                {
                    foreach (var cmd in commands)
                    {
                        Execute(cmd);
                    }
                    trans.Commit();
                }
                catch (Exception e)
                {
                    trans.Rollback();
                    Console.WriteLine($"ERROR: \n{e}");
                    throw;
                }
            }
        }

    }
}
