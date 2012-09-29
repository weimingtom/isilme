using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using MyApplication1.Data;

namespace MyApplication1.Commands
{
    class SetTargetSelector : ICommand
    {
        AIRule mRule;
        String newTargetID;
        String oldTargetID;
        public SetTargetSelector(AIRule rule, String TargetID)
        {
            mRule = rule;
            newTargetID = TargetID;
            oldTargetID = rule.Target.Selector.ID;
        }

        public void Execute()
        {
            mRule.Target.Selector.ID = newTargetID;
        }

        public void Unexecute()
        {
            mRule.Target.Selector.ID = oldTargetID;
        }
    }
}
