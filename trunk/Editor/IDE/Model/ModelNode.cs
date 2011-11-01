using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Linq;

namespace IDE.Model
{
    public class ModelNode
    {
        public String Path
        {
            get;
            set;
        }

        public List<ModelNode> Items
        {
            get;
            set;
        }

        public XElement SaveToElement()
        {
            return null;
        }

        
    }
}
