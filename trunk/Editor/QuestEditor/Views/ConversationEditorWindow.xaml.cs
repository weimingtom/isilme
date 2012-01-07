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
using Common;
using Common.Views;
using LevelEditor;
using LevelEditor.Proxy;
using LevelEditor.Commands;
using System.Collections.ObjectModel;

namespace QuestEditor.Views
{
    /// <summary>
    /// Interaction logic for ConversationEditorWindow.xaml
    /// </summary>
    public partial class ConversationEditorWindow : EditorWindow
    {
        public ConversationEditorWindow()
        {
            InitializeComponent();

            mConversation = new ConversationProxy();

            mConvesationTree.DataContext = mConversation;
            ConversationEditorCommands.AddPhrase.CanExecuteTargets += new Func<bool>(AddPhrase_CanExecuteTargets);
            ConversationEditorCommands.AddPhrase.ExecuteTargets += new Action<object>(AddPhrase_ExecuteTargets);
        }

        public override void Load()
        {
            mConversation = ConversationProxy.Load(FileName);

            mConvItem.DataContext = mConversation;

        }

        public override void Save()
        {
            mConversation.SaveToFile(FileName);
        }

        void AddPhrase_ExecuteTargets(object obj)
        {
            if (mConvesationTree.SelectedItem is PhraseProxy)
            {
                PhraseProxy phrase = new PhraseProxy();
                phrase.Text = "Text";
                CommandManager.Execute(new AddPhrase(mConvesationTree.SelectedItem as PhraseProxy, phrase));
            }
            else
            {
                PhraseProxy phrase = new PhraseProxy();
                phrase.Text = "Text";
                CommandManager.Execute(new AddPhrase(mConversation, phrase));
            }
        }

        bool AddPhrase_CanExecuteTargets()
        {
            return true;
        }

        ConversationProxy mConversation;
    }
}
