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

using System.Windows.Threading;
using System.Data;
using SFT.Forms;
using SFT;
using System.Globalization;
using System.Collections.ObjectModel;

namespace SFT.Forms.MainForm
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        DispatcherTimer timer;
        DateTime date;

        ///////////////////////////////////////////////
        private CBoardFields CBF_0;
        private CBoardFields CBF_1;
        private CBoardFields CBF_2;
        private CBoardFields CBF_3;
        private CMainFormContext m_f_context;
        private ObservableCollection<CBoardFields> temp;
        ////////////////////////////////////////////////

        public MainWindow()
        {
            InitializeComponent();
            Loaded += new RoutedEventHandler(MainWindow_Loaded);

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1.0);
            timer.Start();
            
            date = new DateTime();
            date = DateTime.Now;
            DateBlock.Text = WeekDay(date.DayOfWeek.ToString());
            Date.Text = date.Day.ToString() + "." + date.Month.ToString() + "." + date.Year.ToString();

            timer.Tick += new EventHandler(delegate(object s, EventArgs e)
                {
                    ClockBlock.Text = "" + Timer_(DateTime.Now.Hour) + ":" + Timer_(DateTime.Now.Minute) + ":" + Timer_(DateTime.Now.Second);
                });

            /////////////////////////////////////////////////
            CBF_0 = new CBoardFields() { AirplaneNumber = "10F1", DepartureTime = "04:10", Path_ = "Ижевск - Сочи", Terminal = "F1" };
            CBF_1 = new CBoardFields() { AirplaneNumber = "00A1", DepartureTime = "04:30", Path_ = "Ижевск - Москва", Terminal = "F3" };
            CBF_2 = new CBoardFields() { AirplaneNumber = "2FA1", DepartureTime = "05:15", Path_ = "Ижевск - Париж", Terminal = "F1" };
            CBF_3 = new CBoardFields() { AirplaneNumber = "2FA8", DepartureTime = "05:45", Path_ = "Ижевск - П-Камчатский", Terminal = "F6" };
            temp = new ObservableCollection<CBoardFields>();
            temp.Add(CBF_0);
            temp.Add(CBF_1);
            temp.Add(CBF_2);
            temp.Add(CBF_3);
            //////////////////////////////////////////////////
        }

        
        void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            
            m_f_context = new CMainFormContext();
            m_f_context.RouteList = temp;
            DataContext = m_f_context;
        }

        //корректировка времени (добавление нуля)
        private string Timer_(int _value)
        {
            return ((_value < 10) ? "0" + _value.ToString() : _value.ToString());
        }

        //русское отображение дня недели
        private string WeekDay(string st)
        {
            switch (st.ToUpper())
            {
                case "MONDAY":
                    return "Понедельник";
                case "TUESDAY":
                    return "Вторник";
                case "WEDNESDAY":
                    return "Среда";
                case "THURSDAY":
                    return "Четверг";
                case "FRIDAY":
                    return "Пятница";
                case "SATURDAY":
                    return "Суббота";
                case "SUNDAY":
                    return "Воскресенье";
                default:
                    return "Error";
            }
        }

        private void Exit_click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void TownsEditor_Click(object sender, RoutedEventArgs e)
        {
            var t_e = new TownsEditor.TownsEditor();
            t_e.ShowDialog();
        }

        private void PathsEditor_Click(object sender, RoutedEventArgs e)
        {
            var t_e = new PathsEditor.PathsEditor();
            t_e.ShowDialog();
        }

        private void TimeTable_Click(object sender, RoutedEventArgs e)
        {
            var t_t = new TimeTable.TimeTable();
            t_t.ShowDialog();
        }
    }
}
