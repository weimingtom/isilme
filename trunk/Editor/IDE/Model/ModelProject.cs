using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace IDE.Model
{
    /// <summary>
    /// Модель проекта
    /// </summary>
    public class ModelProject
    {

        public ModelProject()
        {
            Items = new List<ModelNode>();
        }

        public void Save()
        {
        }

        public void Load()
        {
        }

        /// <summary>
        /// Список всех элементов проекта
        /// </summary>
        public List<ModelNode> Items
        {
            get;
            set;
        }
    }
}
