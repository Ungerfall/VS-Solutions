using System;
using System.Linq;
using System.Text;
using System.Xml.Serialization;
using System.IO;
using System.Web.Script.Serialization;

namespace SOASerialization
{
    public class Program
    {
        public class Input
        {
            public int K { get; set; }
            public decimal[] Sums { get; set; }
            public int[] Muls { get; set; }
        }

        public class Output
        {
            public decimal SumResult { get; set; }
            public int MulResult { get; set; }
            public decimal[] SortedInputs { get; set; }
        }
        
        static void Main(string[] args)
        {    
            XmlSerializer xmlSerializer;
            JavaScriptSerializer jsSerializer;
            Input input;
            Output output;

            if (Console.ReadLine() == "Xml")
            {
                xmlSerializer = new XmlSerializer(typeof(Input));
                input = xmlSerializer.Deserialize(Console.In) as Input;
                output = new Output()
                {
                    SumResult = input.Sums.Sum() * input.K,
                    MulResult = input.Muls.Aggregate(1, (a, b) => a * b),
                    SortedInputs = input.Sums.Concat(input.Muls.Select(x => Convert.ToDecimal(x))).OrderBy(t => t).ToArray()
                };
                xmlSerializer.Serialize(Console.Out, output);
            }
            else
            {
                jsSerializer = new JavaScriptSerializer();
                input = jsSerializer.Deserialize<Input>(Console.In.ToString());
                output = new Output()
                {
                    SumResult = input.Sums.Sum() * input.K,
                    MulResult = input.Muls.Aggregate(1, (a, b) => a * b),
                    SortedInputs = input.Sums.Concat(input.Muls.Select(x => Convert.ToDecimal(x))).OrderBy(t => t).ToArray()
                };
                Console.Write(jsSerializer.Serialize(output));
            }
        }
    }
}
