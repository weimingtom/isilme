using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using MyApplication1.Data;

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
