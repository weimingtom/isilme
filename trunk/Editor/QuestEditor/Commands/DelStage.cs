using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using QuestEditor.Models;
using QuestEditor.Proxy;

namespace QuestEditor.Commands
{
    public class DelStage : Common.ICommand
    {
        ProxyQuest mQuest;
        ProxyStage mStage;

        public DelStage(ProxyQuest quest, ProxyStage stage)
        {
            mQuest = quest;
            mStage = stage;
        }

        public virtual void Execute()
        {
            mQuest.RemoveStage(mStage);
        }

        public virtual void Unexecute()
        {
            mQuest.AddStage(mStage);
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
