using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.ComponentModel;

namespace SFT.Forms.MainForm
{
    public class CBoardFields : INotifyPropertyChanged
    {
        //номер самолета
        private string airplane_number;
        public string AirplaneNumber
        {
            get { return airplane_number; }
            set 
            {
                airplane_number = value;
                OnPropertyChanged(new PropertyChangedEventArgs("AirplaneNumber"));
            }
        }

        //маршрут в формате откуда-куда
        private string path_;
        public string Path_
        {
            get { return path_; }
            set 
            {
                path_ = value;
                OnPropertyChanged(new PropertyChangedEventArgs("Path_"));
            }
        }

        //терминал
        private string terminal;
        public string Terminal
        {
            get { return terminal; }
            set
            {
                terminal = value;
                OnPropertyChanged(new PropertyChangedEventArgs("Terminal"));
            }
        }

        //время отправления
        private string departure_time;
        public string DepartureTime
        {
            get { return departure_time; }
            set
            {
                departure_time = value;
                OnPropertyChanged(new PropertyChangedEventArgs("DepartureTime"));
            }
        }

        //
        // Уведомление об изменениях (INotifyPropertyChanged)
        //

        public event PropertyChangedEventHandler PropertyChanged;
        public void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            if (PropertyChanged != null) PropertyChanged(this, e);
        }
    }
}
