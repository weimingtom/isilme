using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Xml.Linq;
using System.Text;
using LuaInterface;
using System.Reflection;

namespace QuestEditor
{
 
    public class LuaSerializer
    {
        public static Dictionary<LuaTable, int> Serialized = new Dictionary<LuaTable,int>();
        public static Lua mLua;

        public static int TableRef = 0;

        public static XElement SerializeVariable(Object key, Object value)
        {
            XElement result = new XElement("Variable");

            // Указываем тип ключа
            if (key is double)
                result.SetAttributeValue("KeyType", "number");
            else
                if (key is string)
                    result.SetAttributeValue("KeyType", "string");
                else
                    if (key is bool)
                        result.SetAttributeValue("KeyType", "boolean");

            result.SetAttributeValue("Key", key);

            // Проверяем строку
            if (value is String)
            {
                result.SetAttributeValue("Type", "string");
                result.SetAttributeValue("Value", value);
            }

            // Проверяем число
            if (value is Double)
            {
                result.SetAttributeValue("Type", "number");
                result.SetAttributeValue("Value", value);
            }

            // Логическое значение
            if (value is Boolean)
            {
                result.SetAttributeValue("Type", "boolean");
                result.SetAttributeValue("Value", value);
            }

            // Ничто
            if (value == null)
            {
                result.SetAttributeValue("Type", "nil");
            }

            // Таблица
            if (value is LuaTable)
            {
                bool found = false;
                foreach (LuaTable table in Serialized.Keys.ToList())
                {
                    if (table.Equals(value))
                        found = true;
                }
                if (found)
                {
                    //System.Windows.Forms.MessageBox.Show("петля найдена");
                    result.SetAttributeValue("Type", "table");
                    result.SetAttributeValue("Reference", 0);
                }
                else
                {
                    //System.Windows.Forms.MessageBox.Show("Обработка таблицы" + key + "     Ref: " + MyLua.GetReference(value as LuaTable));
                    result.SetAttributeValue("Type", "table");
                    result.SetAttributeValue("Reference", TableRef);
                    LuaTable table = value as LuaTable;
                    Serialized[table] = TableRef;
                    TableRef++;


                    IEnumerator enumerator = table.Keys.GetEnumerator();
                    while (enumerator.MoveNext())
                    {
                        Object tableKey = enumerator.Current;
                        Object tableValue = table[tableKey];

                        XElement variable = LuaSerializer.SerializeVariable(tableKey, tableValue);
                        result.Add(variable);
                    }
                }
            }


            return result;
        }

        public static KeyValuePair<Object,Object> GetObject(XElement element)
        {
            Object key = null;
            Object value = null;


            // Создаем ключ
            switch (element.Attribute("KeyType").Value)
            {
                case "number":
                    key = Double.Parse(element.Attribute("Key").Value);
                    break;
                case "boolean":
                    key = Boolean.Parse(element.Attribute("Key").Value);
                    break;
                case "string":
                    key = element.Attribute("Key").Value;
                    break;
            }

            // Создаем значение
            switch (element.Attribute("Type").Value)
            {
                case "number":
                    value = Double.Parse(element.Attribute("Value").Value);
                    break;
                case "string":
                    value = element.Attribute("Value").Value;
                    break;
                case "boolean":
                    value = Boolean.Parse(element.Attribute("Value").Value);
                    break;
                case "table":
                    value = null; /// I don't know how
                    // TODO: Доделать распознаванике таблиц
                    break;
            }

            KeyValuePair<Object, Object> result = new KeyValuePair<object, object>(key, value);
            return result;
        }

        public static String VarName(String prefix, XElement element)
        {
            String result = prefix;

            switch (element.Attribute("KeyType").Value)
            {
                case "number":
                    result += "[" + element.Attribute("Key").Value + "]";
                    break;
                case "boolean":
                    result += "[" + element.Attribute("Key").Value + "]";
                    break;
                case "string":
                    result += "[\"" + element.Attribute("Key").Value + "\"]";
                    break;
            }

            switch (element.Attribute("Type").Value)
            {
                case "number":
                    result += " = " + element.Attribute("Value").Value + ";\n";
                    break;
                case "boolean":
                    result += " = " + element.Attribute("Value").Value + ";\n";
                    break;
                case "string":
                    result += " = \"" + element.Attribute("Value").Value + "\";\n";
                    break;
                case "table":
                    String newTable = result + " = {};\n";
                    break;
            }
            return result;
        }
    }

    public class MyLua
    {
        public static int GetReference(LuaBase luaObject)
        {
           Object reference = luaObject.GetType().InvokeMember(
                "_Reference",
                BindingFlags.Public |
                BindingFlags.NonPublic |
                BindingFlags.Instance |
                BindingFlags.GetField,
                null,
                luaObject,
                null
            );
           return (int)reference;
        }
    }
}
