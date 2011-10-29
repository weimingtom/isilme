using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Common
{
    public interface IProxyObject
    {
        CommandManager ActionManager
        {
            get;
            set;
        }

        Object SelectedObject
        {
            get;
            set;
        }
    };

}
