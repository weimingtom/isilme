using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using QuestEditor.Models;

namespace QuestEditor.Commands
{
    public class AddQuest : ICommand
    {
        #region Members

        ModelStory mStory;
        ModelQuest mQuest;

        #endregion

        #region Constructors

        public AddQuest(ModelStory story, ModelQuest quest)
        {
            mStory = story;
            mQuest = quest;
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
            mStory.AddQuest(mQuest);
        }

        public virtual void Unexecute()
        {
            mStory.RemoveQuest(mQuest);
        }

        #endregion
    }
}
