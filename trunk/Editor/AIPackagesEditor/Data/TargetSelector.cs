using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;

namespace MyApplication1.Data
{
    public class TargetSelector : ProxyObject
    {
        public String ID
        {
            get;
            set;
        }
        public List<ParamInfo> Params
        {
            get;
            set;
        }
    }
}
