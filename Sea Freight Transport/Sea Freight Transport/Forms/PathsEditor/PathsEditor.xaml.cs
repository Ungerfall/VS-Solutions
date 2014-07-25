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

namespace SFT.Forms.PathsEditor
{
    /// <summary>
    /// Interaction logic for PathsEditor.xaml
    /// </summary>
    public partial class PathsEditor : Window
    {
        public PathsEditor()
        {
            InitializeComponent();
        }

        private void AddPath_Click(object sender, RoutedEventArgs e)
        {
            var a_p = new AddNewPath.AddNewPath();
            a_p.ShowDialog();
        }
    }
}
