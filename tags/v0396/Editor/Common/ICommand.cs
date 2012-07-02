using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Common
{
    /// <summary>
    /// Абстрактный класс команды, Если необходимо создать новую отменяемую команду, нужно наследовать его от этого класса
    /// </summary>
    public interface ICommand
    {
        void Execute();
        void Unexecute();
    }
}
