using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Collections;

namespace XCob
{
	public delegate void StatusDelegate(bool posssible);

	/// <summary>
	/// Абстрактный класс команды, Если необходимо создать новую отменяемую команду, нужно наследовать его от этого класса
	/// </summary>
	public abstract class Command
	{
		public abstract void Execute();
		public abstract void UnExecute();
	}

	/// <summary>
	/// Команда установления свойства
	/// </summary>
	public class SetProperty : Command
	{
		protected String mProperty;
		protected Object mObject;
		protected Object mOldValue;
		protected Object mNewValue;

		/// <summary>
		/// Конструктор создает действие изменение свойства
		/// </summary>
		/// <param name="obj">Объект-владелец свойства</param>
		/// <param name="property">Имя свойства</param>
		/// <param name="value">Новое значение свойства</param>
		public SetProperty(Object obj, String property, Object value)
		{
			mProperty = property;
			mObject = obj;
			mNewValue = value;
			mOldValue = mObject.GetType().InvokeMember(
				mProperty,
				BindingFlags.Public |
				BindingFlags.NonPublic |
				BindingFlags.Instance |
				BindingFlags.GetProperty,
				null,
				mObject,
				null
			);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="obj"></param>
		/// <param name="property"></param>
		/// <param name="value"></param>
		/// <param name="oldValue"></param>
		public SetProperty(Object obj, String property, Object value, Object oldValue)
		{
			mProperty = property;
			mObject = obj;
			mNewValue = value;
			mOldValue = oldValue;
		}

		/// <summary>
		/// Изменяет значение свойства на новое
		/// </summary>
		public override void Execute()
		{
			mObject.GetType().InvokeMember(
				mProperty,
				BindingFlags.Public |
				BindingFlags.NonPublic |
				BindingFlags.Instance |
				BindingFlags.SetProperty,
				null,
				mObject,
				new Object[] { mNewValue }
			);
		}

		/// <summary>
		/// Возвращает старое значение свойства
		/// </summary>
		public override void UnExecute()
		{
			mObject.GetType().InvokeMember(
					mProperty,
					BindingFlags.Public |
					BindingFlags.NonPublic |
					BindingFlags.Instance |
					BindingFlags.SetProperty,
					null,
					mObject,
					new Object[] { mOldValue }
				);
		}
	}

	/// <summary>
	/// Команда добавления элемента в коллекцию
	/// </summary>
	public class AddItem : Command
	{
		protected Object mItem;
		protected IList mCollection;
		protected Int32 mIndex;

		/// <summary>
		/// Конструктор создает действие добавления в коллекцию
		/// </summary>
		/// <param name="collection">Коллекция</param>
		/// <param name="item">Элемент, добавляемый в коллекцию</param>
		public AddItem(IList collection, Object item)
		{
			mItem = item;
			mCollection = collection;
			mIndex = mCollection.Count;
		}

		/// <summary>
		/// Конструктор создает действие вставки в коллекцию
		/// </summary>
		/// <param name="collection">Коллекция</param>
		/// <param name="item">Элемент, добавляемый в коллекцию</param>
		/// <param name="index">Индекс</param>
		public AddItem(IList collection, Object item, Int32 index)
		{
			mItem = item;
			mCollection = collection;
			mIndex = index;
		}

		/// <summary>
		/// 
		/// </summary>
		public override void Execute()
		{
			mCollection.Insert(mIndex, mItem);
		}

		/// <summary>
		/// 
		/// </summary>
		public override void UnExecute()
		{
			mCollection.Remove(mItem);
		}
	}

	/// <summary>
	/// Действие удаления элемента
	/// </summary>
	public class DelItem : Command
	{
		protected Object mItem;
		protected IList mCollection;
		protected Int32 mIndex;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="collection"></param>
		/// <param name="item"></param>
		public DelItem(IList collection, Object item)
		{
			mItem = item;
			mCollection = collection;
			mIndex = mCollection.IndexOf(mItem);
		}

		/// <summary>
		/// 
		/// </summary>
		/// <param name="collection"></param>
		/// <param name="index"></param>
		public DelItem(IList collection, Int32 index)
		{
			mCollection = collection;
			mIndex = index;
			mItem = mCollection[mIndex];
		}

		/// <summary>
		/// 
		/// </summary>
		public override void Execute()
		{
			mCollection.Remove(mItem);
		}

		/// <summary>
		/// 
		/// </summary>
		public override void UnExecute()
		{
			mCollection.Insert(mIndex, mItem);
		}
	}

	/// <summary>
	/// Менеджер действий. Используется для запоминания, отмены и повтора действий
	/// </summary>
	public class ActionManager
	{
		private Stack<Command> mUndoStack;
		private Stack<Command> mRedoStack;
		private Stack<Int32> mUndoCount;
		private Stack<Int32> mRedoCount;
		private bool isChanged = false;

		public event StatusDelegate OnUndoSetStatus;
		public event StatusDelegate OnRedoSetStatus;

		/// <summary>
		/// 
		/// </summary>
		public ActionManager()
		{
			mUndoStack = new Stack<Command>();
			mRedoStack = new Stack<Command>();

			mUndoStack.Push(null);
			mRedoStack.Push(null);
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
			return mUndoStack.Count > 1;
		}

		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		public bool RedoIsPossible()
		{
			return mRedoStack.Count > 1;
		}

		/// <summary>
		/// Запоминает и исполняет команду
		/// </summary>
		/// <param name="command">команда</param>
		public void ExecuteCommand(Command command)
		{
			mUndoStack.Push(command);
			command.Execute();

			IsChanged = true;
		}

		/// <summary>
		/// Финализирует команду. Каждое действие должно заканчиваться этой коммандой
		/// </summary>
		public void FinaliseCommand()
		{
			mUndoStack.Push(null);

			if (mRedoStack.Count > 1)
			{
				mRedoStack.Clear();
				mRedoStack.Push(null);
			}

			if (OnUndoSetStatus != null)
				OnUndoSetStatus(true);

			if (OnRedoSetStatus != null)
				OnRedoSetStatus(false);
		}

		/// <summary>
		/// Отменяет последнее действие
		/// </summary>
		public void Undo()
		{
			Command command;

			mUndoStack.Pop();

			while ((command = mUndoStack.Pop()) != null)
			{
				command.UnExecute();
				mRedoStack.Push(command);
			}

			mRedoStack.Push(null);
			mUndoStack.Push(null);

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
				Redo();
		}

		/// <summary>
		/// Повторяет последнее действие
		/// </summary>
		public void Redo()
		{
			Command command;

			mRedoStack.Pop();

			while ((command = mRedoStack.Pop()) != null)
			{
				command.Execute();
				mUndoStack.Push(command);
			}

			mRedoStack.Push(null);
			mUndoStack.Push(null);

			if (OnUndoSetStatus != null)
				OnUndoSetStatus(true);

			if (OnRedoSetStatus != null && mRedoStack.Count == 1)
				OnRedoSetStatus(false);

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
