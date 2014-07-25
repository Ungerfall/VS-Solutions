using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Torchlight_II_save_comparison
{
    class Program
    {
        static void Main(string[] args)
        {
            using (BinaryReader br_first = new BinaryReader(File.Open("1st.tmp", FileMode.Open)))
            using (BinaryReader br_second = new BinaryReader(File.Open("2nd.svb", FileMode.Open)))
            using (StreamWriter answer = new StreamWriter(@"answer.txt"))
            {
                int pos = 0;
                int length = (int)br_first.BaseStream.Length;
                while (pos < length)
                {
                    var first = br_first.ReadByte();
                    var snd = br_second.ReadByte();
                    if (first != snd)
                        answer.WriteLine(pos + "\t" + first + "   " + snd);
                    pos += sizeof(int);
                }
            }
        }
    }
}
