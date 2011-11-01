using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using QuestEditor.Models;
using QuestEditor.Proxy;

namespace QuestEditor.Commands
{
    public class DelQuest : ICommand
    {
        #region Members

        ProxyStory mStory;
        ProxyQuest mQuest;
        int mIndex;

        #endregion

        #region Constructors

        public DelQuest(ProxyStory story, ProxyQuest quest)
        {
            mStory = story;
            mQuest = quest;
            mIndex = mStory.Quests.IndexOf(mQuest);
        }

        #endregion

        #region Properties

        public virtual Boolean IsReversible
        {
            get
            {
                return true;
            }
        }

        #endregion

        #region Methods

        public virtual void Execute()
        {
            mStory.RemoveQuest(mQuest);
        }

        public virtual void Unexecute()
        {
            mStory.AddQuest(mQuest, mIndex);
        }

        #endregion
    }
}
