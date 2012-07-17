using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace MyApplication1.Data
{
    public class AIRulesList
    {
        public AIRulesList()
        {
            Rules = new ObservableCollection<AIRule>();
        }

        public ObservableCollection<AIRule> Rules
        {
            get;
            set;
        }
    }
}
