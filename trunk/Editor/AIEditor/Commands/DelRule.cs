using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using MyApplication1.Data;

namespace MyApplication1.Commands
{
    class DelRule : ICommand
    {
        AIRulesList mList;
        AIRule mRule;

        public DelRule(AIRulesList list, AIRule rule)
        {
            mList = list;
            mRule = rule;
        }

        public void Execute()
        {
            mList.Rules.Remove(mRule);
        }

        public void Unexecute()
        {
            mList.Rules.Add(mRule);
        }
    }
}
