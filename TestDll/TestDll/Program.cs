using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace TestDll
{
    class MathFuncs
    {
        [DllImport("testctoc.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double Add(double a, double b);

        [DllImport("testctoc.dll", CallingConvention = CallingConvention.Cdecl)]
	    public static extern double Subtract(double a, double b);

        [DllImport("testctoc.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern double Multiply(double a, double b); 

        [DllImport("megalib1.dll", EntryPoint = "_CHGetInLine", CallingConvention = CallingConvention.Cdecl)]
        public static extern uint CHGetInLine(uint Line);
    }
    class Program
    {
        static void Main(string[] args)
        {
            Console.Out.WriteLine(MathFuncs.CHGetInLine(4));
            Console.ReadKey();
        }
    }
}
