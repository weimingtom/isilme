using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Reflection;
using System.IO;
using System.Xml.Linq;
using XCob;

namespace XQuest
{
    public class QuestProperties : IProperty
    {
        #region Members
        ActionManager mActionManager;
        Quest mQuest;
        #endregion

        public ActionManager ActionManager
        {
            get { return mActionManager; }
            set { mActionManager = value; }
        }

        public Object SelectedObject
        {
            get { return mQuest; }
            set { mQuest = (Quest)value; }
        }

        [DisplayName("Идентификатор")]
        public String ID
        {
            get { return mQuest.ID; }
            set
            {
                mActionManager.ExecuteCommand(new SetProperty(mQuest, "ID", value));

            }
        }

    }
}