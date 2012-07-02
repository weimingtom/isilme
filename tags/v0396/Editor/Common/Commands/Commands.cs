using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Common
{
    public class Commands : ICommand
    {
        private readonly List<ICommand> mCommands = new List<ICommand>();

        public bool IsReversible
        {
            get
            {
                return true;
            }
        }

        public Commands()
        {
        }

        public void Push(ICommand command)
        {
            this.mCommands.Add(command);
        }

        public void Pop()
        {
            this.mCommands.RemoveAt(this.mCommands.Count - 1);
        }

        public void Clear()
        {
            this.mCommands.Clear();
        }

        public void Execute()
        {
            this.mCommands.ForEach((Action<ICommand>)(obj0 => obj0.Execute()));
        }

        public void Unexecute()
        {
            for (int index = this.mCommands.Count - 1; index >= 0; --index)
                this.mCommands[index].Unexecute();
        }
    }

}
