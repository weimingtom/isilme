using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using Common;

namespace QuestEditor.Proxy
{
    public class ProxyObject : IProxyObject, INotifyPropertyChanged
    {
        public ProxyObject(CommandManager commandManager)
        {
            ActionManager = commandManager;
        }

        [Browsable(false)]
        public CommandManager ActionManager
        {
            get;
            set;
        }

        public Object SelectedObject
        {
            get;
            set;
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public void RaisePropertyChanged(object sender, string property = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(property));
        }
    }
}
