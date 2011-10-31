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
using Common.Views;

namespace LuaEditor.Views
{
    /// <summary>
    /// Interaction logic for LuaEditorWindow.xaml
    /// </summary>
    public partial class LuaEditorWindow : EditorWindow
    {
        public LuaEditorWindow()
        {
            InitializeComponent();
        }

        public override void Undo()
        {
            mEditor.Undo();
        }

        public override void Redo()
        {
            mEditor.Redo();
        }

        public override void Save()
        {
            base.Save();
        }

        public override void Load()
        {
            base.Load();
        }
    }
}
