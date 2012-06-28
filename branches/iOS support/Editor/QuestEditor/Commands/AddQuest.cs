using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using QuestEditor.Models;
using QuestEditor.Proxy;

namespace QuestEditor.Commands
{
    public class AddQuest : ICommand
    {
        #region Members

        ProxyStory mStory;
        ProxyQuest mQuest;

        #endregion

        #region Constructors

        public AddQuest(ProxyStory story, ProxyQuest quest)
        {
            mStory = story;
            mQuest = quest;
        }

        #endregion

        #region Properties


        #endregion

        #region Methods

        public virtual void Execute()
        {
            mStory.AddQuest(mQuest);
        }

        public virtual void Unexecute()
        {
            mStory.RemoveQuest(mQuest);
        }

        #endregion
    }
}
