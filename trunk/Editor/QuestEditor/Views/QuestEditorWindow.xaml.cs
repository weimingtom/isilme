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
using QuestEditor.Commands;

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

            ModelQuest q = new ModelQuest() { Title = "Test quest", ID = "test" };
            
            mStory.AddQuest(q);
            mStory.AddQuest(new ModelQuest() { Title = "Test quest 2", ID = "test2" });
            mStory.AddQuest(new ModelQuest() { Title = "Test quest 3", ID = "test3" });
            mStory.AddQuest(new ModelQuest() { Title = "Test quest 4", ID = "test4" });

            mStory.AddStage(q, new ModelStage() {ID=10 });
            mStory.AddStage(q, new ModelStage() { ID = 20 });
            mStory.AddStage(q, new ModelStage() { ID = 30 });
            mStoryTreeView.DataContext = mStory;
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

        void onAddQuest(Object sender, RoutedEventArgs e)
        {
            ModelQuest q = new ModelQuest() { Title="Created by command"};
            CommandManager.Execute(new AddQuest(mStory, q));
        }

        void onAddStage(Object sender, RoutedEventArgs e)
        {
            ModelQuest quest = mStoryTreeView.SelectedItem as ModelQuest;
            ModelStage stage = new ModelStage();

            if (quest == null)
            {
            }
            else
            {
                CommandManager.Execute(new AddStage(quest, stage));
            }
        }

        void onRemoveNode(Object sender, RoutedEventArgs e)
        {
        }
    }
}
