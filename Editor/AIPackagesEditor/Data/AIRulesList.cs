using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Collections.ObjectModel;

namespace MyApplication1.Data
{
    public class AIRulesList
    {
        public AIRulesList()
        {
            Rules = new ObservableCollection<AIRule>();
            Actions = new ObservableCollection<AIAction>();
            TargetSelectors = new ObservableCollection<TargetSelector>();

        }

        public ObservableCollection<AIRule> Rules
        {
            get;
            set;
        }
        public ObservableCollection<AIAction> Actions
        {
            get;
            set;
        }
        public ObservableCollection<TargetSelector> TargetSelectors
        {
            get;
            set;
        }
    }
}
