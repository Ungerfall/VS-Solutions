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
using System.Windows.Shapes;

using Microsoft.VisualBasic;

namespace SFT.Forms.TownsEditor
{
    /// <summary>
    /// Interaction logic for TownsEditor.xaml
    /// </summary>
    /// 
    public partial class TownsEditor : Window
    {
        public TownsEditor()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {

        }

        private void Add_Button_Click(object sender, RoutedEventArgs e)
        {
            string st = Microsoft.VisualBasic.Interaction.InputBox("Название города", "Добавление города", "", 100, 100);
        }
    }
}
