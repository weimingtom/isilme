using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace QuestEditor.Models
{
    public class ModelStage
    {
        #region Constructors

        public ModelStage()
        {
        }

        #endregion

        #region Properties

        /// <summary>
        /// Квест
        /// </summary>
        public ModelQuest Quest
        {
            get;
            set;
        }

        /// <summary>
        /// Иентификатор
        /// </summary>
        public int ID
        {
            get;
            set;
        }

        /// <summary>
        /// Стартовый скрипт
        /// </summary>
        public String OnStart
        {
            get;
            set;
        }

        /// <summary>
        /// Скрипт итерации
        /// </summary>
        public String OnUpdate
        {
            get;
            set;
        }

        public String Text
        {
            get;
            set;
        }
        #endregion

        public override string ToString()
        {
            return String.Format("[{0}] {1}", ID, Text);
        }
    }
}
