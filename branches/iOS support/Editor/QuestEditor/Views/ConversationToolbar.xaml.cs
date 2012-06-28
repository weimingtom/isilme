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

namespace QuestEditor.Views
{
    /// <summary>
    /// Interaction logic for ConversationToolbar.xaml
    /// </summary>
    public partial class ConversationToolbar : ToolBar
    {
        static ConversationToolbar mInstance = new ConversationToolbar();

        public static ConversationToolbar Instance
        {
            get { return mInstance; }
        }

        public ConversationToolbar()
        {
            mInstance = this;

            InitializeComponent();

            mAddPhraseBtn.Command = LevelEditor.ConversationEditorCommands.AddPhrase;
        }
    }
}
