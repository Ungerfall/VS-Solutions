using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IMStocker;
using IMStocker.Common;

namespace SFC.Forms.MainForm
{
    public class MWContext : PropertyHolder
    {
        //ключевые слова
        public static readonly NotifiableCollection<string> KeyWords = new NotifiableCollection<string>()
        {
            "START",
            "END",
            "CONDITION",
            "IF",
            "ELSE",
            "CONDITIONEND",
            "CYCLE",
            "CYCLEEND",
            "FUNCT",
            "TEXT"
        };

        //список доступных ключевых слов
        public NotifiableCollection<string> AvailableKeyWords
        {
            get { return p_GetProp<NotifiableCollection<string>>("AvailableKeyWords"); }
            set { p_SetProp("AvailableKeyWords", value); }
        }
        public bool IsRefact
        {
            get { return p_GetProp<bool>("IsRefact"); }
            set { p_SetProp("IsRefact", value); }
        }

        //наличие ошибок
        public bool IsError
        {
            get { return p_GetProp<bool>("IsError"); }
            set { p_SetProp("IsError", value); }
        }

        //контент ошибок
        public string ErrorText
        {
            get { return p_GetProp<string>("ErrorText"); }
            set { p_SetProp("ErrorText", value); }
        }

        //горизонтальное смещение popup
        public double HorOffset
        {
            get { return p_GetProp<double>("HorOffset"); }
            set { p_SetProp("HorOffset", value); }
        }

        //вертикальное смещение popup
        public double VerOffset
        {
            get { return p_GetProp<double>("VerOffset"); }
            set { p_SetProp("VerOffset", value); }
        }


    }
}
