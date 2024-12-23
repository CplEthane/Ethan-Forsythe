using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Timers;
using System.Diagnostics;

namespace _2DGameEngine
{
    class Text
    {
        static string textline1, textline2, textline3, textlineTemp;
        static int stringiter;
        int stringlength;

        Stopwatch textsp = new Stopwatch();

        Text()
        {
            stringiter = 0;
        }


        public static void displayText()
        {
           
            if (stringiter <= stringlength && textsp.ElapsedMilliseconds > 50)
            {

                textlineTemp = textline1;
                textlineTemp = Truncate(textlineTemp, stringiter);
                stringiter++;
                
            }
            
        }

        public static string Truncate(string source, int length)
        {
            if (source.Length > length)
            {
                source = source.Substring(0, length);
            }
            return source;
        }
    }
}
