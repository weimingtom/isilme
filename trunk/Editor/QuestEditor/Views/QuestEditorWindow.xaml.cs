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
using System.Reflection;
using System.Resources;
using System.Windows.Markup;
using System.IO;
using QuestEditor.Proxy;

namespace QuestEditor.Views
{
    /// <summary>
    /// Interaction logic for QuestEditorWindow.xaml
    /// </summary>
    public partial class QuestEditorWindow : EditorWindow
    {
        #region Commands

        public static RoutedCommand AddQuest = new RoutedCommand();
        public static RoutedCommand AddStage = new RoutedCommand();
        public static RoutedCommand Remove = new RoutedCommand();

        private void ExecutedAddQuestCommand(object sender, ExecutedRoutedEventArgs e)
        {
            ProxyQuest q = mProxyStory.CreateNewQuest();
            CommandManager.Execute(new AddQuest(mProxyStory, q));
        }

        private void CanExecuteAddQuestCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            Control target = e.Source as Control;

            if (target != null)
            {
                e.CanExecute = true;
            }
            else
            {
                e.CanExecute = false;
            }
        }

        private void ExecutedAddStage(object sender, ExecutedRoutedEventArgs e)
        {
            ProxyQuest quest = mStoryTreeView.SelectedItem as ProxyQuest;
            ProxyStage stage;

            if (quest == null)
            {
                quest = (mStoryTreeView.SelectedItem as ProxyStage).Parent;
                stage = quest.CreateNewStage();
                CommandManager.Execute(new AddStage(quest, stage));
            }
            else
            {
                stage = quest.CreateNewStage();
                CommandManager.Execute(new AddStage(quest, stage));
            }
        }

        private void CanExecuteAddStage(object sender, CanExecuteRoutedEventArgs e)
        {
            Control target = e.Source as Control;

            if (target != null)
            {
                e.CanExecute = true;
            }
            else
            {
                e.CanExecute = false;
            }
        }

        private void ExecutedRemove(object sender, ExecutedRoutedEventArgs e)
        {
            ProxyQuest quest = mStoryTreeView.SelectedItem as ProxyQuest;
            ProxyStage stage = mStoryTreeView.SelectedItem as ProxyStage;
            if (quest != null)
            {
                CommandManager.Execute(new DelQuest(mProxyStory, quest));
            }
            else if (stage != null)
            {
                CommandManager.Execute(new DelStage(stage.Parent, stage));
            }
        }

        private void CanExecuteRemove(object sender, CanExecuteRoutedEventArgs e)
        {
            Control target = e.Source as Control;

            if (target != null)
            {
                e.CanExecute = true;
            }
            else
            {
                e.CanExecute = false;
            }
        }

        #endregion

        public static ToolBar getToolbar()
        {
            return new QuestEditor.Views.QuestToolbar();
        }

        #region Members

        ModelStory mStory = new ModelStory();
        ProxyStory mProxyStory;

        #endregion

        public QuestEditorWindow()
        {
            InitializeComponent();

            ModelQuest q = new ModelQuest() { Title = "Test quest", ID = "test" };
            Proxy.ProxyStory s = new Proxy.ProxyStory(CommandManager, mStory);
            s.AddQuest(s.CreateNewQuest());
            s.AddQuest(s.CreateNewQuest());
            s.AddQuest(s.CreateNewQuest());
            s.AddQuest(s.CreateNewQuest());

            mStoryTreeView.DataContext = s;
            mProxyStory = s;

           // CommandBindings.Add(new CommandBinding(QuestEditorWindow.AddQuest, ExecutedAddQuestCommand, CanExecuteAddQuestCommand));
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

        private void onStoryTreeView_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            SelectedObject = mStoryTreeView.SelectedItem as Common.IProxyObject;
        }
    }
}
