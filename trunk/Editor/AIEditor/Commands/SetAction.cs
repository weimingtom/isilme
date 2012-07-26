using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using MyApplication1.Data;

namespace MyApplication1.Commands
{
    class SetAction : ICommand
    {
        AIRule mRule;
        String newActionID;
        String oldActionID;
        public SetAction(AIRule rule, String ActionID)
        {
            mRule = rule;
            newActionID = ActionID;
            oldActionID = rule.Action.ID;
        }

        public void Execute()
        {
            mRule.Action.ID = newActionID;
        }

        public void Unexecute()
        {
            mRule.Action.ID = oldActionID;
        }
    }
}