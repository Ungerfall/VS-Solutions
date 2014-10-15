using System;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using System.Xml.Serialization;
using Newtonsoft.Json;

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
            public Output()
            {
                SumResult = SumResult;
                MulResult = MulResult;
                SortedInputs = SortedInputs;
            }
            public Output(Input input)
            {
                SumResult = input.Sums.Sum()*input.K;
                MulResult = input.Muls.Aggregate(1, (a, b) => a*b);
                SortedInputs = input.Sums.Concat(input.Muls.Select(Convert.ToDecimal)).OrderBy(t => t).ToArray();
            }
            public decimal SumResult { get; set; }
            public int MulResult { get; set; }
            public decimal[] SortedInputs { get; set; }
        }
        
        static void Main()
        {
            Input input;
            Output output;
            var sType = Console.ReadLine();
            var text = Regex.Replace(Console.In.ReadToEnd(), @"\s+", string.Empty);
            if (sType == "Xml")
            {
                var xmlSerializer = new XmlSerializer(typeof(Input));
                using (var stream = new MemoryStream(Encoding.UTF8.GetBytes(text)))
                    input = (Input) xmlSerializer.Deserialize(stream);
                output = new Output(input);
                xmlSerializer = new XmlSerializer(typeof(Output));
                using (var xmlWriter = XmlWriter.Create(Console.Out, new XmlWriterSettings {OmitXmlDeclaration = true}))
                    xmlSerializer.Serialize(xmlWriter, output, new XmlSerializerNamespaces(new[] {XmlQualifiedName.Empty}));
            }
            else
            {
                input = JsonConvert.DeserializeObject<Input>(text);
                output = new Output(input);
                Console.Write(JsonConvert.SerializeObject(output));
            }
        }
    }
}