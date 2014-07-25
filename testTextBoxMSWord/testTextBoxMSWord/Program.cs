using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using Microsoft.Office.Interop.Word;

namespace testTextBoxMSWord
{
    class Program
    {
        static void Main()
        {
            const String documentLocation = @"D:\textTextBoxMSWord.docx";
            const String findText = "Foobar";
            const String replaceText = "Woo";

            FindReplace(documentLocation, findText, replaceText);
        }

        private static void FindReplace(String documentLocation, string findText, string replaceText)
        {
            var app = new Application();
            var doc = app.Documents.Open(documentLocation);

            var range = doc.Range();

            range.Find.Execute(FindText: findText, Replace: WdReplace.wdReplaceAll, ReplaceWith: replaceText);

            var shapes = doc.Shapes;

            foreach (Shape shape in shapes)
            {
                var initialText = shape.TextFrame.TextRange.Text;
                var resultingText = initialText.Replace(findText, replaceText);
                shape.TextFrame.TextRange.Text = resultingText;
            }

            doc.Save();
            doc.Close();

            Marshal.ReleaseComObject(app);
        }
    }
}
