using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml.Linq;
using LuaInterface;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;

namespace XQuest
{
	public class Story
	{
		public Story()
		{
			mScript = "";
		}

		#region Members Serialise
		String mScript;
		NamespaceManager<Quest> mQNamespace = new NamespaceManager<Quest>();
		NamespaceManager<Task> mTNamespace = new NamespaceManager<Task>();
		#endregion

		#region Members NonSerialise

		List<Quest> mActiveQuests = new List<Quest>();
		Lua mLua = null;

		#endregion

		#region Properties

		/// <summary>
		/// Интерпретатор Lua, для запуска скриптов
		/// </summary>
		public Lua LuaInterpreter
		{
			get { return mLua; }
			set { mLua = value; }
		}

		public List<Quest> Quests
		{
			get { return mQNamespace.Entities; }
		}

		public List<Task> Tasks
		{
			get { return mTNamespace.Entities; }
		}

		public String Script
		{
			get { return mScript; }
			set { mScript = value; }
		}

		/// <summary>
		/// Список активных зданий. 
		/// </summary>
		public List<Quest> ActiveQuests
		{
			get { return mActiveQuests; }
			set { mActiveQuests = value; }
		}

		#endregion

		#region Methods

		public void Add(Quest quest)
		{
			mQNamespace.Add(quest, quest.ID);

			// Оповестить наблюдателей
			if (QuestAdded != null)
				QuestAdded(quest);
		}

		public void Remove(Quest quest)
		{
			mQNamespace.Remove(quest);

			// Оповестить наблюдателей
			if (QuestRemoved != null)
				QuestRemoved(quest);
		}

		public void Clear()
		{
			mQNamespace.Clear();
			mTNamespace.Clear();
		}

		public void Open(String XML)
		{
			Clear();
			//LoadData(XML);
			XDocument xmlDocument = XDocument.Load(XML);
			XElement root = xmlDocument.Element("Quests");
			LoadAll(root);
		}

		public void Save(String XML)
		{
			//SaveData(XML);
			XElement element = SaveAll();
			XDocument xmlDocument = new XDocument();
			xmlDocument.Add(element);
			xmlDocument.Save(XML);
		}

		/// <summary>
		/// Создать новое сюжетное задание
		/// </summary>
		/// <returns></returns>
		public Quest CreateQuest()
		{
			Quest quest = new Quest(mQNamespace);
			quest.Owner = this;

			return quest;
		}

		/// <summary>
		/// Получить пространство имен по имени
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		public Quest GetQuest(String name)
		{
			return mQNamespace.GetObject(name);
		}

		/// <summary>
		/// Создать задачу
		/// </summary>
		/// <returns></returns>
		public Task CreateTask()
		{
			Task task = new Task(mTNamespace);
			return task;
		}

		/// <summary>
		/// Получить задачу по имени
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		public Task GetTask(String name)
		{
			return mTNamespace.GetObject(name);
		}

		#endregion

		#region XML

		XElement SaveTask(Task task)
		{
			XElement taskElement = new XElement("Task");
			// Свойства задачи
			taskElement.SetAttributeValue("ID", task.ID);
			taskElement.SetAttributeValue("Title", task.Title);
			taskElement.SetAttributeValue("Description", task.Description);
			taskElement.SetAttributeValue("StartScript", task.StartScript);
			taskElement.SetAttributeValue("IterationScript", task.IterationScript);


			// Сохранение решений задачи
			XElement endings = new XElement("Endings");
			taskElement.Add(endings);
			foreach (Ending ending in task.Endings)
			{
				XElement endingElement = SaveEnding(ending);
				endings.Add(endingElement);
			}

			return taskElement;
		}
		XElement SaveEnding(Ending ending)
		{
			XElement endingElement = new XElement("Ending");

			// Свойства решений
			endingElement.SetAttributeValue("ID", ending.ID);
			endingElement.SetAttributeValue("Title", ending.Title);
			endingElement.SetAttributeValue("Description", ending.Description);
			endingElement.SetAttributeValue("Condition", ending.ConditionScript);
			endingElement.SetAttributeValue("Script", ending.GoOffScript);

			// Новые задачи
			XElement starts = new XElement("StartTasks");
			endingElement.Add(starts);
			foreach (Task task in ending.NewTasks)
			{
				XElement taskElement = SaveTask(task);
				starts.Add(taskElement);
			}
			return endingElement;
		}
		XElement SaveQuest(Quest quest)
		{
			XElement questElement = new XElement("Quest");

			// Сохранение свойств задания
			questElement.SetAttributeValue("ID", quest.ID);
			questElement.SetAttributeValue("Title", quest.Title);
			questElement.SetAttributeValue("Description", quest.Description);
			questElement.SetAttributeValue("Status", quest.Status);
			questElement.SetAttributeValue("StartScript", quest.StartScript);
			questElement.SetAttributeValue("EndScript", quest.EndScript);

			// Сохранение всех активных задач задания
			XElement tasks = new XElement("Tasks");
			questElement.Add(tasks);
			foreach (Task task in quest.ActiveTasks)
			{
				XElement taskElement = SaveTask(task);
				tasks.Add(taskElement);
			}

			return questElement;
		}

		public XElement SaveAll()
		{
			XElement quests = new XElement("Quests");
			quests.SetAttributeValue("Script", Script);

			foreach (Quest quest in Quests)
			{
				quests.Add(SaveQuest(quest));
			}

			return quests;
		}

		Task LoadTask(Quest parent, XElement element)
		{
			Task task = CreateTask();

			task.ID = element.Attribute("ID").Value;
			task.Title = element.Attribute("Title").Value;
			task.Description = element.Attribute("Description").Value;
			task.StartScript = element.Attribute("StartScript").Value;
			task.IterationScript = element.Attribute("IterationScript").Value;

			task.Status = QuestStatus.Inactive;
			task.Owner = parent;

			XElement e = element.Element("Endings");
			IEnumerable<XElement> endingElements =
					from e1 in e.Elements()
					select e1;

			foreach (XElement endingElement in endingElements)
			{
				Ending ending = LoadEnding(task, endingElement);
				task.Add(ending);
			}

			return task;
		}
		Ending LoadEnding(Task parent, XElement element)
		{
			Ending ending = parent.CreateEnding();

			ending.ID = element.Attribute("ID").Value;
			ending.Description = element.Attribute("Description").Value;
			ending.Title = element.Attribute("Title").Value;
			ending.ConditionScript = element.Attribute("Condition").Value;
			ending.GoOffScript = element.Attribute("Script").Value;
			ending.Owner = parent;

			IEnumerable<XElement> elements =
					from el in element.Element("StartTasks").Elements()
					select el;

			foreach (XElement e in elements)
			{
				Task task = LoadTask(parent.Owner, e);
				ending.NewTasks.Add(task);
			}
			return ending;
		}
		Quest LoadQuest(XElement element)
		{
			Quest quest = CreateQuest();

			quest.ID = element.Attribute("ID").Value;
			quest.Title = element.Attribute("Title").Value;
			quest.Description = element.Attribute("Description").Value;
			quest.StartScript = element.Attribute("StartScript").Value;
			quest.EndScript = element.Attribute("EndScript").Value;

			XElement e = element.Element("Tasks");
			IEnumerable<XElement> taskElements =
					from el in e.Elements()
					select el;

			foreach (XElement taskElement in taskElements)
			{
				Task task = LoadTask(quest, taskElement);
				task.Status = QuestStatus.Active;

				quest.ActiveTasks.Add(task);
			}

			return quest;
		}

		public void LoadAll(XElement quests)
		{
			IEnumerable<XElement> elements =
					from el in quests.Elements()
					select el;

			foreach (XElement element in elements)
			{
				Add(LoadQuest(element));

			}

			try
			{
				Script = quests.Attribute("Script").Value;
			}
			catch
			{
			}
		}

		#endregion

		#region Serialize

		public void SaveData(String name)
		{
			FileStream file = new FileStream(name, FileMode.Create);
			BinaryFormatter bf = new BinaryFormatter();

			bf.Serialize(file, mScript);
			bf.Serialize(file, mQNamespace);
			bf.Serialize(file, mTNamespace);

			file.Close();
		}

		public void LoadData(String name)
		{
			FileStream file = new FileStream(name, FileMode.Open);
			BinaryFormatter bf = new BinaryFormatter();

			mScript = bf.Deserialize(file) as String;
			mQNamespace = bf.Deserialize(file) as NamespaceManager<Quest>;
			mTNamespace = bf.Deserialize(file) as NamespaceManager<Task>;

			file.Close();
		}
		#endregion

		#region Events

		public event QuestEventHandler QuestListChanged;
		public event QuestChangedEventHandler QuestAdded;
		public event QuestChangedEventHandler QuestRemoved;
		public event QuestChangedEventHandler QuestStarted;

		#endregion
	}
}
