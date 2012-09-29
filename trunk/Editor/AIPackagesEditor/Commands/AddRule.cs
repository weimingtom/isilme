using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using MyApplication1.Data;
using MyApplication1;

namespace MyApplication1.Commands
{
    class AddRule : ICommand
    {
        AIRulesList mList;
        AIRule mRule;

        public AddRule(AIRulesList list, AIRule rule)
        {
            mList = list;
            mRule = rule;
            mRule.Action = new AIAction();
            mRule.Action.ID = "-1";
            mRule.Priority = new Script();
            mRule.Priority.Code = "";
            mRule.Condition = new Script();
            mRule.Condition.Code = "";
            mRule.Target = new ActionTarget();
            mRule.Target.Selector = new TargetSelector();
            mRule.Target.Selector.ID = "-1";
        }

        public void Execute()
        {
            mList.Rules.Add(mRule);
        }

        public void Unexecute()
        {
            mList.Rules.Remove(mRule);
        }
    }
}
