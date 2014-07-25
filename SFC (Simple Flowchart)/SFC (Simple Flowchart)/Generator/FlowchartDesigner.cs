using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Word = Microsoft.Office.Interop.Word;
using Microsoft.Office.Core;
using Microsoft.VisualBasic;
using System.IO;
using SFC.Forms.MainForm;
using SFC.Parser;

namespace SFC.Generator
{
    public class FlowchartDesigner
    { 
        private const float HEIGHTSHAPE = 1.2f;
        private const float WIDTHSHAPE = 2.4f;
        private const float MAXEDGESIZE = 55.87f;
        private const float DISTBETWEENSHAPES = 0.6f;
        private const int MAXSHAPESOFWIDTHONPAGE = 17;
        private const int MAXSHAPESOFHEIGHTONPAGE = 29;

        private Word.Application WordApp;
        private Word.Document WordDoc;
        private Word.Shape WordShape;
        private readonly MainWindow form = new MainWindow();

        //
        public FlowchartDesigner()
        { }

        public FlowchartDesigner(MainWindow form)
        {
            this.form = form;
        }

        public void CreateDoc()
        {
            WordApp = new Word.Application();
            Object filename = makeTempCopy("SFT.docx");
            WordDoc = WordApp.Documents.Add();
            WordDoc.SaveAs(filename);

            WordDoc.PageSetup.TopMargin = WordApp.CentimetersToPoints(0.1f);
            WordDoc.PageSetup.LeftMargin = WordApp.CentimetersToPoints(0.1f);
            WordDoc.PageSetup.RightMargin = WordApp.CentimetersToPoints(0.1f);
            WordDoc.PageSetup.BottomMargin = WordApp.CentimetersToPoints(0.1f);
        }

        private void SetPageSize(int count_of_hei, int count_of_wid)
        {
            if (count_of_wid > MAXSHAPESOFHEIGHTONPAGE)
            {
                form.ErrorBox.Text = "Ошибка. Недопустимое количество блоков по горизонтали.";
                form.ErrorBox.Visibility = System.Windows.Visibility.Visible;
            }
            else
            {
                if (count_of_hei > MAXSHAPESOFWIDTHONPAGE)
                {
                    SetPageSize(MAXSHAPESOFHEIGHTONPAGE, MAXSHAPESOFWIDTHONPAGE);
                }
                else
                {
                    SetPageSize(0.4f + count_of_hei * (HEIGHTSHAPE + DISTBETWEENSHAPES), 0.4f + count_of_wid * (WIDTHSHAPE + DISTBETWEENSHAPES));
                }
            }
        }

        public void SetPageSize(float hei, float wid)
        {
            try
            {
                WordDoc.PageSetup.PageHeight = WordApp.CentimetersToPoints(hei);
                WordDoc.PageSetup.PageWidth = WordApp.CentimetersToPoints(wid);
            }
            catch (Exception e)
            {
                form.ErrorBox.Text = e.Message;
                form.ErrorBox.Visibility = System.Windows.Visibility.Visible;
            }
        }

        private void create_new_page()
        {
            object missing = Type.Missing;
            object what = Word.WdGoToItem.wdGoToLine;
            object which = Word.WdGoToDirection.wdGoToFirst;
            WordDoc.Application.Selection.GoTo(ref what, ref which, ref missing, ref missing);
            WordDoc.Application.Selection.InsertNewPage();
            WordDoc.Application.Selection.GoToPrevious(Word.WdGoToItem.wdGoToPage);
        }

        public void complete()
        {
            WordDoc.Application.Visible = true;
        }

        private string getNewName(string path, int id)
        {
            int i = path.Length - 1;
            string extention = "";
            string filename = "";
            while (i >= 0 && path[i] != '.')
            {
                i--;
            }
            extention = path.Substring(i + 1);
            filename = path.Substring(0, i);
            return filename + "_" + id + "." + extention;
        }

        private string makeTempCopy(string orignal_name)
        {
            string newname = orignal_name;
            string newpath = "D:\\учёба\\C, C++, C#\\SFC (Simple Flowchart)\\SFC (Simple Flowchart)\\temp\\" + newname;

            var rand = new Random();
            var rand_i = 0;
            for (int i = 1; i < 100000; i++)
            {
                rand_i += rand.Next(20);
                newname = getNewName(orignal_name, rand_i);
                newpath = "D:\\учёба\\C, C++, C#\\SFC (Simple Flowchart)\\SFC (Simple Flowchart)\\temp\\" + newname;
                if (!File.Exists(newpath))
                {
                    break;
                }
            }
            return newpath;
        }

        //creating shapes 
        private float CtoP(float value)
        {
            return WordApp.CentimetersToPoints(value);
        }

        //FUNCT
        private void FunctBlock(ref float x, ref float y, string text = "")
        {
            WordShape = WordDoc.Shapes.AddShape((int)MsoAutoShapeType.msoShapeFlowchartProcess, CtoP(x), CtoP(y), CtoP(WIDTHSHAPE), CtoP(HEIGHTSHAPE));
            WordShape.TextFrame.TextRange.ParagraphFormat.Alignment = Word.WdParagraphAlignment.wdAlignParagraphCenter;
            WordShape.TextFrame.TextRange.Text = text;
            WordShape = WordDoc.Shapes.AddLine(CtoP(x + WIDTHSHAPE / 2f), CtoP(y + HEIGHTSHAPE), CtoP(x + WIDTHSHAPE / 2f), CtoP(y + HEIGHTSHAPE + DISTBETWEENSHAPES));
            y += HEIGHTSHAPE + DISTBETWEENSHAPES;
        }
        
        //START
        private void StartBlock(ref float x, ref float y, string text = "start")
        {
            WordShape = WordDoc.Shapes.AddShape((int)MsoAutoShapeType.msoShapeFlowchartTerminator, CtoP(x), CtoP(y), CtoP(WIDTHSHAPE), CtoP(HEIGHTSHAPE / 1.5f));
            WordShape.TextFrame.TextRange.ParagraphFormat.Alignment = Word.WdParagraphAlignment.wdAlignParagraphCenter;
            WordShape.TextFrame.TextRange.Text = text;
            WordShape = WordDoc.Shapes.AddLine(CtoP(x + WIDTHSHAPE / 2f), CtoP(y + HEIGHTSHAPE / 1.5f), CtoP(x + WIDTHSHAPE / 2f), CtoP(y + HEIGHTSHAPE / 1.5f + DISTBETWEENSHAPES));
            y += HEIGHTSHAPE / 1.5f + DISTBETWEENSHAPES;
        }

        //END
        private void EndBlock(float x, float y, string text = "end")
        {
            WordShape = WordDoc.Shapes.AddShape((int)MsoAutoShapeType.msoShapeFlowchartTerminator, CtoP(x), CtoP(y), CtoP(WIDTHSHAPE), CtoP(HEIGHTSHAPE / 1.5f));
            WordShape.TextFrame.TextRange.ParagraphFormat.Alignment = Word.WdParagraphAlignment.wdAlignParagraphCenter;
            WordShape.TextFrame.TextRange.Text = text;
        }

        //DECISION
        private void DecisionBlock(ref float x, ref float y, string text = "")
        {
            WordShape = WordDoc.Shapes.AddShape((int)MsoAutoShapeType.msoShapeFlowchartDecision, CtoP(x), CtoP(y), CtoP(WIDTHSHAPE), CtoP(HEIGHTSHAPE));
            WordShape.TextFrame.TextRange.ParagraphFormat.Alignment = Word.WdParagraphAlignment.wdAlignParagraphCenter;
            WordShape.TextFrame.TextRange.Text = text;
            WordShape = WordDoc.Shapes.AddLine(CtoP(x + WIDTHSHAPE), CtoP(y + HEIGHTSHAPE / 2f), CtoP(x + WIDTHSHAPE + DISTBETWEENSHAPES), CtoP(y + HEIGHTSHAPE / 2f));
            WordShape = WordDoc.Shapes.AddLine(CtoP(x + WIDTHSHAPE / 2f), CtoP(y + HEIGHTSHAPE), CtoP(x + WIDTHSHAPE / 2f), CtoP(y + HEIGHTSHAPE + DISTBETWEENSHAPES));
            y += HEIGHTSHAPE + DISTBETWEENSHAPES;
        }

        //CYCLE
        private void CycleStartBlock(ref float x, ref float y, string text = "")
        {
        }

        private void CycleEndBlock(ref float x, ref float y, string text = "")
        {

        }

        //creating flowcharts combos

        //CONDITION
        private void Condition(ref float cur_x, ref float cur_y, List<Token> list, string text)
        {
            float start_x = cur_x;
            float start_y = cur_y;
            float lower_x = 0;
            float lower_y = 0;

            DecisionBlock(ref cur_x, ref cur_y, text);
            for (int i = 0; i < list.Count; i++)
            {
                switch (list[i].TokenName)
                {
                    case "CONDITION":
                        Condition(ref cur_x, ref cur_y, list[i].TokenRef, list[i].BlockText);
                        break;
                    case "ELSE":
                        lower_x = cur_x;
                        lower_y = cur_y;
                        if (list[i + 1].TokenName == "CONDITIONEND")
                        {
                            WordShape = WordDoc.Shapes.AddLine(CtoP(start_x + WIDTHSHAPE + DISTBETWEENSHAPES), CtoP(start_y + HEIGHTSHAPE / 2f), CtoP(start_x + 1.5f * WIDTHSHAPE + DISTBETWEENSHAPES), CtoP(start_y + HEIGHTSHAPE / 2f));
                            WordShape = WordDoc.Shapes.AddLine(CtoP(start_x + 1.5f * WIDTHSHAPE + DISTBETWEENSHAPES), CtoP(start_y + HEIGHTSHAPE / 2f), CtoP(start_x + 1.5f * WIDTHSHAPE + DISTBETWEENSHAPES), CtoP(start_y + HEIGHTSHAPE + DISTBETWEENSHAPES));
                            cur_y = start_y + HEIGHTSHAPE + DISTBETWEENSHAPES;
                        }
                        else 
                        {
                            cur_y = start_y;
                        }                        
                        cur_x = start_x + WIDTHSHAPE + DISTBETWEENSHAPES;                        
                        break;
                    case "CONDITIONEND":
                        if (lower_y > cur_y)
                        {
                            WordShape = WordDoc.Shapes.AddLine(CtoP(cur_x + WIDTHSHAPE / 2f), CtoP(cur_y), CtoP(cur_x + WIDTHSHAPE / 2f), CtoP(lower_y - DISTBETWEENSHAPES / 2f));
                            WordShape = WordDoc.Shapes.AddLine(CtoP(lower_x + WIDTHSHAPE / 2f), CtoP(lower_y - DISTBETWEENSHAPES / 2f), CtoP(cur_x + WIDTHSHAPE / 2f), CtoP(lower_y - DISTBETWEENSHAPES / 2f));
                            cur_y = lower_y;
                        }
                        else 
                        {
                            WordShape = WordDoc.Shapes.AddLine(CtoP(lower_x + WIDTHSHAPE / 2f), CtoP(lower_y), CtoP(lower_x + WIDTHSHAPE / 2f), CtoP(cur_y + DISTBETWEENSHAPES));
                            WordShape = WordDoc.Shapes.AddLine(CtoP(lower_x + WIDTHSHAPE / 2f), CtoP(cur_y), CtoP(cur_x + WIDTHSHAPE / 2f), CtoP(cur_y));
                            cur_y += DISTBETWEENSHAPES; 
                        }
                        cur_x = lower_x;
                        break;
                    case "CYCLE":
                        break;
                    case "FUNCT":
                        FunctBlock(ref cur_x, ref cur_y, list[i].BlockText);
                        break;
                }
            }
        }

        //Процесс создания
        public void ProcessStart(List<Token> list, float cur_x = 0.2f, float cur_y = 0.2f)
        {
            int count_width_page = 1;
            int count_height_page = 0;
            foreach (Token item in list)
            {
                if (item.TokenName == "CONDITION")
                {
                    count_width_page++;
                }
                var m_lst = item.TokenRef;
                while (m_lst != null)
                {
                    foreach (Token itm in m_lst)
                    {
                        count_height_page++;
                        if (itm.TokenName == "CONDITION")
                        {
                            count_width_page++;
                            m_lst = itm.TokenRef;
                            break;
                        }
                        if (itm.TokenName == "CONDITIONEND")
                        {
                            m_lst = null;
                            break;
                        }
                    }
                }
            }
            count_height_page = (count_height_page > list.Count) ? ++count_height_page : list.Count;
            SetPageSize(count_height_page, count_width_page);
            for (int i = 0; i < list.Count; i++)
            {
                switch (list[i].TokenName)
                {
                    case "START":
                        StartBlock(ref cur_x, ref cur_y);
                        break;
                    case "END":
                        EndBlock(cur_x, cur_y);
                        break;
                    case "CONDITION":
                        Condition(ref cur_x, ref cur_y, list[i].TokenRef, list[i].BlockText);
                        break;
                    case "CYCLE":
                        break;
                    case "FUNCT":
                        FunctBlock(ref cur_x, ref cur_y, list[i].BlockText);
                        break;
                }
            }
        }
    }
}
