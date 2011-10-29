using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using Common;
using QuestEditor.Models;

namespace QuestEditor.Proxy
{
    public class ProxyQuest : ProxyObject
    {
        ModelQuest mQuest;

        [Browsable(false)]
        public ModelQuest Quest
        {
            get
            {
                return mQuest;
            }
        }

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
                ActionManager.Execute(new SetProperty(mQuest, "Title", value));
                RaisePropertyChanged(this);
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
                ActionManager.Execute(new SetProperty(mQuest, "ID", value));
                RaisePropertyChanged(this);
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
                ActionManager.Execute(new SetProperty(mQuest, "OnStart", value));
                RaisePropertyChanged(this);
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
                ActionManager.Execute(new SetProperty(mQuest, "OnUpdate", value));
                RaisePropertyChanged(this);
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
                ActionManager.Execute(new SetProperty(mQuest, "OnFinish", value));
                RaisePropertyChanged(this);
            }
        }
    }
}
