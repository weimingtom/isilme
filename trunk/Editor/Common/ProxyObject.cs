using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using Common;

namespace Common
{
    public class ProxyObject : IProxyObject, INotifyPropertyChanged
    {
        private ICommand mCommand;

        public ProxyObject()
        {
        }

        [Browsable(false)]
        public ICommand CurrentCommand
        {
            get
            {
                return mCommand;
            }
            set
            {
                mCommand = value;
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public void RaisePropertyChanged(object sender, string property = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(property));
        }
    }
}
