using System;
using System.Collections;
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
using IMStocker.Common;

namespace CW_Teory_LugachevPP
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            MContext = new NotifiableCollection<GraphItem>();
            var item = new GraphItem() { Number = "1", Perspectives = "Внедрение crm", Events = "CRM", Limit = 90, I_C = "Петров", Investments = "900 тыс." };
            MContext.Add(item);
            this.DataContext = MContext;
            //DataGrid.ItemsSource = Examples;
        }

        private void Exit_click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        public NotifiableCollection<GraphItem> MContext
        {
            get;
            set;
        }

        private void TB_Loaded(object sender, RoutedEventArgs e)
        {
            ToolBar toolBar = sender as ToolBar;
            var overflowGrid = toolBar.Template.FindName("OverflowGrid", toolBar) as FrameworkElement;
            if (overflowGrid != null)
            {
                overflowGrid.Visibility = Visibility.Collapsed;
            }

            var mainPanelBorder = toolBar.Template.FindName("MainPanelBorder", toolBar) as FrameworkElement;
            if (mainPanelBorder != null)
            {
                mainPanelBorder.Margin = new Thickness(0);
            }
        }

        private void Save_click(object sender, RoutedEventArgs e)
        {
            System.Diagnostics.Process.Start(@"D:\Study\C, C++, C#\CW_Teory_LugachevPP\CW_Teory_LugachevPP\Graph.docx");
        }

        private void Add_click(object sender, RoutedEventArgs e)
        {
            var item = new GraphItem() { Number = (MContext.Count + 1).ToString() };
            MContext.Add(item);
        }

        private void Clear_click(object sender, RoutedEventArgs e)
        {
            MContext.Clear();
            MContext.Add(new GraphItem() { Number = (MContext.Count + 1).ToString() });
        }

        private void Addadd_click(object sender, RoutedEventArgs e)
        {
            
        }
    }

    public class GraphItem : PropertyHolder
    {
        #region Properties
        //номер
        public string Number
        {
            get { return p_GetProp<string>("Number"); }
            set { p_SetProp("Number", value); }
        }

        //перспективы и цели
        public string Perspectives
        {
            get { return p_GetProp<string>("Perspectives"); }
            set { p_SetProp("Perspectives", value); }
        }

        //предельное значение
        public int Limit
        {
            get { return p_GetProp<int>("Limit"); }
            set { p_SetProp("Limit", value); }
        }
        
        //мероприятия
        public string Events
        {
            get { return p_GetProp<string>("Events"); }
            set { p_SetProp("Events", value); }
        }

        //ответственный
        public string I_C
        {
            get { return p_GetProp<string>("I_C"); }
            set { p_SetProp("I_C", value); }
        }

        //инвестиции
        public string Investments
        {
            get { return p_GetProp<string>("Investments"); }
            set { p_SetProp("Investments", value); }
        }
        #endregion
    }
}
