using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Common
{
    class Singleton<T> where T :class, new()
    {
        private static T mInstance = null;

        protected Singleton()
        {
            mInstance = this as T;
        }

        public static T Instance
        {
            get
            {
                if (mInstance == null)
                {
                   mInstance = new T();
                }

                return mInstance;
            }
        }
    }
}
