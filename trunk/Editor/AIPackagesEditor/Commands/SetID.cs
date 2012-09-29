using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using MyApplication1.Data;

namespace MyApplication1.Commands
{
    class SetID : ICommand
    {
        AIRule mRule;
        String newID;
        String oldID;
        public SetID(AIRule rule, String id)
        {
            mRule = rule;
            oldID = rule.ID;
            newID = id;
        }

        public void Execute()
        {
            mRule.ID = newID;
        }

        public void Unexecute()
        {
            mRule.ID = oldID;
        }
    }
}
