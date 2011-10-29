using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Common.Views
{

	/// <summary>
	/// Интерфейс для формы редактора (который бдет привязан к luaeditor и questeditor)
	/// </summary>
	public interface IEditorWindow
	{
		#region Properties

        CommandManager ActionManager
        {
            get;
        }

		/// <summary>
		/// Полное имя файла
		/// </summary>
		string FileName
		{
			get;
		}

        IProxyObject SelectedObject
        {
            get;
        }

        IProxyObject[] SelectedObjects
        {
            get;
        }
		/// <summary>
		/// Редактируемый файл был изменен
		/// </summary>
		bool IsChanged
		{
			get;
		}

		bool UndoEnabled
		{
			get;
		}

		bool RedoEnabled
		{
			get;
		}

		bool PrintEnabled
		{
			get;
		}

		bool PreviewEnabled
		{
			get;
		}

		bool CutEnabled
		{
			get;
		}

		bool CopyEnabled
		{
			get;
		}

		bool PasteEnabled
		{
			get;
		}

		#endregion

		#region File

		/// <summary>
		/// Загружает инфорамцию из файла
		/// </summary>
		/// <param name="fileName"></param>
		void Open(String fileName);

		/// <summary>
		/// Сохранить как
		/// </summary>
		/// <param name="fileName"></param>
		bool SaveAs();

		/// <summary>
		/// Сохранить
		/// </summary>
		/// <returns></returns>
		bool Save();

		#endregion

		#region Edit

		/// <summary>
		/// Отменить
		/// </summary>
		void Undo();

		/// <summary>
		/// Повторить
		/// </summary>
		void Redo();

		void Copy();

		void Cut();

		void Paste();

		void SelectAll();

		void Deselect();

		void Print();

		void Preview();

		#endregion

		event EventHandler DocumentChanged;

		event EditorSelectionEventHandler SelectionChanged;
	}
}
