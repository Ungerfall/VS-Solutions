using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using IMStocker;
using IMStocker.Common;

namespace SFC.Parser
{
    public class Token : PropertyHolder
    {
        public static readonly List<string> TokenKeyWords = new List<string>()
        {
            "START",
            "END",
            "CONDITION",
            "ELSE",
            "CONDITIONEND",
            "CYCLE",
            "CYCLEEND",
            "FUNCT",
        };

        public string TokenName
        {
            get { return p_GetProp<string>("TokenName"); }
            set { p_SetProp("TokenName", value); }
        }

        public string BlockText
        {
            get { return p_GetProp<string>("BlockText"); }
            set { p_SetProp("BlockText", value); }
        }

        public List<Token> TokenRef
        {
            get { return p_GetProp<List<Token>>("TokenRef"); }
            set { p_SetProp("TokenRef", value); }
        }
    }
}
