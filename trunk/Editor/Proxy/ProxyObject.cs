using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using Common;

namespace GameEditor.Proxy
{
    public class ProxyObject
    {
        public ProxyObject(CommandManager commandManager)
        {
            CommandManager = commandManager;
        }

        [Browsable(false)]
        public CommandManager CommandManager
        {
            get;
            set;
        }
    }
}
