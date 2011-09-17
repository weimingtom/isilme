using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GameEditor.Models;

namespace GameEditor.Action
{
    public class AddStage : Common.ICommand
    {
        ModelQuest mQuest;
        ModelStage mStage;

        public AddStage(ModelQuest quest, ModelStage stage)
        {
            mQuest = quest;
            mStage = stage;
        }

        public virtual void Execute()
        {
            mQuest.Story.AddStage(mQuest, mStage);
        }

        public virtual void Unexecute()
        {
            mQuest.Story.RemoveStage(mQuest, mStage);
        }

        public Boolean IsReversible
        {
            get
            {
                return true;
            }
        }
    }
}
