using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Visio = Microsoft.Office.Interop.Visio;

namespace TestVisio
{
    class Program
    {
        public static Visio.Application VisioApp;
        public static Visio.Document VisioDoc;

        static void Main(string[] args)
        {
            
            VisioApp = new Visio.Application();            
            VisioDoc = VisioApp.Documents.Add("");
            
            
        }
    }
}
