using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.Net;
using System.Text.RegularExpressions;
using IMStocker.Common;
using System.Diagnostics;

namespace ClickToCallURL
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            InputTextBox.Focus();
        }

        private List<ContentItem> items;
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            using (WebClient client = new WebClient())
            {
                items = new List<ContentItem>();
                Regex re = new Regex("<h3 class=\"r\">(.*?)<\\/h3>", RegexOptions.Multiline);
                Regex snd_re = new Regex("(<a.*\">)(.*)(<\\/a>)", RegexOptions.Multiline);
                string search = UrlEncode(InputTextBox.Text);
                var content = client.DownloadString("http://google.com/search?q=" + search);
                var txt = re.Matches(content);
                foreach (Match item in txt)
                {
                    string test = item.Value;
                    var snd_txt = snd_re.Match(item.Groups[1].Value);
                    items.Add(new ContentItem() { Link = get_link(snd_txt.Groups[2].Value) + "\n", HyperLink = get_url(item.Groups[1].Value) });
                }
            }

            DataContext = items;
        }

        private string get_link(string text)
        {
            var str = text.Replace("<b>", "").Replace("</b>", "");
            return str;
        }

        private string get_url(string text)
        {
            Regex regex = new Regex("url\\?q=(.*?)&", RegexOptions.Multiline);
            var txt = regex.Match(text);
            return txt.Groups[1].Value;
        }

        private void Hyperlink_RequestNavigate(object sender, RequestNavigateEventArgs e)
        {
            Process.Start(new ProcessStartInfo(e.Uri.AbsoluteUri));
            e.Handled = true;
        }

         private string UrlEncode(string value) 
         {
             StringBuilder result = new StringBuilder();
             string _UnreservedChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.~";
             foreach (char symbol in value) 
             {
                 if (_UnreservedChars.IndexOf(symbol) != -1) 
                 {
                     result.Append(symbol);
                 } 
                 else 
                 {
                     result.AppendFormat("%{0:X2}", (int)symbol);
                 }
             }
             return result.ToString();
         }
    }

    public class ContentItem : PropertyHolder
    {
        public string Link
        {
            get { return p_GetProp<string>("Link"); }
            set { p_SetProp("Link", value); }
        }

        public string HyperLink
        {
            get { return p_GetProp<string>("HyperLink"); }
            set { p_SetProp("HyperLink", value); }
        }
    }
}
