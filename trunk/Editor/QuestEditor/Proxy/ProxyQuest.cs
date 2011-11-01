using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
using Common;
using QuestEditor.Models;
using System.Collections.ObjectModel;

namespace QuestEditor.Proxy
{
    public class ProxyQuest : ProxyObject
    {
        #region Members

        ModelQuest mQuest;
        ProxyStory mParent;

        #endregion

        [Browsable(false)]
        public ModelQuest Value
        {
            get
            {
                return mQuest;
            }
        }

        [Browsable(false)]
        public ProxyStory Parent
        {
            get
            {
                return mParent;
            }
            set
            {
                mParent = value;
                mQuest.Story = value == null ? null : value.Value;
            }
        }

        public ProxyQuest(CommandManager commandManager, ModelQuest quest) : base(commandManager)
        {
            Stages = new ObservableCollection<ProxyStage>();
            mQuest = quest;
        }

        #region Methods

        public ProxyStage CreateNewStage()
        {
            return new ProxyStage(ActionManager, new ModelStage() { ID = 0 });
        }

        public void AddStage(ProxyStage stage)
        {
            Stages.Add(stage);
            Value.Stages.Add(stage.Value);
            stage.Parent = this;
        }

        public void RemoveStage(ProxyStage stage)
        {
            Stages.Remove(stage);
            Value.Stages.Remove(stage.Value);
            stage.Parent = null;
        }

        #endregion

        [Browsable(false)]
        public ObservableCollection<ProxyStage> Stages
        {
            get;
            set;
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
