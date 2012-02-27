using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Input;

namespace Common
{
    public class FileCommands
    {
        public static DelegateCommand OpenFile = new DelegateCommand();

        public static RoutedCommand NewFileCommand = new RoutedCommand();
    }

}
