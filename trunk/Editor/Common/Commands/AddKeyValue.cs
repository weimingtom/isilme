using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Collections;

namespace Common
{
    public class AddKeyValue : ICommand
    {
        #region Members
        IDictionary mDictionary;
        Object mKey;
        Object mValue;
        #endregion

        public AddKeyValue(IDictionary dictionary, Object key, Object value)
        {
            mDictionary = dictionary;
            mKey = key;
            mValue = value;
        }

        public void Execute()
        {
            mDictionary[mKey] = mValue;
        }

        public void Unexecute()
        {
            mDictionary.Remove(mKey);
        }
    }
}
