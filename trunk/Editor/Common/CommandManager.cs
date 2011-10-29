using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Collections;


namespace Common
{
    /// <summary>
    /// Менеджер действий. Используется для запоминания, отмены и повтора действий
    /// </summary>
    public class CommandManager
    {
        private Stack<ICommand> mUndoStack;
        private Stack<ICommand> mRedoStack;
        private Stack<Int32> mUndoCount;
        private Stack<Int32> mRedoCount;
        private bool isChanged = false;

        public event StatusDelegate OnUndoSetStatus;
        public event StatusDelegate OnRedoSetStatus;

        /// <summary>
        /// 
        /// </summary>
        public CommandManager()
        {
            mUndoStack = new Stack<ICommand>();
            mRedoStack = new Stack<ICommand>();
        }

        public bool IsChanged
        {
            get
            {
                return isChanged;
            }
            set
            {
                isChanged = value;
                if (DocumentChanged != null)
                {
                    DocumentChanged(this, null);
                }

            }
        }

        /// <summary>
        /// 
        /// </summary>
        public void Clear()
        {
            mUndoStack.Clear();
            mUndoStack.Push(null);

            if (OnUndoSetStatus != null)
                OnUndoSetStatus(false);

            mRedoStack.Clear();
            mRedoStack.Push(null);

            if (OnRedoSetStatus != null)
                OnRedoSetStatus(false);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public bool UndoIsPossible()
        {
            return mUndoStack.Count > 0;
        }

        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public bool RedoIsPossible()
        {
            return mRedoStack.Count > 0;
        }

        /// <summary>
        /// Запоминает и исполняет команду
        /// </summary>
        /// <param name="command">команда</param>
        public void Execute(ICommand command)
        {
            mUndoStack.Push(command);
            mRedoStack.Clear();
            command.Execute();

            IsChanged = true;
        }

        /// <summary>
        /// Финализирует команду. Каждое действие должно заканчиваться этой коммандой
        /// </summary>
        public void FinaliseCommand()
        {

        }

        /// <summary>
        /// Отменяет последнее действие
        /// </summary>
        public void Undo()
        {
            if (!UndoIsPossible())
                return;

            ICommand command = mUndoStack.Pop();
            command.Unexecute();
            mRedoStack.Push(command);

            if (OnRedoSetStatus != null)
                OnRedoSetStatus(true);

            if (OnUndoSetStatus != null && mUndoStack.Count == 1)
                OnUndoSetStatus(false);

            IsChanged = true;
        }

        /// <summary>
        /// Отменяет последние несколько действий
        /// </summary>
        /// <param name="count">количество действий</param>
        public void Undo(Int32 count)
        {
            for (int i = 0; i < count; ++i)
                Undo();
        }

        /// <summary>
        /// Повторяет последнее действие
        /// </summary>
        public void Redo()
        {
            ICommand command = mRedoStack.Pop();
            command.Execute();
            mUndoStack.Push(command);
            IsChanged = true;
        }

        /// <summary>
        /// Повторяет несколько действий
        /// </summary>
        /// <param name="count">количество действий</param>
        public void Redo(Int32 count)
        {
            for (int i = 0; i < count; ++i)
                Redo();
        }

        public event EventHandler DocumentChanged;
    }
}
