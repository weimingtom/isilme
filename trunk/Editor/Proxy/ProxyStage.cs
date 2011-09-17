using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GameEditor.Models;
using GameEditor.Views;
using System.ComponentModel;
using System.Drawing.Design;
using Common;

namespace GameEditor.Proxy
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
                CommandManager.Execute(new Action.SetProperty(mStage, "ID", value));
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
                CommandManager.Execute(new Action.SetProperty(mStage, "Text", value));
            }
        }

        [Editor(typeof(ScriptUIEditor), typeof(UITypeEditor))]
        public String OnUpdate
        {
            get
            {
                return mStage.OnUpdate;
            }
            set
            {
                CommandManager.Execute(new Action.SetProperty(mStage, "OnUpdate", value));
            }
        }

        [Editor(typeof(ScriptUIEditor), typeof(UITypeEditor))]
        public String OnStart
        {
            get
            {
                return mStage.OnStart;
            }
            set
            {
                CommandManager.Execute(new Action.SetProperty(mStage, "OnStart", value));
            }
        }

        #endregion
    }
}
