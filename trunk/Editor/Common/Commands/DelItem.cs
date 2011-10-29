using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Collections;

namespace Common
{
    /// <summary>
    /// Действие удаления элемента
    /// </summary>
    public class DelItem : ICommand
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
        public void Execute()
        {
            mCollection.Remove(mItem);
        }

        /// <summary>
        /// 
        /// </summary>
        public void Unexecute()
        {
            mCollection.Insert(mIndex, mItem);
        }
    }
}
