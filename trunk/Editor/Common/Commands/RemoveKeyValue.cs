using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Collections;

namespace Common
{
    public class RemoveKeyValue : ICommand
    {
        #region Members
        IDictionary mDictionary;
        Object mKey;
        Object mValue;
        #endregion

        public RemoveKeyValue(IDictionary dictionary, Object key)
        {
            mDictionary = dictionary;
            mKey = key;
            mValue = mDictionary[mKey];
        }

        public void Execute()
        {
            mDictionary.Remove(mKey);
        }

        public void Unexecute()
        {
            mDictionary[mKey] = mValue;
        }
    }
}
