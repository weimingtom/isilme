using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Linq;
using System.Collections.ObjectModel;

namespace QuestEditor.Models
{
    public class QuestEvtArgs : EventArgs
    {
        public ModelQuest Quest
        {
            get;
            set;
        }

        public ModelStage Stage
        {
            get;
            set;
        }

        public ModelStory Story
        {
            get;
            set;
        }
    }

    public class ModelStory
    {
        #region Members

        List<ModelQuest> mQuests = new List<ModelQuest>();

        #endregion

        #region Constructors

        public ModelStory()
        {
        }

        #endregion

        #region Prperties

        public List<ModelQuest> Quests
        {
            get
            {
                return mQuests;
            }
            private set
            {
                mQuests = value;
            }
        }

        #endregion

        #region Methods

        public void Load(XElement storyElement)
        {
            foreach (XElement questElement in storyElement.Elements("Quest"))
            {
                ModelQuest quest = new ModelQuest();
                Quests.Add(quest);

                XAttribute nameAttr = questElement.Attribute("Name");
                XAttribute titleAttr = questElement.Attribute("Title");
                XAttribute startScriptAttr = questElement.Attribute("StartScript");
                XAttribute finishScriptAttr = questElement.Attribute("FinishScript");
                XAttribute updateScriptAttr = questElement.Attribute("UpdateScript");

                quest.ID = nameAttr.Value;
                quest.Title = titleAttr.Value;
                quest.OnStart = startScriptAttr.Value;
                quest.OnFinish = finishScriptAttr.Value;
                quest.OnUpdate = updateScriptAttr.Value;

                foreach (XElement stageElement in questElement.Elements("Stage"))
                {
                    ModelStage stage = new ModelStage();
                    quest.Stages.Add(stage);

                    XAttribute idAttr = stageElement.Attribute("ID");
                    XAttribute textAttr = stageElement.Attribute("Text");
                    XAttribute stageStartScriptAttr = stageElement.Attribute("StartScript");
                    XAttribute stageUpdateScriptAttr = stageElement.Attribute("UpdateScript");

                    stage.ID = int.Parse(idAttr.ToString());
                    stage.Text = textAttr.Value;
                    stage.OnStart = stageStartScriptAttr.Value;
                    stage.OnUpdate = stageUpdateScriptAttr.Value;
                }
            }
        }

        public XElement Save()
        {
            XElement storyElement = new XElement("Story");

            foreach (ModelQuest quest in Quests)
            {
                XElement questElement = new XElement("Quest");
                storyElement.Add(questElement);

                questElement.SetAttributeValue("Name", quest.ID);
                questElement.SetAttributeValue("Title", quest.Title);
                questElement.SetAttributeValue("StartScript", quest.OnStart);
                questElement.SetAttributeValue("FinishScript", quest.OnFinish);
                questElement.SetAttributeValue("UpdateScript", quest.OnUpdate);

                foreach (ModelStage stage in quest.Stages)
                {
                    XElement stageElement = new XElement("Stage");
                    questElement.Add(stageElement);

                    stageElement.SetAttributeValue("ID", stage.ID);
                    stageElement.SetAttributeValue("Text", stage.Text);
                    stageElement.SetAttributeValue("StartScript", stage.OnStart);
                    stageElement.SetAttributeValue("UpdateScript", stage.OnUpdate);
                }
            }
            return storyElement;
        }

        public void AddQuest(ModelQuest quest, int postion = -1)
        {
            if (postion == -1 || postion == Quests.Count)
                Quests.Add(quest);
            else
                Quests.Insert(postion, quest);

            OnQuestAdded(quest);
        }

        public void RemoveQuest(ModelQuest quest)
        {
            Quests.Remove(quest);
            OnQuestRemoved(quest);
        }

        public void AddStage(ModelQuest quest, ModelStage stage)
        {
            quest.Stages.Add(stage);
            OnStageAdded(quest, stage);
        }

        public void RemoveStage(ModelQuest quest, ModelStage stage)
        {
            quest.Stages.Remove(stage);
            OnStageRemoved(quest, stage);
        }

        void OnQuestAdded(ModelQuest quest)
        {
            quest.Story = this;

            if (QuestAdded != null)
            {
                QuestEvtArgs e = new QuestEvtArgs();
                e.Quest = quest;
                e.Story = this;
                QuestAdded(this, e);
            }
        }

        void OnQuestRemoved(ModelQuest quest)
        {
            quest.Story = null;

            if (QuestRemoved != null)
            {
                QuestEvtArgs e = new QuestEvtArgs();
                e.Quest = quest;
                e.Story = this;
                QuestRemoved(this, e);
            }
        }

        void OnStageAdded(ModelQuest quest, ModelStage stage)
        {
            stage.Quest = quest;
            if (StageAdded != null)
            {
                QuestEvtArgs e = new QuestEvtArgs();
                e.Quest = quest;
                e.Story = this;
                e.Stage = stage;
                StageAdded(this, e);
            }

        }

        void OnStageRemoved(ModelQuest quest, ModelStage stage)
        {
            stage.Quest = null;
            if (StageRemoved != null)
            {
                QuestEvtArgs e = new QuestEvtArgs();
                e.Quest = quest;
                e.Story = this;
                e.Stage = stage;
                StageRemoved(this, e);
            }
        }

        #endregion

        #region Events

        public event EventHandler<QuestEvtArgs> QuestAdded;

        public event EventHandler<QuestEvtArgs> QuestRemoved;

        public event EventHandler<QuestEvtArgs> StageAdded;

        public event EventHandler<QuestEvtArgs> StageRemoved;

        #endregion
    }
}
