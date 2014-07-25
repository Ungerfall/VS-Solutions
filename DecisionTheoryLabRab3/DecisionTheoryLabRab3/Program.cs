using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Excel = Microsoft.Office.Interop.Excel;

namespace DecisionTheoryLabRab3
{
    public struct LentochniiGrafik
    {
        public string Task;
        public string Doer;
        public DateTime From;
        public DateTime Till;
    }
    class Program
    {
        static void _Print(List<LentochniiGrafik> lg)
        {            
            DateTime max = lg[0].Till;
            DateTime min = lg[0].From;

            for (int i = 0; i < lg.Count; i++)
            {
                if (lg[i].From < min)
                    min = lg[i].From;
                if (lg[i].Till > max)
                    max = lg[i].Till;
            }
            var result = max - min;
            Console.WriteLine("Работы   | Исполнители             | Срок: С " + min.ToShortDateString() + " до " + max.ToShortDateString());
            Console.WriteLine("---------|-------------------------|-------------------------------------------");
            for (int i = 0; i < lg.Count; i++)
            {
                int probeli = (int)(((float)(lg[i].From - min).Days / (float)result.Days) * 43);
                int konec = (int)(((float)(lg[i].Till - lg[i].From).Days / (float)result.Days) * 43);
                Console.WriteLine((lg[i].Task.PadRight(9).Substring(0, 9) + "| " + lg[i].Doer.PadRight(24).Substring(0, 24) + "| " + new string(' ', probeli) + new string('*', konec)));
            }
            Console.WriteLine("\nПримечание: 1 символ = {0:0.0} дн", ((float)result.Days / 43));
        }
        static void Main(string[] args)
        {
            List<LentochniiGrafik> LG = new List<LentochniiGrafik>();
            LG.Add(new LentochniiGrafik() { Task = "Design", Doer = "Fatih, Anton, Tigran", From = new DateTime(2014, 2, 25), Till = new DateTime(2014, 3, 12) });
            LG.Add(new LentochniiGrafik() { Task = "Code", Doer = "Leonid, Vitaliy", From = new DateTime(2014, 2, 28), Till = new DateTime(2014, 3, 14) });
            LG.Add(new LentochniiGrafik() { Task = "Advertising", Doer = "P.P.Lugachev", From = new DateTime(2014, 1, 28), Till = new DateTime(2014, 3, 12) });
            _Print(LG);
            Console.ReadKey();
        }
        
        static void ExportExcell()
        {
            Excel.Application excelapp = new Excel.Application();
        }
    }
}
