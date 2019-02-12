using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;

namespace TIme
{
    class Program
    {
        [DllImport("Lab1.dll", EntryPoint = "TimeForCSharp")]
        public static extern void TimeForCSharp();

        [STAThread]
        static void Main(string[] args)
        {
            TimeForCSharp();
            Console.ReadLine();
        }

    }
}
