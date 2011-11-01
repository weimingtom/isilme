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

        CommandManager CommandManager
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

		#endregion

		#region File

        void Load();

		/// <summary>
		/// Сохранить как
		/// </summary>
		/// <param name="fileName"></param>
		void  SaveAs(String fileName);

		/// <summary>
		/// Сохранить
		/// </summary>
		/// <returns></returns>
		void Save();

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

		#endregion
        
		event EditorSelectionEventHandler SelectionChanged;
	}
}
