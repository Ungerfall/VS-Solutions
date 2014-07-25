using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using System.Net;
using System.Text.RegularExpressions;

namespace CallToGoogle
{
    class Program
    {
        static void Main(string[] args)
        {
            using (WebClient client = new WebClient())
            {
                Regex re = new Regex("<h3 class=\"r\">(.*?)<\\/h3>", RegexOptions.Multiline);
                Console.WriteLine("Enter string");
                string str = Console.ReadLine();
                var content = client.DownloadString("http://google.com/search?q=" + str);
                var txt = re.Matches(content);
                foreach (Match item in txt)
                {
                    Console.WriteLine(item.Groups[1].Value);
                }
                Console.ReadKey();
            }
        }
    }
}
