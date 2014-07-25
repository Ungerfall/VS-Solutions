using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OperatingSystemContest_6_MemoryManage
{
    class Program
    {
        static void Main(string[] args)
        {
            int M, N;
            int[] Arr;

            var st = Console.ReadLine().Split(' ');
            N = int.Parse(st[0]);
            M = int.Parse(st[1]);

            Arr = new int[N];

            for (int i = 0; i < N; i++)
            {
                Arr[i] = int.Parse(Console.ReadLine());
            }
        }
    }
}
