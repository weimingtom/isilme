using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Common
{
    public interface IProxyObject
    {
        ICommand CurrentCommand
        {
            get;
        }

        void RaisePropertyChanged(object sender, string property = "");
    };

}
