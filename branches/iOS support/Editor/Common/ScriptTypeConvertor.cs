using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using System.IO;

namespace Common
{
    /// <summary>
    /// А здесь поле ввода для скриптов (Недописано)
    /// </summary>
    public class ScriptTypeConvertor : StringConverter
    {
        #region Members
        List<String> mScripts = new List<String>();
        #endregion

        #region Constructors

        ScriptTypeConvertor()
        {
        }

        #endregion

        #region Methods

        void UpdateScripts()
        {
            mScripts.Clear();
            mScripts.Add("");
            mScripts.Add("[Выбрать]");
            mScripts.Add("[Новый]");

            foreach (String fileName in Directory.GetFiles(@"Scripts\"))
            {
                mScripts.Add(fileName.Remove(0, 8));
            }
        }
        #endregion

        public static void AddItem(string str)
        {
        }
        public static void Clear()
        {
        }
        public override StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
        {
            UpdateScripts();
            return new StandardValuesCollection(mScripts);
        }
        public override bool GetStandardValuesExclusive(ITypeDescriptorContext context)
        {
            return true;
        }
        public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
        {
            return true;
        }
    }

}
