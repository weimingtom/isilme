using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using System.Reflection;

namespace GameEditor.Action
{
    public class SetProperty : ICommand
    {
        Object mTarget;
        Object mOldValue;
        Object mValue;
        String mProperty;

        public SetProperty(Object target, String property, Object value)
        {
            mTarget = target;
            mProperty = property;
            mValue = value;
            mOldValue = mTarget.GetType().InvokeMember
                (
                    mProperty,
                     BindingFlags.Instance | BindingFlags.DeclaredOnly | BindingFlags.GetProperty | BindingFlags.Public | BindingFlags.NonPublic,
                    null, 
                    mTarget, 
                    null
                );
        }

        public virtual void Execute()
        {
            mTarget.GetType().InvokeMember
                (
                    mProperty,
                    BindingFlags.Instance | BindingFlags.DeclaredOnly | BindingFlags.SetProperty | BindingFlags.Public | BindingFlags.NonPublic,
                    null,
                    mTarget,
                    new Object[]{mValue}
                );
        }

        public virtual void Unexecute()
        {
            mTarget.GetType().InvokeMember
                (
                    mProperty,
                    BindingFlags.Instance | BindingFlags.DeclaredOnly | BindingFlags.SetProperty | BindingFlags.Public | BindingFlags.NonPublic,
                    null,
                    mTarget,
                    new Object[] { mOldValue }
                );
        }

        public virtual Boolean IsReversible
        {
            get
            {
                return true;
            }
        }
    }
}
