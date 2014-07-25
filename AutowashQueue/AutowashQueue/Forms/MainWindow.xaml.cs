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

using System.IO;

namespace AutowashQueue
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void LoadImgButton_click(object sender, RoutedEventArgs e)
        {
            var OFD = new System.Windows.Forms.OpenFileDialog();

            StringBuilder FilePath = new StringBuilder();
            if (OFD.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                FilePath.Append(OFD.FileName);
            }
            Camera.awLoadImage(FilePath);
        }

        private void LookAtQueue_click(object sender, RoutedEventArgs e)
        {
            Camera.awInitCamera();
            Camera.awGetImage();
        }

        private void Exit_click(object sender, RoutedEventArgs e)
        {
            Camera.awComplete();
            Application.Current.Shutdown();
        }
    }
}
