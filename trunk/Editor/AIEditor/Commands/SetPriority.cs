using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using MyApplication1.Data;

namespace MyApplication1.Commands
{
    class SetPriority : ICommand
    {
        AIRule mRule;
        String newPriority;
        String oldPriority;
        public SetPriority(AIRule rule, String priority)
        {
            mRule = rule;
            oldPriority = rule.Priority.Code;
            newPriority = priority;
        }

        public void Execute()
        {
            mRule.Priority.Code = newPriority;
        }

        public void Unexecute()
        {
            mRule.Priority.Code = oldPriority;
        }
    }
}

