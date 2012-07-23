using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;

namespace MyApplication1.Data
{
    public class ActionTarget : ProxyObject
    {
        public TargetSelector Selector
        {
            get;
            set;
        }
        public ParamsTable Params
        {
            get;
            set;
        }
     }
}
