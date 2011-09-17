using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace GameEditor.Models
{
    public class ModelQuest
    {
        #region Constructors

        public ModelQuest()
        {
            Stages = new List<ModelStage>();
        }

        #endregion

        #region Properies

        public ModelStory Story
        {
            get;
            set;
        }

        public String Title
        {
            get;
            set;
        }

        public String ID
        {
            get;
            set;
        }

        public List<ModelStage> Stages
        {
            get;
            set;
        }

        public String OnStart
        {
            get;
            set;
        }

        public String OnUpdate
        {
            get;
            set;
        }

        public String OnFinish
        {
            get;
            set;
        }

        #endregion

        public override string ToString()
        {
            return String.Format("[{0}] {1}", ID, Title);
        }
    }
}
