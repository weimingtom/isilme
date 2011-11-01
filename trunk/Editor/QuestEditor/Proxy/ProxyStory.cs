using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;
using Common;
using QuestEditor.Models;

namespace QuestEditor.Proxy
{
    public class ProxyStory : ProxyObject
    {
        ModelStory mStory = null;

        public ModelStory Value
        {
            get { return mStory; }
        }

        public ProxyStory(ModelStory story)
        {
            mStory = story;
            Quests = new ObservableCollection<ProxyQuest>();
        }


        public ObservableCollection<ProxyQuest> Quests
        {
            get;
            set;
        }

        public void AddQuest(ProxyQuest quest, int index = -1)
        {
            if (index == -1 || index >= Quests.Count)
            {
                Quests.Add(quest);
                Value.Quests.Add(quest.Value);
            }
            else
            {
                Quests.Insert(index, quest);
                Value.Quests.Insert(index, quest.Value);
            }
            quest.Parent = this;
        }

        public void RemoveQuest(ProxyQuest quest)
        {
            Quests.Remove(quest);
            Value.Quests.Remove(quest.Value);
            quest.Parent = null;
        }

        public ProxyQuest CreateNewQuest()
        {
            return new ProxyQuest(new ModelQuest() { Title = "Test" });
        }
    }
}
