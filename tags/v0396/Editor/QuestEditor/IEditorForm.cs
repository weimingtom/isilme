using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace XCob
{

	/// <summary>
	/// Интерфейс для формы редактора (который бдет привязан к luaeditor и questeditor)
	/// </summary>
	public interface IEditorForm
	{
		/// <summary>
		/// Полное имя файла
		/// </summary>
		string FileName
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

		/// <summary>
		/// Отменить
		/// </summary>
		void Undo();

		/// <summary>
		/// Повторить
		/// </summary>
		void Redo();
	}
}
