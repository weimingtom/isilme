using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using QuestEditor.Models;

namespace QuestEditor.Commands
{
    public class DelStage : Common.ICommand
    {
        ModelQuest mQuest;
        ModelStage mStage;

        public DelStage(ModelQuest quest, ModelStage stage)
        {
            mQuest = quest;
            mStage = stage;
        }

        public virtual void Execute()
        {
            mQuest.Story.RemoveStage(mQuest, mStage);
        }

        public virtual void Unexecute()
        {
            mQuest.Story.AddStage(mQuest, mStage);
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
