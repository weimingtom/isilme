using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;

namespace MyApplication1.Data
{
    public class AIRule:ProxyObject
    {
        private String mID = ""; // Это значение идентифкатора
        public String ID
        {
            get { return mID; } // Чтение
            set { mID = value; RaisePropertyChanged(this, "ID"); } // меняем значение и оповещаем наблюдателей
        }
        private AIAction mAction;
        public AIAction Action
        {
            get {return mAction;}
            set {mAction = value; RaisePropertyChanged(this, "Action"); }
        }
        private ActionTarget mTarget;
        public ActionTarget Target
        {
            get { return mTarget; }
            set { mTarget = value; RaisePropertyChanged(this, "Target"); }
        }
        private Script mCondition;
        public Script Condition
        {
            get { return mCondition; }
            set { mCondition = value; RaisePropertyChanged(this, "Condition"); }
        }
        private Script mPriority;
        public Script Priority
        {
            get { return mPriority; }
            set { mPriority = value; RaisePropertyChanged(this, "Priority"); }
        }
    }
}
