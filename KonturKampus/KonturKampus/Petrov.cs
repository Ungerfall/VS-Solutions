#region using stmt
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
#endregion

namespace KonturKampus
{
    class Petrov
    {
        static void Main(string[] args)
        {
            using (var query_text = File.OpenText("small.queries.txt"))
            using (var text = File.OpenText(("small.txt")))
            {
                text.BaseStream.Seek(0, SeekOrigin.Begin);
                string[] st = text.ReadToEnd().Split('\n');

                string query;
                int limit = 0;
                while ((query = query_text.ReadLine()) != null)
                {
                    Console.WriteLine("Запрос: {0}", query);
                    Console.Write("Ответ: ");
                    int line_number = 0;
                    string answer = "";
                    foreach (string item in st)
                    {
                        if (limit == 19)
                        {
                            limit = 0;
                            break;
                        }
                        if (Contains(item.ToUpper(), correct_query(query)))
                        {
                            answer += line_number + ", ";
                            limit++;
                        }
                        line_number++;
                    }
                    Console.WriteLine((answer.Length > 0) ? answer.Remove(answer.Length - 2) : "");
                }
                
            }
            Console.ReadKey();
        }

        static List<string> correct_query(string st)
        {
            return st.Replace('\r', ' ').Split(' ', '\t').Distinct().ToList();
        }

        static bool Contains(string text, List<string> query)
        {
            bool ret = true;
            foreach (var item in query)
            {
                if (!text.Contains(item.ToUpper()))
                    return false;
            }
            return ret;
        }
    }
}
