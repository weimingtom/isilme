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
using System.IO;

namespace Common.Views
{
    /// <summary>
    /// Interaction logic for TextEditor.xaml
    /// </summary>
    public partial class TextEditorWindow : EditorWindow
    {
        public String Text
        {
            get;
            set;
        }

        public TextEditorWindow()
        {
            InitializeComponent();
        }

        public override void Load()
        {
            StreamReader reader = new StreamReader(FileName);
            Text = reader.ReadToEnd();
            mTextEditor.Text = Text;
            reader.Close();
        }

        public override void Load(IEditableData data)
        {
            
        }

        public override void Save()
        {
            StreamWriter writer = new StreamWriter(FileName);
            writer.Write(mTextEditor.Text);
            writer.Close();
        }
    }
}
