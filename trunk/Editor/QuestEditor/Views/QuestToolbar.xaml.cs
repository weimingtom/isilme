using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace QuestEditor.Views
{
    /// <summary>
    /// Interaction logic for QuestToolbar.xaml
    /// </summary>
    public partial class QuestToolbar : ToolBar
    {
        static QuestToolbar mInstance = new QuestToolbar();

        public static QuestToolbar Instance
        {
            get { return mInstance; }
        }

        public QuestToolbar()
        {
            mInstance = this;
            InitializeComponent();
            
        }
    }
}
