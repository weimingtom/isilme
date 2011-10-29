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

        #endregion

        #region Constructors

        public ProxyStage(CommandManager commandManager, ModelStage stage) : base(commandManager)
        {
            mStage = stage;
        }

        #endregion

        #region Properties

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
                ActionManager.Execute(new SetProperty(mStage, "ID", value));
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
                ActionManager.Execute(new SetProperty(mStage, "Text", value));
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
                ActionManager.Execute(new SetProperty(mStage, "OnUpdate", value));
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
                ActionManager.Execute(new SetProperty(mStage, "OnStart", value));
                RaisePropertyChanged(this);
            }
        }

        #endregion
    }
}
