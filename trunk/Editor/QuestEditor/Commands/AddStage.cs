using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using QuestEditor.Models;
using QuestEditor.Proxy;

namespace QuestEditor.Commands
{
    public class AddStage : Common.ICommand
    {
        ProxyQuest mQuest;
        ProxyStage mStage;

        public AddStage(ProxyQuest quest, ProxyStage stage)
        {
            mQuest = quest;
            mStage = stage;
        }

        public virtual void Execute()
        {
            mQuest.AddStage(mStage);
        }

        public virtual void Unexecute()
        {
            mQuest.RemoveStage(mStage);
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
