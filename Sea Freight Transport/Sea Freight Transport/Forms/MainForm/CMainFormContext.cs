using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.ComponentModel;
using System.Collections.ObjectModel;

namespace SFT.Forms.MainForm
{
    public class CMainFormContext : INotifyPropertyChanged
    {
        private ObservableCollection<CBoardFields> routelist;
        public ObservableCollection<CBoardFields> RouteList
        {
            get { return routelist; }
            set
            {
                routelist = value;
                OnPropertyChanged(new PropertyChangedEventArgs("RouteList"));
            }
        }

        private CBoardFields selected_route;
        public CBoardFields SelectedRoute
        {
            get { return selected_route; }
            set
            {
                selected_route = value;
                OnPropertyChanged(new PropertyChangedEventArgs("SelectedRoute"));
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
