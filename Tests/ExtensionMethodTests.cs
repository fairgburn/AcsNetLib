using System;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using AcsLib.Extensions;


namespace AcsNetLibTests
{
    [TestClass]
    public class ExtensionMethodTests
    {
        [TestMethod]
        public void StringTests()
        {
            /** FileName method **************************/
            string filePath = @"C:\path\to\some\file.txt";
            string expectedResult = "file";
            string actualResult = filePath.FileName();

            Assert.AreEqual(expectedResult, actualResult);
            //-------------------------------------------


            /** FileExtension method *********************/
            expectedResult = "txt";
            actualResult = filePath.FileExtension();

            Assert.AreEqual(expectedResult, actualResult);
            //------------------------------------------
        }

        [TestMethod]
        public void ByteArrayTests()
        {
            /** SubRange method *******************************************/
            byte[] sample1 = { 49, 43, 85, 92, 87, 67, 100, 255, 96 };
            byte[] expectedResult1 = { 85, 92, 87 };
            byte[] actualResult1 = sample1.SubRange(2, 3);

            // check lengths are equal
            Assert.AreEqual(expectedResult1.Length, actualResult1.Length);

            // check contents are equal
            for (int i = 0; i < expectedResult1.Length; i++)
            {
                Assert.AreEqual(expectedResult1[i], actualResult1[i]);
            }
            //-------------------------------------------------------------


            /** ToUTF8 method **********************************************************/
            byte[] sample2 = { (byte)' ', (byte)'t', (byte)'e', (byte)'s', (byte)'t' };
            string expectedResult2 = "test";
            string actualResult2 = sample2.ToUTF8();

            Assert.AreEqual(expectedResult2, actualResult2);
            //----------------------------------------------------------------------------


            /** ToUTF8NoTrim method **********************************************/
            string expectedResult3 = " test";
            string actualResult3 = sample2.ToUTF8NoTrim();

            Assert.AreEqual(expectedResult3, actualResult3);
            //----------------------------------------------------------------------

        }
    }
}
