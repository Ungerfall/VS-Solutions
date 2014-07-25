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

using SFC.Forms.MainForm;
using System.Text.RegularExpressions;
using SFC.Generator;
using IMStocker;
using IMStocker.Common;
using SFC.Parser;

namespace SFC
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>

    public partial class MainWindow : Window
    {
        private MWContext m_context;
        private string m_key_word;
        //private char[] delimeters = { '\r', '\n', '\t', ' ', '<', '>' };

        public MainWindow()
        {
            InitializeComponent();
            Loaded += new RoutedEventHandler(MainWindow_Loaded);
            TextBox.FontFamily = new System.Windows.Media.FontFamily("Consolas");
            TextBox.Text = "<START text=\"start\">\n{тело схемы}\n<END text=\"end\">";
            TextBox.Focus();
            m_context = new MWContext();
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            DataContext = m_context;
        }

        private void Exit_button_click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void Exit_button_2_click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void TextBox_KeyUp(object sender, KeyEventArgs e)
        {
            m_key_word = Regex.Replace(p_get_key_word(TextBox.Text).ToUpper(), @"\s", "");
            m_context.AvailableKeyWords = new NotifiableCollection<string>();
            m_context.AvailableKeyWords.Clear();
            m_context.IsRefact = false;

            foreach (var item in MWContext.KeyWords)
            {
                if (item.Contains(m_key_word))
                {
                    m_context.AvailableKeyWords.Add(item);
                }
            }

            if (m_context.AvailableKeyWords.Count != 0)
                m_context.IsRefact = true;            
            DataContext = m_context;
            RefactoringListBox.ItemsSource = m_context.AvailableKeyWords;
        }

        private string p_get_key_word(string st)
        {
            try
            {
                if ((TextBox.CaretIndex != 0) && (st.LastIndexOf('<', TextBox.CaretIndex - 1) > st.LastIndexOf('>', TextBox.CaretIndex - 1)))
                {
                    Regex re = new Regex(@"<(.*)>?", RegexOptions.Multiline);
                    int m_start_index = TextBox.Text.LastIndexOf("<", TextBox.CaretIndex) == -1 ? 0 : TextBox.Text.LastIndexOf("<", TextBox.CaretIndex);
                    string sub = TextBox.Text.Substring(m_start_index, TextBox.CaretIndex - m_start_index);
                    string answ = re.Match(sub).Groups[1].Value;
                    int last_idx = answ.LastIndexOfAny(new char[] { ' ', '>' });
                    if (last_idx == -1)
                        last_idx = answ.Length;
                    return answ.Substring(0, last_idx);
                }
                else
                {
                    return "error";
                }
            }
            catch (Exception e)
            {
                m_context.ErrorText = e.Message;
                m_context.IsError = true;
                return "error";
            }
        }

        private void RefactoringListBox_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            int firstindex = TextBox.Text.LastIndexOf('<', TextBox.CaretIndex - 1) + 1;
            if (RefactoringListBox.SelectedValue != null)
            {
                TextBox.Text = TextBox.Text.Remove(firstindex, TextBox.CaretIndex - firstindex);
                TextBox.Text = TextBox.Text.Insert(firstindex, RefactoringListBox.SelectedValue.ToString());
                m_context.IsRefact = false;
                TextBox.Focus();
                TextBox.CaretIndex = firstindex + RefactoringListBox.SelectedValue.ToString().Length;
            }
            DataContext = m_context;
        }

        private void DrawButton_Click(object sender, RoutedEventArgs e)
        {
            Scanner input = new Scanner(TextBox.Text, this);
            var test = input.Parsing();
            if (test.Count != 0)
            {
                FlowchartDesigner des = new FlowchartDesigner(this);
                des.CreateDoc();
                des.ProcessStart(test);
                des.complete();
            }
            if (ErrorBox.Text.Length > 0)
            {
                m_context.IsError = true;
                DataContext = m_context;
            }
        }

        private void ErrorBoxClose(object sender, RoutedEventArgs e)
        {
            m_context.IsError = false;
            DataContext = m_context;
        }

        private void CheckSpelling(object sender, RoutedEventArgs e)
        {
            m_context.ErrorText = Scanner.CheckKeyWord(TextBox.Text).ToString();
            m_context.IsError = (m_context.ErrorText == "") ? false : true;
        }
    }
}
