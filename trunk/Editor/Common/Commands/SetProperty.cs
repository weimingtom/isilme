using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Reflection;
using System.Collections;

namespace Common
{
    /// <summary>
    /// Команда установления свойства
    /// </summary>
    public class SetProperty : ICommand
    {
        protected String mProperty;
        protected Object mObject;
        protected Object mOldValue;
        protected Object mNewValue;

        /// <summary>
        /// Конструктор создает действие изменение свойства
        /// </summary>
        /// <param name="obj">Объект-владелец свойства</param>
        /// <param name="property">Имя свойства</param>
        /// <param name="value">Новое значение свойства</param>
        public SetProperty(Object obj, String property, Object value)
        {
            mProperty = property;
            mObject = obj;
            mNewValue = value;
            mOldValue = mObject.GetType().InvokeMember(
                mProperty,
                BindingFlags.Public |
                BindingFlags.NonPublic |
                BindingFlags.Instance |
                BindingFlags.GetProperty,
                null,
                mObject,
                null
            );
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="property"></param>
        /// <param name="value"></param>
        /// <param name="oldValue"></param>
        public SetProperty(Object obj, String property, Object value, Object oldValue)
        {
            mProperty = property;
            mObject = obj;
            mNewValue = value;
            mOldValue = oldValue;
        }

        /// <summary>
        /// Изменяет значение свойства на новое
        /// </summary>
        public void Execute()
        {
            mObject.GetType().InvokeMember(
                mProperty,
                BindingFlags.Public |
                BindingFlags.NonPublic |
                BindingFlags.Instance |
                BindingFlags.SetProperty,
                null,
                mObject,
                new Object[] { mNewValue }
            );
        }

        /// <summary>
        /// Возвращает старое значение свойства
        /// </summary>
        public void Unexecute()
        {
            mObject.GetType().InvokeMember(
                    mProperty,
                    BindingFlags.Public |
                    BindingFlags.NonPublic |
                    BindingFlags.Instance |
                    BindingFlags.SetProperty,
                    null,
                    mObject,
                    new Object[] { mOldValue }
                );
        }
    }
}
