using System;
using System.Collections;
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
using System.Windows.Shapes;
using System.Windows.Forms;
using GameEditor.Models;
using Common;

namespace GameEditor
{
    /// <summary>
    /// Interaction logic for StoryEditor.xaml
    /// </summary>
    public partial class StoryEditor : Window
    {
        #region Members

        ModelStory mStory = new ModelStory();
        Common.CommandManager mCommandManager = new Common.CommandManager();
        PropertyGrid mPropertyGrid;
        #endregion

        public StoryEditor()
        {
            InitializeComponent();

            mPropertyGrid = new PropertyGrid();
            mPropertyGrid.Dock = DockStyle.Fill;
            windowsFormsHost1.Child = mPropertyGrid;

            mStory.QuestAdded += new EventHandler<QuestEvtArgs>(mStory_QuestAdded);
            mStory.QuestRemoved += new EventHandler<QuestEvtArgs>(mStory_QuestRemoved);
            mStory.StageAdded += new EventHandler<QuestEvtArgs>(mStory_StageAdded);
            mStory.StageRemoved += new EventHandler<QuestEvtArgs>(mStory_StageRemoved);
        }

        void mStory_StageRemoved(object sender, QuestEvtArgs e)
        {
            TreeViewItem questItem = null;
            TreeViewItem stageItem = null;
            foreach (Object item in tvStory.Items)
            {
                if ((item as TreeViewItem).Header == e.Quest)
                    questItem = item as TreeViewItem;
            }
            foreach (Object item in questItem.Items)
            {
                if ((item as TreeViewItem).Header == e.Stage)
                    stageItem = item as TreeViewItem;
            }
            questItem.Items.Remove(stageItem);
        }

        void mStory_StageAdded(object sender, QuestEvtArgs e)
        {
            TreeViewItem questItem = null;
            foreach (Object item in tvStory.Items)
            {
                if ((item as TreeViewItem).Header == e.Quest)
                    questItem = item as TreeViewItem;
            }

            TreeViewItem stageItem = new TreeViewItem();
            stageItem.Header = e.Stage;
            int index = e.Quest.Stages.IndexOf(e.Stage);
            if (index >= questItem.Items.Count)
                questItem.Items.Add(stageItem);
            else
                questItem.Items.Insert(index, stageItem);
        }

        void mStory_QuestRemoved(object sender, QuestEvtArgs e)
        {
            TreeViewItem removedItem = null;
            foreach (Object item in tvStory.Items)
            {
                if ((item as TreeViewItem).Header == e.Quest)
                    removedItem = item as TreeViewItem;
            }
        }

        void mStory_QuestAdded(object sender, QuestEvtArgs e)
        {
            TreeViewItem item = new TreeViewItem();
            item.Header = e.Quest;

            foreach (ModelStage stage in e.Quest.Stages)
            {
                TreeViewItem stageItem = new TreeViewItem();
                stageItem.Header = stage;

                item.Items.Add(stageItem);
            }

            int index = mStory.Quests.IndexOf(e.Quest);
            if (index < tvStory.Items.Count)
                tvStory.Items.Insert(index, item);
            else
                tvStory.Items.Add(item);
        }

        private void onAddQuest(object sender, RoutedEventArgs e)
        {
            ModelQuest quest = new ModelQuest();
            mCommandManager.Execute(new Action.AddQuest(mStory, quest));
        }

        private void onAddStage(object sender, RoutedEventArgs e)
        {
            if (tvStory.SelectedItem == null)
                return;

            if ((tvStory.SelectedItem as TreeViewItem).Header is ModelQuest)
            {
                ModelQuest quest = (tvStory.SelectedItem as TreeViewItem).Header as ModelQuest;
                ModelStage stage = new ModelStage();
                mCommandManager.Execute(new Action.AddStage(quest, stage));
            }

            if ((tvStory.SelectedItem as TreeViewItem).Header is ModelStage)
            {
                ModelQuest quest = ((tvStory.SelectedItem as TreeViewItem).Header as ModelStage).Quest;
                ModelStage stage = new ModelStage();

                mCommandManager.Execute(new Action.AddStage(quest, stage));
            }
        }

        private void onDelItem(object sender, RoutedEventArgs e)
        {
            if (tvStory.SelectedItem == null)
                return;

            if ((tvStory.SelectedItem as TreeViewItem).Header is ModelQuest)
            {
                ModelQuest quest = (tvStory.SelectedItem as TreeViewItem).Header as ModelQuest;
                mCommandManager.Execute(new Action.DelQuest(mStory, quest));
            }

            if ((tvStory.SelectedItem as TreeViewItem).Header is ModelStage)
            {
                ModelStage stage = (tvStory.SelectedItem as TreeViewItem).Header as ModelStage;
                ModelQuest quest = stage.Quest;

                mCommandManager.Execute(new Action.DelStage(quest, stage));
            }
        }

        private void onUndo(object sender, RoutedEventArgs e)
        {
            if (mCommandManager.IsUndoPossible)
                mCommandManager.Undo();
            mPropertyGrid.Refresh();
        }

        private void onRedo(object sender, RoutedEventArgs e)
        {
            if (mCommandManager.IsRedoPossible)
                mCommandManager.Redo();
            mPropertyGrid.Refresh();
        }

        private void tvStory_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            if (tvStory.SelectedItem != null)
            {
                if ((tvStory.SelectedItem as TreeViewItem).Header is ModelQuest)
                {
                    mPropertyGrid.SelectedObject = new Proxy.ProxyQuest(mCommandManager, (tvStory.SelectedItem as TreeViewItem).Header as ModelQuest);
                }

                if ((tvStory.SelectedItem as TreeViewItem).Header is ModelStage)
                {
                    mPropertyGrid.SelectedObject = new Proxy.ProxyStage(mCommandManager, (tvStory.SelectedItem as TreeViewItem).Header as ModelStage);
                }
            }
        }
    }
}
