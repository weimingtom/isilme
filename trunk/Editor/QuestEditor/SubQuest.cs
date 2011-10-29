using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace XCob
{
	/// <summary>
	/// Описание стадии выполнения задания
	/// </summary>
	public class SubQuest
	{
		#region Members

		String mID;
		String mTitle;
		String mDescription;
		Dictionary<String, Ending> mEndings;

		#endregion

		#region Properties

		public String ID
		{
			get
			{
				return mID;
			}
			set
			{
				mID = value;
			}
		}

		public String Title
		{
			get
			{
				return mTitle;
			}
			set
			{
				mTitle = value;
			}
		}

		public String Description
		{
			get
			{
				return mDescription;
			}
			set
			{
				mDescription = value;
			}
		}

		#endregion

		#region Constructors

		public SubQuest()
		{
			mEndings = new Dictionary<String, Ending>();
		}

		#endregion

		#region Methods

		/// <summary>
		/// Добавить новую концовку
		/// </summary>
		/// <param name="ending">Новая концовка</param>
		public void AddEnding(Ending ending)
		{
			mEndings[ending.ID] = ending;
		}

		public void DelEnding(Ending ending)
		{
			mEndings.Remove(ending.ID);
		}

		#endregion
	}
}
