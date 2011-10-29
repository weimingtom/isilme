using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Controls;
using QuestEditor.Proxy;
using QuestEditor.Models;

namespace QuestEditor.Views
{
    public class QuestNode : TreeViewItem
    {
        ProxyQuest mProxyQuest;

        public QuestNode(ProxyQuest proxyQuest)
        {
        }

        public String QuestID
        {
            get { return mProxyQuest.ID; }
        }

        public String QuestTitle
        {
            get { return mProxyQuest.Title; }
        }
    }
}
