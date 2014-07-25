using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;

using System.Text.RegularExpressions;
using SFC.Forms.MainForm;

namespace SFC.Parser
{
    public class Scanner
    {
        private string InputStream { get; set; }

        private readonly MainWindow form = new MainWindow();
        public Scanner()
        { }

        public Scanner(string input_text, MainWindow form)
        {
            this.form = form;
            InputStream = input_text;
        }

        //create tokens
        private List<Token> GetTokenList()
        {
            Regex com = new Regex("{.*?}", RegexOptions.Multiline);
            foreach ( Match item in com.Matches(InputStream))
            {
                InputStream = InputStream.Replace(item.Value, "");
            }
            List<string> m_list = new List<string>();
            Regex re = new Regex("<(.*?)>", RegexOptions.Multiline);
            foreach (Match item in re.Matches(InputStream))
            {
                m_list.Add(item.Groups[1].Value);
            }

            Regex rex = new Regex(".+\"(.*)\".*", RegexOptions.Multiline);
            List<Token> out_lst = new List<Token>();

            foreach (string item in m_list)
            {
                var txt = rex.Match(item).Groups[1].Value;
                if (txt != "" && item.Contains('\"') && item.Contains(' '))
                {
                    out_lst.Add(new Token() { TokenName = item.Substring(0, item.IndexOf(' ')).ToUpper(), BlockText = txt });
                }
                else
                {
                    out_lst.Add(new Token() { TokenName = item.ToUpper() });
                }
            }

            return out_lst;
        }

        //create tokens
        private List<Token> GetTokenList(string text)
        {
            List<string> m_list = new List<string>();
            Regex re = new Regex("<(.*?)>", RegexOptions.Multiline);
            foreach (Match item in re.Matches(text))
            {
                m_list.Add(item.Groups[1].Value);
            }

            Regex rex = new Regex(".+\"(.*)\".*", RegexOptions.Multiline);
            List<Token> out_lst = new List<Token>();

            foreach (string item in m_list)
            {
                var txt = rex.Match(item).Groups[1].Value;
                if (txt != "" && item.Contains('\"') && item.Contains(' '))
                {
                    out_lst.Add(new Token() { TokenName = item.Substring(0, item.IndexOf(' ')).ToUpper(), BlockText = txt });
                }
                else
                {
                    out_lst.Add(new Token() { TokenName = item.ToUpper() });
                }
            }

            return out_lst;
        }

        public static StringBuilder CheckKeyWord(string text)
        {
            Scanner a = new Scanner();
            var lst = a.GetTokenList(text);

            StringBuilder out_txt = new StringBuilder();
            foreach (var item in lst.Select((value, index) => new { value, index }))
            {
                if (!MWContext.KeyWords.Any(str => str.Contains(item.value.TokenName)))
                {
                    out_txt.AppendFormat("Строка {0}. Грамматическая ошибка. Проверьте правильность написания.\n", item.index + 1);
                }
            }
            return out_txt;
        }

        public List<Token> Parsing()
        {
            List<Token> token_list = GetTokenList();
            var out_lst = new List<Token>();
            bool check = true;
            Stack<List<Token>> stack = new Stack<List<Token>>();
            Stack<string> texts = new Stack<string>();


            if (token_list[0].TokenName != "START")
            {
                form.ErrorBox.Text = "Ошибка. Нет точки начала START\n";
                check = false;
            }
            else
            {
                var counter_list = token_list;
                for (int i = 0; i < counter_list.Count; i++)
                {
                    switch (counter_list[i].TokenName)
                    {
                        case "START":
                            if (token_list[counter_list.Count - 1].TokenName != "END")
                            {
                                form.ErrorBox.Text = "Ошибка. Отсутствует ключевое слово END\n";
                                check = false;
                                goto default;
                            }
                            out_lst.Add(new Token { TokenName = "START", BlockText = counter_list[i].BlockText });
                            break;
                        case "END":
                            if (counter_list[counter_list.Count - 1].TokenName != "END")
                            {
                                form.ErrorBox.Text = "Ошибка. После END существуют другие ключевые слова\n";
                                check = false;
                                goto default;
                            }
                            else
                                out_lst.Add(new Token { TokenName = "END", BlockText = counter_list[i].BlockText });
                            break;
                        case "CONDITION":
                            if (counter_list[i + 1].TokenName != "IF")
                            {
                                form.ErrorBox.Text = "Ошибка. Отсутствие IF в условии\n";
                                check = false;
                                goto default;
                            }
                            break;
                        case "IF":
                            if (counter_list[i - 1].TokenName != "CONDITION")
                            {
                                form.ErrorBox.Text = "Ошибка. Отсутствие CONDITION перед IF\n";
                                check = false;
                                goto default;
                            }
                            texts.Push(counter_list[i].BlockText);
                            stack.Push(out_lst);
                            out_lst = new List<Token>();
                            break;
                        case "ELSE":
                            if (!counter_list.GetRange(0, i).Any(str => str.TokenName.Contains("IF")))
                            {
                                form.ErrorBox.Text = "Ошибка. Отсутствие IF перед ELSE\n";
                                check = false;
                                goto default;
                            }
                            if (!counter_list.GetRange(0, i).Any(str => str.TokenName.Contains("CONDITION")))
                            {
                                form.ErrorBox.Text = "Ошибка. ELSE вне CONDITION\n";
                                check = false;
                                goto default;
                            }
                            out_lst.Add(new Token { TokenName = "ELSE" });
                            break;
                        case "CONDITIONEND":
                            if (!counter_list.GetRange(0, i).Any(str => str.TokenName.Contains("CONDITION")))
                            {
                                form.ErrorBox.Text = "Ошибка. Отсутствет начало условия - CONDITION\n";
                                check = false;
                                goto default;
                            }
                            if (!counter_list.GetRange(0, i).Any(str => str.TokenName.Contains("IF")))
                            {
                                form.ErrorBox.Text = "Ошибка. Отсутствует IF в условии\n";
                                check = false;
                                goto default;
                            }
                            if (!counter_list.GetRange(0, i).Any(str => str.TokenName.Contains("ELSE")))
                            {
                                form.ErrorBox.Text = "Ошибка. Отсутствует ELSE в условии\n";
                                check = false;
                                goto default;
                            }
                            out_lst.Add(new Token { TokenName = "CONDITIONEND" });
                            var w_list = out_lst;
                            out_lst = stack.Pop();
                            out_lst.Add(new Token { TokenName = "CONDITION", BlockText = texts.Pop(), TokenRef = w_list });
                            break;
                        case "CYCLE":
                            break;
                        case "CYCLEEND":
                            break;
                        case "FUNCT":
                            out_lst.Add(new Token { TokenName = "FUNCT", BlockText = counter_list[i].BlockText });
                            break;
                        default:
                            i = counter_list.Count - 1;
                            break;
                    }
                }
            }
            if (check == false)
            {
                MessageBoxResult msng = MessageBox.Show("Невозможно отобразить схему. Посмотрите в ErrorBox", "Ошибка");
            }
            else
                return out_lst;
            return new List<Token>();
        }
    }
}
