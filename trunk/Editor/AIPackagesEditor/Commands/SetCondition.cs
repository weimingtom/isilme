using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using MyApplication1.Data;

namespace MyApplication1.Commands
{
    class SetCondition : ICommand
    {
        AIRule mRule;
        String newCondition;
        String oldCondition;
        public SetCondition(AIRule rule, String condition)
        {
            mRule = rule;
            oldCondition = rule.Condition.Code;
            newCondition = condition;
        }

        public void Execute()
        {
            mRule.Condition.Code = newCondition;
        }

        public void Unexecute()
        {
            mRule.Condition.Code = oldCondition;
        }
    }
}
