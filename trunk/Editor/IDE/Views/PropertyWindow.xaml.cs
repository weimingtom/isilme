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
using AvalonDock;
using Common.Views;

namespace IDE.Views
{
    /// <summary>
    /// Interaction logic for PropertyWindow.xaml
    /// </summary>
    public partial class PropertyWindow : ToolWindow
    {
        System.Windows.Forms.PropertyGrid mPropertyGrid;

        public PropertyWindow()
        {
            InitializeComponent();

            mPropertyGrid = new System.Windows.Forms.PropertyGrid();
            mPropertyGrid.Dock = System.Windows.Forms.DockStyle.Fill;

            mWFHost.Child = mPropertyGrid;
        }
    }
}
