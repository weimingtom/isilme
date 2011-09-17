using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using Common;
using GameEditor.Models;
using GameEditor.Views;

namespace GameEditor.Proxy
{
    public class ProxyQuest : ProxyObject
    {
        ModelQuest mQuest;

        public ProxyQuest(CommandManager commandManager, ModelQuest quest) : base(commandManager)
        {
            mQuest = quest;
        }

        public String Title
        {
            get
            {
                return mQuest.Title;
            }
            set
            {
                CommandManager.Execute(new Action.SetProperty(mQuest, "Title", value));
            }
        }

        public String ID
        {
            get
            {
                return mQuest.ID;
            }
            set
            {
                CommandManager.Execute(new Action.SetProperty(mQuest, "ID", value));
            }
        }

        public String OnStart
        {
            get
            {
                return mQuest.OnStart;
            }
            set
            {
                CommandManager.Execute(new Action.SetProperty(mQuest, "OnStart", value));
            }
        }

        public String OnUpdate
        {
            get
            {
                return mQuest.OnUpdate;
            }
            set
            {
                CommandManager.Execute(new Action.SetProperty(mQuest, "OnUpdate", value));
            }
        }

        public String OnFinish
        {
            get
            {
                return mQuest.OnFinish;
            }
            set
            {
                CommandManager.Execute(new Action.SetProperty(mQuest, "OnFinish", value));
            }
        }
    }
}
