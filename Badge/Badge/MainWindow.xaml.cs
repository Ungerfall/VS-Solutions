using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.VisualBasic;
using Word = Microsoft.Office.Interop.Word;
using System.ComponentModel;

namespace Badge
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private BackgroundWorker backgroundWorker;
        public MainWindow()
        {
            InitializeComponent();
            backgroundWorker = (BackgroundWorker)this.FindResource("backgroundWoker");
        }

        //прогресс-бар
        private void BackgroundWorker_ProgressChanged(object sender, System.ComponentModel.ProgressChangedEventArgs e)
        {
            txtProgress.Content = (e.ProgressPercentage.ToString() + "%");
            progressBar.Value = e.ProgressPercentage;
        }

        private void BackgroundWorker_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
        {
            BackgroundWorker worker = sender as BackgroundWorker;

            //
            wordapp = new Word.Application();
            Object Template = Type.Missing;
            Object NewTemplate = true;
            Object DocumentType = Word.WdNewDocumentType.wdNewBlankDocument;
            Object Visible = true;
            worddoc = wordapp.Documents.Add(ref Template, ref NewTemplate, ref DocumentType, ref Visible);
            wordapp.Documents.Save();
            worddoc.PageSetup.TopMargin = wordapp.CentimetersToPoints(0.2f);
            worddoc.PageSetup.LeftMargin = wordapp.CentimetersToPoints(0.2f);
            worddoc.PageSetup.RightMargin = wordapp.CentimetersToPoints(0.2f);
            worddoc.PageSetup.BottomMargin = wordapp.CentimetersToPoints(0.2f);

            //добавление элементов в список (для примера)
            first_name_participant.Add("Шевякова");
            first_name_participant.Add("Засыпкина");
            first_name_participant.Add("Шамшурин");
            first_name_participant.Add("Смирнов");
            first_name_participant.Add("Соловцов");
            first_name_participant.Add("Тарасов");
            first_name_participant.Add("Чучков");
            first_name_participant.Add("Михайлов");
            first_name_participant.Add("Боткин");
            first_name_participant.Add("Якимович");
            first_name_participant.Add("Кузнецов");
            first_name_participant.Add("Татаркин");
            second_name_participant.Add("Елена");
            second_name_participant.Add("Галина");
            second_name_participant.Add("Алексей");
            second_name_participant.Add("Борис");
            second_name_participant.Add("Никита");
            second_name_participant.Add("Владимир");
            second_name_participant.Add("Виктор");
            second_name_participant.Add("Юрий");
            second_name_participant.Add("Олег");
            second_name_participant.Add("Борис");
            second_name_participant.Add("Андрей");
            second_name_participant.Add("Александр");
            patronymic_participant.Add("Валентиновна");
            patronymic_participant.Add("Павловна");
            patronymic_participant.Add("Михайлович");
            patronymic_participant.Add("Петрович");
            patronymic_participant.Add("Сергеевич");
            patronymic_participant.Add("Григорьевич");
            patronymic_participant.Add("Михайлович");
            patronymic_participant.Add("Олегович");
            patronymic_participant.Add("Иванович");
            patronymic_participant.Add("Анатольевич");
            patronymic_participant.Add("Леонидович");
            patronymic_participant.Add("Иванович");
            institute_name.Add("Ижевский государственный технический университет");
            institute_name.Add("Ижевский государственный технический университет");
            institute_name.Add("МОУ «Экономико-естественный лицей №41», г. Ижевск");
            institute_name.Add("МОУ «Экономико-естественный лицей №41», г. Ижевск");
            institute_name.Add("МОУ «Экономико-естественный лицей №41», г. Ижевск");
            institute_name.Add("ИжГТУ, Ижевск");
            institute_name.Add("зам. министра образования и науки Удмуртской Республики");
            institute_name.Add("проректор по инновационной работе ИжГТУ");
            institute_name.Add("директор Удмуртского филиала ИЭ УрО РАН");
            institute_name.Add("ректор Ижевского государственного технического университета");
            institute_name.Add("министр образования и науки Удмуртской Республики");
            institute_name.Add("директор Института экономики УрО РАН");
            
            for (int ccl = 0; ccl < first_name_participant.Count; ccl++)
            {
                worker.ReportProgress(((int)((float)ccl / first_name_participant.Count * 100)));
                create_badge(first_name_participant[ccl], second_name_participant[ccl], patronymic_participant[ccl], institute_name[ccl]);
            }
            worker.ReportProgress(100);
            wordapp.Visible = true;
        }

        public Word.Application wordapp;
        public Word.Document worddoc;
        public Word.Range wordcellrange;
        public Word.Range wordrange;
        public Word.Table wordtable;
        public Word.Shape wordshape;

        //контент
        private List<string> first_name_participant = new List<string>();
        private List<string> second_name_participant = new List<string>();
        private List<string> patronymic_participant = new List<string>();
        private List<string> institute_name = new List<string>();
        private string name_event = "10-е УЧЕБНЫЕ СПОРТИВНЫЕ ИНТЕЛЛЕКТУАЛЬНЫЕ СОСТЯЗАНИЯ  СТУДЕНТОВ ПО ПРОГРАММИРОВАНИЮ";
        private string date_event = "18-30 сентября 2012 г.";
        private string footer = "Ижевск, ИжГТУ имени М.Т. Калашникова";
        private int main_count = 1;
        private int main_i = 0;
        private int main_j = 0;

        //создание и форматирование новой пустой страницы в документе word
        private void create_new_page()
        {
            wordapp.Selection.InsertNewPage();
            worddoc.PageSetup.TopMargin = wordapp.CentimetersToPoints(0.2f);
            worddoc.PageSetup.LeftMargin = wordapp.CentimetersToPoints(0.2f);
            worddoc.PageSetup.RightMargin = wordapp.CentimetersToPoints(0.2f);
            worddoc.PageSetup.BottomMargin = wordapp.CentimetersToPoints(0.2f);
            wordapp.Selection.GoToPrevious(Word.WdGoToItem.wdGoToPage);
        }

        //создание одного бейджа
        private void create_badge(String fst_name, String snd_name, String patro, String inst_name)
        {
            if (main_count == 7)
            {
                create_new_page();
                main_count = 1;
            }

            if (main_i == 2)
                main_i = 0;
            if (main_j == 3)
                main_j = 0;
            
            
            //добавление надписи
            var orient = Microsoft.Office.Core.MsoTextOrientation.msoTextOrientationHorizontal;
            float left_sh = wordapp.CentimetersToPoints(0.2f + main_i * 10.16f);
            float top_sh = wordapp.CentimetersToPoints(0.2f + main_j * 7.62f);
            float wid_sh = wordapp.CentimetersToPoints(10.16f);
            float hei_sh = wordapp.CentimetersToPoints(7.62f);
            wordshape = worddoc.Shapes.AddTextbox(orient, left_sh, top_sh, wid_sh, hei_sh);
            int line_shape_rbg = Information.RGB(128, 128, 128);
            Word.WdColor line_shape = (Word.WdColor)line_shape_rbg;
            wordshape.Line.ForeColor.RGB = (Int32)line_shape;

            //добавление текста
            //шапка
            float sh3_left = wordapp.CentimetersToPoints(1.3f + main_i * 10.16f);
            float sh3_top = wordapp.CentimetersToPoints(0.21f + main_j * 7.62f);
            float sh3_wid = wordapp.CentimetersToPoints(7.99f);
            float sh3_hei = wordapp.CentimetersToPoints(2.36f);
            wordshape = worddoc.Shapes.AddTextbox(orient, sh3_left, sh3_top, sh3_wid, sh3_hei);
            wordshape.Line.Visible = Microsoft.Office.Core.MsoTriState.msoFalse;

            wordshape.TextFrame.TextRange.Font.Name = "Verdana";
            wordshape.TextFrame.TextRange.Font.Bold = 1;
            wordshape.TextFrame.TextRange.Font.Size = 9;
            wordshape.TextFrame.TextRange.Font.Color = Word.WdColor.wdColorRed;
            wordshape.TextFrame.TextRange.ParagraphFormat.LineSpacingRule = Word.WdLineSpacing.wdLineSpace1pt5;
            wordshape.TextFrame.TextRange.ParagraphFormat.Alignment = Word.WdParagraphAlignment.wdAlignParagraphCenter;
            wordshape.TextFrame.TextRange.Text = name_event + " " + date_event;

            //тело
            float sh4_left = wordapp.CentimetersToPoints(0.2f + main_i * 10.16f);
            float sh4_top = wordapp.CentimetersToPoints(2.78f + main_j * 7.62f);
            float sh4_wid = wordapp.CentimetersToPoints(10.15f);
            float sh4_hei = wordapp.CentimetersToPoints(4.06f);

            wordshape = worddoc.Shapes.AddTextbox(orient, sh4_left, sh4_top, sh4_wid, sh4_hei);
            wordshape.Line.Visible = Microsoft.Office.Core.MsoTriState.msoFalse;
            wordshape.TextFrame.TextRange.Paragraphs.Add();
            wordshape.TextFrame.TextRange.Paragraphs.Add();
            wordshape.TextFrame.TextRange.Paragraphs.Add();
            wordshape.TextFrame.TextRange.Paragraphs.Add();
            wordshape.TextFrame.TextRange.Paragraphs.Add();
            wordshape.TextFrame.TextRange.Paragraphs.Add();
            wordshape.TextFrame.TextRange.ParagraphFormat.SpaceAfter = wordapp.CentimetersToPoints(0f);
            wordshape.TextFrame.TextRange.ParagraphFormat.LineSpacingRule = Word.WdLineSpacing.wdLineSpaceSingle;
            wordshape.TextFrame.TextRange.ParagraphFormat.Alignment = Word.WdParagraphAlignment.wdAlignParagraphCenter;

            wordshape.TextFrame.TextRange.Paragraphs[1].Range.Font.Size = 13;

            wordshape.TextFrame.TextRange.Paragraphs[2].Range.Font.Name = "Tahoma";
            wordshape.TextFrame.TextRange.Paragraphs[2].Range.Font.Color = Word.WdColor.wdColorRed;
            wordshape.TextFrame.TextRange.Paragraphs[2].Range.Font.Bold = 1;
            wordshape.TextFrame.TextRange.Paragraphs[2].Range.Font.Italic = 1;
            wordshape.TextFrame.TextRange.Paragraphs[2].Range.Font.Size = 18;
            wordshape.TextFrame.TextRange.Paragraphs[2].Range.Text = fst_name.ToUpper();

            wordshape.TextFrame.TextRange.Paragraphs[3].Range.Font.Name = "Tahoma";
            wordshape.TextFrame.TextRange.Paragraphs[3].Range.Font.Color = Word.WdColor.wdColorRed;
            wordshape.TextFrame.TextRange.Paragraphs[3].Range.Font.Bold = 1;
            wordshape.TextFrame.TextRange.Paragraphs[3].Range.Font.Italic = 1;
            wordshape.TextFrame.TextRange.Paragraphs[3].Range.Font.Size = 18;
            wordshape.TextFrame.TextRange.Paragraphs[3].Range.Text = snd_name.ToUpper() + " " + patro.ToUpper();

            wordshape.TextFrame.TextRange.Paragraphs[4].Range.Font.Size = 8;

            wordshape.TextFrame.TextRange.Paragraphs[5].Range.Font.Name = "Tahoma";
            wordshape.TextFrame.TextRange.Paragraphs[5].Range.Font.Color = Word.WdColor.wdColorRed;
            wordshape.TextFrame.TextRange.Paragraphs[5].Range.Font.Bold = 1;
            wordshape.TextFrame.TextRange.Paragraphs[5].Range.Font.Italic = 0;
            wordshape.TextFrame.TextRange.Paragraphs[5].Range.Font.Size = 12;
            wordshape.TextFrame.TextRange.Paragraphs[5].Range.Text = inst_name;

            //добаление рисунков
            float pic_top = wordapp.CentimetersToPoints(0.0f + main_j * 7.62f);
            Object pic_LTF = Type.Missing;
            Object pic_SWD = Type.Missing;
            Object pic_ant = Type.Missing;

            float pic1_wid = wordapp.CentimetersToPoints(1.59f);
            float pic1_hei = wordapp.CentimetersToPoints(1.59f);
            float pic1_left = wordapp.CentimetersToPoints(0.0f + main_i * 10.16f);
            wordshape = worddoc.Shapes.AddPicture(System.IO.Path.GetFullPath("left.png"), ref pic_LTF, ref pic_SWD, pic1_left, pic_top, pic1_wid, pic1_hei, pic_ant);
            wordshape.Line.Visible = Microsoft.Office.Core.MsoTriState.msoFalse;

            float pic2_wid = wordapp.CentimetersToPoints(1.80f);
            float pic2_hei = wordapp.CentimetersToPoints(1.22f);
            float pic2_left = wordapp.CentimetersToPoints(8.35f + main_i * 10.16f);
            wordshape = worddoc.Shapes.AddPicture(System.IO.Path.GetFullPath("right.png"), ref pic_LTF, ref pic_SWD, pic2_left, pic_top, pic2_wid, pic2_hei, ref pic_ant);
            wordshape.Line.Visible = Microsoft.Office.Core.MsoTriState.msoFalse;
            //wordshape.ZOrder(Microsoft.Office.Core.MsoZOrderCmd.msoBringForward);

            float pic3_wid = wordapp.CentimetersToPoints(9.29f);
            float pic3_hei = wordapp.CentimetersToPoints(0.16f);
            float pic3_left = wordapp.CentimetersToPoints(0.60f + main_i * 10.16f);
            float pic3_top = wordapp.CentimetersToPoints(2.41f + main_j * 7.62f);
            wordshape = worddoc.Shapes.AddPicture(System.IO.Path.GetFullPath("center.png"), ref pic_LTF, ref pic_SWD, pic3_left, pic3_top, pic3_wid, pic3_hei, ref pic_ant);
            wordshape.Line.Visible = Microsoft.Office.Core.MsoTriState.msoFalse;

            //футер
            float sh2_hei = wordapp.CentimetersToPoints(0.95f);
            float sh2_top = wordapp.CentimetersToPoints(6.86f + main_j * 7.62f);
            float sh2_wid = wordapp.CentimetersToPoints(10.15f);
            wordshape = worddoc.Shapes.AddTextbox(orient, left_sh, sh2_top, sh2_wid, sh2_hei);
            wordshape.Line.Visible = Microsoft.Office.Core.MsoTriState.msoFalse;
            int back_color_rbg = Information.RGB(153, 255, 153);
            Word.WdColor back_color = (Word.WdColor)back_color_rbg;
            wordshape.Fill.ForeColor.RGB = (Int32)back_color;
            wordshape.TextFrame.TextRange.Font.Name = "Times New Roman";
            wordshape.TextFrame.TextRange.Font.Bold = 1;
            wordshape.TextFrame.TextRange.Font.Size = 12;
            wordshape.TextFrame.TextRange.ParagraphFormat.Alignment = Word.WdParagraphAlignment.wdAlignParagraphCenter;
            wordshape.TextFrame.TextRange.Text = footer;

            ++main_count;
            ++main_i;
            ++main_j;
        }
    
        private void button1_Click(object sender, RoutedEventArgs e)
        {
            //старт прогресс бара
            progressBar.Value = 0;
            progressBar.Visibility = Visibility.Visible;
            backgroundWorker.RunWorkerAsync();

            
            //Application.Current.Shutdown();
        }
    }
}
