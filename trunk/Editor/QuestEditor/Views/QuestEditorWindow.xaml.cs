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
using System.Xml;
using System.Xml.Linq;
using Common.Views;
using QuestEditor.Models;

namespace QuestEditor.Views
{
    /// <summary>
    /// Interaction logic for QuestEditorWindow.xaml
    /// </summary>
    public partial class QuestEditorWindow : EditorWindow
    {
        #region Members

        ModelStory mStory = new ModelStory();

        #endregion

        public QuestEditorWindow()
        {
            InitializeComponent();
        }

        public override void Load()
        {
            XDocument document = XDocument.Load(FileName);

            mStory.Load(document.Root);
        }

        public override void Save()
        {
            XDocument document = new XDocument(mStory.Save());
            document.Save(FileName);
        }
    }
}
