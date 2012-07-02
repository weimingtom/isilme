using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace XQuest
{
	[Serializable]
	public class NamespaceManager<TEntity>
	{
		#region Members

		Dictionary<TEntity, String> mNames;
		Dictionary<String, TEntity> mObjects;
		String mPrefix;

		#endregion

		#region Properties

		public String Prefix
		{
			get { return mPrefix; }
			set { mPrefix = value; }
		}

		public List<TEntity> Entities
		{
			get { return mObjects.Values.ToList(); }
		}

		#endregion

		#region Constructor

		public NamespaceManager()
		{
			mNames = new Dictionary<TEntity, String>();
			mObjects = new Dictionary<String, TEntity>();
			mPrefix = "Name";
		}

		#endregion

		#region Methods

		/// <summary>
		/// Очистить пространство имен сущностей
		/// </summary>
		public void Clear()
		{
			mObjects.Clear();
			mNames.Clear();
		}

		/// <summary>
		/// Добавить в пространство имен новую сущность
		/// Имя генерируется автоматически
		/// </summary>
		/// <param name="entity"></param>
		public void Add(TEntity entity)
		{
			String name = mPrefix + mNames.Count;
			while (mNames.ContainsValue(name)) name += "_1";

			if (!mNames.ContainsKey(entity))
			{
				mNames.Add(entity, name);
				mObjects.Add(name, entity);
			}
		}

		/// <summary>
		/// Попытаться добавить в пространство имен сущность с заданным именем
		/// </summary>
		/// <param name="entity"></param>
		/// <param name="name"></param>
		public void Add(TEntity entity, String name)
		{
			if (!mNames.ContainsKey(entity) && !mObjects.ContainsKey(name))
			{
				mNames.Add(entity, name);
				mObjects.Add(name, entity);
			}
		}

		/// <summary>
		/// Удалить сущность из пространства имен
		/// </summary>
		/// <param name="entity"></param>
		public void Remove(TEntity entity)
		{
			mObjects.Remove(mNames[entity]);
			mNames.Remove(entity);
		}

		/// <summary>
		/// Удалить сущность из пространства имен
		/// </summary>
		/// <param name="name"></param>
		public void Remove(String name)
		{
			mNames.Remove(mObjects[name]);
			mObjects.Remove(name);
		}

		/// <summary>
		/// Получить имя сущности
		/// </summary>
		/// <param name="entity"></param>
		/// <returns></returns>
		public String GetName(TEntity entity)
		{
			return mNames[entity];
		}

		/// <summary>
		/// Получить сущность по имени
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		public TEntity GetObject(String name)
		{
			return mObjects[name];
		}

		/// <summary>
		/// Попытаться переименовать сущность
		/// </summary>
		/// <param name="entity"></param>
		/// <param name="name"></param>
		public void Rename(TEntity entity, String name)
		{
			if (!mObjects.ContainsKey(name))
			{
				Remove(entity);
				Add(entity, name);
			}
		}

		#endregion
	}
}
