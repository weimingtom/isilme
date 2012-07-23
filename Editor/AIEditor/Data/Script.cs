using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;

namespace MyApplication1.Data
{
    public class Script : ProxyObject
    {
        public List<String> Params
        {
            get;
            set;
        }
        public String Code
        {
            get;
            set;
        }
    }
}
