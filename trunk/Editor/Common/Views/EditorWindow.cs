using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using AvalonDock;
using Common;

namespace Common.Views
{
    /// <summary>
    /// Interaction logic for ToolWindow.xaml
    /// </summary>
    public class EditorWindow : DockableContent
    {
        #region Commands

        protected virtual void ExecutedUndoCommand(object sender, ExecutedRoutedEventArgs e)
        {
            Undo();
        }

        protected virtual void CanExecuteUndoCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            EditorWindow target = sender as EditorWindow;

            if (target != null)
            {
                e.CanExecute = target.IsUndoEnabled; ;
            }
            else
            {
                e.CanExecute = false;
            }
        }

        protected virtual void ExecutedRedoCommand(object sender, ExecutedRoutedEventArgs e)
        {
            Redo();
        }

        protected virtual void CanExecuteRedoCommand(object sender, CanExecuteRoutedEventArgs e)
        {
            EditorWindow target = sender as EditorWindow;

            if (target != null)
            {
                e.CanExecute = target.IsRedoEnabled; ;
            }
            else
            {
                e.CanExecute = false;
            }
        }


        #endregion

        #region Members

        IProxyObject mSelectedObject = null;
        IProxyObject[] mSelectedObjects = null;

        /// <summary>
        /// Менеджер комманд редактора
        /// </summary>
        CommandManager mCommandManager = new CommandManager();

        /// <summary>
        /// Имя файла
        /// </summary>
        String mFileName = "";

        #endregion

        public EditorWindow()
        {
            CommandBindings.Add(new CommandBinding(ApplicationCommands.Undo, ExecutedUndoCommand, CanExecuteUndoCommand));
            CommandBindings.Add(new CommandBinding(ApplicationCommands.Redo, ExecutedRedoCommand, CanExecuteRedoCommand));
        }

        #region Methods

        /// <summary>
        /// Открывает документ
        /// </summary>
        public virtual void Load()
        {
        }

        /// <summary>
        /// Сохраняет документ
        /// </summary>
        public virtual void Save()
        {
        }

        /// <summary>
        /// Сохраняет документ с другим именем
        /// </summary>
        /// <param name="fileName"></param>
        public void SaveAs(String fileName)
        {
            FileName = fileName;
            Save();
        }

        /// <summary>
        /// Отменить последнее действие
        /// </summary>
        public virtual void Undo()
        {
            CommandManager.Undo();
        }

        /// <summary>
        /// Повторить отмененное действие
        /// </summary>
        public virtual void Redo()
        {
            CommandManager.Redo();
        }

        /// <summary>
        /// Инициирует событие по смене активного объекта
        /// </summary>
        protected void RaiseSelectionChanged()
        {
            if (SelectionChanged != null)
            {
                EditorSelectionEventArgs e = new EditorSelectionEventArgs();
                e.SelectedObject = SelectedObject;
                
                SelectionChanged(this, e);
            }
        }

        #endregion

        #region Proeprties

        /// <summary>
        /// Возвращает менеджер комманд
        /// </summary>
        public CommandManager CommandManager
        {
            get { return mCommandManager; }
        }

        /// <summary>
        /// Возвращает имя файла
        /// </summary>
        public String FileName
        {
            get
            {
                return mFileName;
            }
            set
            {
                mFileName = value;
                Title = System.IO.Path.GetFileNameWithoutExtension(mFileName);
            }
        }

        public virtual Boolean IsUndoEnabled
        {
            get { return CommandManager.UndoIsPossible(); }
        }

        public virtual Boolean IsRedoEnabled
        {
            get { return CommandManager.RedoIsPossible(); }
        }

        public IProxyObject SelectedObject
        {
            get 
            { 
                return mSelectedObject; 
            }
            set
            {
                mSelectedObject = value;
                mSelectedObjects = null;
                RaiseSelectionChanged();
            }
        }

        public IProxyObject[] SelectedObjects
        {
            get
            {
                return mSelectedObjects;
            }
            set
            {
                mSelectedObjects = value;
                mSelectedObject = null;
                RaiseSelectionChanged();
            }
        }

        #endregion

        #region Events

        /// <summary>
        /// Вызывается при смене выделенного объекта
        /// </summary>
        public event EditorSelectionEventHandler SelectionChanged;

        #endregion
    }
}
