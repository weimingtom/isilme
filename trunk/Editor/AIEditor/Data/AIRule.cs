using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;

namespace MyApplication1.Data
{
    public class AIRule:ProxyObject
    {
        public String ID
        {
            get;
            set;
        }
        public AIAction Action
        {
            get;
            set;
        }
        public ActionTarget Target
        {
            get;
            set;
        }
        public Script Condition
        {
            get;
            set;
        }
        public Script Priority
        {
            get;
            set;
        }
    }
}
