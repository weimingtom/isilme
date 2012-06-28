using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Collections;

namespace Common
{

    /// <summary>
    /// Команда добавления элемента в коллекцию
    /// </summary>
    public class AddItem : ICommand
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
        public void Execute()
        {
            mCollection.Insert(mIndex, mItem);
        }

        /// <summary>
        /// 
        /// </summary>
        public void Unexecute()
        {
            mCollection.Remove(mItem);
        }
    }
}
