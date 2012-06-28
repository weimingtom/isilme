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
using Common;

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
            mPropertyGrid.PropertyValueChanged += new System.Windows.Forms.PropertyValueChangedEventHandler(mPropertyGrid_PropertyValueChanged);

            mWFHost.Child = mPropertyGrid;
        }

        void mPropertyGrid_PropertyValueChanged(object s, System.Windows.Forms.PropertyValueChangedEventArgs e)
        {
            if (SelectedObject != null)
            {
                if (SelectedObject.CurrentCommand != null)
                    CommandManager.Execute(SelectedObject.CurrentCommand);
            }
            //else if (SelectedObjects != null)
            //{
            //}
        }

        public IProxyObject SelectedObject
        {
            get
            {
                return mPropertyGrid.SelectedObject as IProxyObject;
            }
            set
            {
                mPropertyGrid.SelectedObject = value;
            }
        }

        public Common.CommandManager CommandManager
        {
            get;
            set;
        }
    }
}
