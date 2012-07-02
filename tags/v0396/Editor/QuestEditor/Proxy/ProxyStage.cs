using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using QuestEditor.Models;
using System.ComponentModel;
using System.Drawing.Design;
using Common;
//using LuaEditor.Views;

namespace QuestEditor.Proxy
{
    public class ProxyStage : ProxyObject
    {
        #region Members

        ModelStage mStage;
        ProxyQuest mParent;

        #endregion

        #region Constructors

        public ProxyStage(ModelStage stage)
        {
            mStage = stage;
        }

        #endregion

        #region Properties

        [Browsable(false)]
        public ModelStage Value
        {
            get
            {
                return mStage;
            }
        }

        [Browsable(false)]
        public ProxyQuest Parent
        {
            get
            {
                return mParent;
            }
            set
            {
                mParent = value;
                mStage.Quest = value == null ? null : mParent.Value;
            }
        }

        [Browsable(false)]
        public ModelStage Stage
        {
            get
            {
                return mStage;
            }
        }

        [DisplayName("Иденифкатор")]
        [Description("Идентификатор стадии.")]
        public int ID
        {
            get
            {
                return mStage.ID;
            }
            set
            {
                CurrentCommand = new SetProperty(this, mStage, "ID", value);
                RaisePropertyChanged(this);
            }
        }

        [DisplayName("Текст")]
        [Description("Запись в дневник")]
        public String Text
        {
            get
            {
                return mStage.Text;
            }
            set
            {
                CurrentCommand = new SetProperty(this, mStage, "Text", value);
                RaisePropertyChanged(this);
            }
        }

 //       [Editor(typeof(ScriptUIEditor), typeof(UITypeEditor))]
        public String OnUpdate
        {
            get
            {
                return mStage.OnUpdate;
            }
            set
            {
                CurrentCommand = new SetProperty(this, mStage, "OnUpdate", value);
                RaisePropertyChanged(this);
            }
        }

  //      [Editor(typeof(ScriptUIEditor), typeof(UITypeEditor))]
        public String OnStart
        {
            get
            {
                return mStage.OnStart;
            }
            set
            {
                CurrentCommand = new SetProperty(this, mStage, "OnStart", value);
                RaisePropertyChanged(this);
            }
        }

        #endregion
    }
}
