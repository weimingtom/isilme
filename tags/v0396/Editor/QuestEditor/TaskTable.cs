using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace XQuest
{
	public class TaskTable : DataGridView
	{
		#region Members

		List<Task> mTasks; // Задания которые надо редактировать
		DataGridViewComboBoxColumn mIDColumn;
		DataGridViewTextBoxColumn mTitleColumn;
		#endregion

		#region Constructors

		public TaskTable()
		{
			mIDColumn = new DataGridViewComboBoxColumn();
			mIDColumn.HeaderText = "ID";
			mTitleColumn = new DataGridViewTextBoxColumn();
			mTitleColumn.ReadOnly = true;
			mTitleColumn.HeaderText = "Заголовок";			
			
			Columns.AddRange(new DataGridViewColumn[] { mIDColumn, mTitleColumn });

			AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill;
		}

		#endregion

		#region Properties

		/// <summary>
		/// Список задач, добавленных в таблицу.
		/// </summary>
		public List<Task> TaskList
		{
			get { return mTasks; }
			set 
			{ 
				mTasks = null;
				mIDColumn.DataSource = Task.AllID;
				Rows.Clear();
				mTasks = value;
				if (mTasks == null)
					return;
				foreach (Task task in mTasks)
				{
					Rows.Add(new object[] { task.ID, task.Title});
				}
			}
		}

		#endregion

		#region Event Handlers

		protected override void OnCellEndEdit(DataGridViewCellEventArgs e)
		{
			// Изменилось значение 
			Task task = Task.Tasks[(String)(Rows[e.RowIndex].Cells[e.ColumnIndex].Value)];
			if (e.RowIndex < mTasks.Count)
				mTasks[e.RowIndex] = task;
			else
				mTasks.Add(task);

			Rows[e.RowIndex].Cells[1].Value = task.Title;

			base.OnCellEndEdit(e);
		}

		protected override void OnCellBeginEdit(DataGridViewCellCancelEventArgs e)
		{
			mIDColumn.DataSource = Task.AllID; // Доступные задачи
			base.OnCellBeginEdit(e);
		}

		protected override void OnRowsRemoved(DataGridViewRowsRemovedEventArgs e)
		{
			if (mTasks != null)
			{
				for (int d = 0; d < e.RowCount; ++d)
					mTasks.RemoveAt(e.RowIndex + d);
			}

			base.OnRowsRemoved(e);
		}

		#endregion
	}
}
