using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MyApplication1.Data;
using System.Xml.Linq;

namespace MyApplication1.Data
{
    public class AILoader
    {
        int ruleId = 1;
        int typeId = 1;
        int type = 0;
        string fileName = "base.xml";

        AIAction LoadAction(XElement element)
        {
            AIAction rule = new AIAction();
            rule.ID = element.Element("Action").Value;
            return rule;
        }
        TargetSelector LoadTarget(XElement element)
        {
            TargetSelector rule = new TargetSelector();
            rule.ID = element.Element("Target Selector").Value;
            return rule;
        }
        public AIRule LoadRule(XElement element) 
        { 
            AIRule rule = new AIRule(); 
            rule.ID = element.Attribute("ID").Value;
            return rule; 
        }
        public AIRulesList LoadFromFile(String fileName)
        {
           AIRulesList mRules = new AIRulesList();
            //читаем данные из файла
            XDocument doc = XDocument.Load(fileName);
            foreach (XElement e in doc.Root.Elements()) 
            {
                AIRule rule = LoadRule(e);
                AIAction ruleAction = LoadAction(e);
                TargetSelector ruleTarget = LoadTarget(e);
                mRules.Rules.Add(rule);
                mRules.Actions.Add(ruleAction);
                mRules.TargetSelectors.Add(ruleTarget);
                
            }
            return mRules;
        }

        XElement SaveAction(AIAction a)
        {
            XElement rule = new XElement("Action");
            return rule;
        }
        XElement SaveTargetSelector(TargetSelector s)
        {
            XElement rule = new XElement("Target Selector");
            return rule;
        }
        XElement SaveRule(AIRule rule) 
        {
            XElement e = new XElement("AIRule"); 
            e.SetAttributeValue("ID", rule.ID);
            e.Add(SaveAction(rule.Action));
            e.Add(SaveTargetSelector(rule.Target.Selector));
          
            return e; 
        }
        public void SaveToFile(AIRulesList mRules, String fileName)
        {
            XElement doc = new XElement("AIRules"); 
            foreach (AIRule rule in mRules.Rules) 
            {
                doc.Add(SaveRule(rule));
            } 
            doc.Save(fileName);
        }

    }
}
