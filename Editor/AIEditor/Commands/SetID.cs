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
        public SetID(AIRule rule, String id)
        {
        }

        public void Execute()
        {
        }

        public void Unexecute()
        {
        }
    }
}
