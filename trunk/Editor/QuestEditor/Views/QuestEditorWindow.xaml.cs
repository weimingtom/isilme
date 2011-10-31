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
            ModelQuest q = new ModelQuest() { Title = "Created by command" };
            CommandManager.Execute(new AddQuest(mStory, q));
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


        #endregion

        public static Stream OpenStream(string name)
        {
            Stream s = typeof(QuestEditorWindow).Assembly.GetManifestResourceStream("QuestEditor.Views.QuestToolbar.xaml");

            if (s == null)
                throw new FileNotFoundException("The resource file '" + name + "' was not found.");
            return s;
        }

        public static ToolBar getToolbar()
        {
            return new QuestEditor.Views.QuestToolbar();
        }

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

        /// <summary>
        /// Создает новое задание
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void onAddQuest(Object sender, RoutedEventArgs e)
        {
            ModelQuest q = new ModelQuest() { Title="Created by command"};
            CommandManager.Execute(new AddQuest(mStory, q));
        }

        /// <summary>
        /// Создает новыу стадию текущего задания
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void onAddStage(Object sender, RoutedEventArgs e)
        {
            ModelQuest quest = mStoryTreeView.SelectedItem as ModelQuest;
            ModelStage stage = new ModelStage();

            if (quest == null)
            {
                quest = (mStoryTreeView.SelectedItem as ModelStage).Quest;
                CommandManager.Execute(new AddStage(quest, stage));
            }
            else
            {
                CommandManager.Execute(new AddStage(quest, stage));
            }
        }

        void onRemoveNode(Object sender, RoutedEventArgs e)
        {
            ModelQuest quest = mStoryTreeView.SelectedItem as ModelQuest;
            ModelStage stage = mStoryTreeView.SelectedItem as ModelStage;
            if (quest != null)
            {
                CommandManager.Execute(new DelQuest(mStory, quest));
            }
            else if (stage != null)
            {
                CommandManager.Execute(new DelStage(stage.Quest, stage));
            }
        }

        private void onStoryTreeView_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            ModelQuest quest = mStoryTreeView.SelectedItem as ModelQuest;
            ModelStage stage = mStoryTreeView.SelectedItem as ModelStage;
            if (quest != null)
            {
                SelectedObject = new Proxy.ProxyQuest(CommandManager, quest);
            }
            else if (stage != null)
            {
                SelectedObject = new Proxy.ProxyStage(CommandManager, stage);
            }
        }
    }
}
