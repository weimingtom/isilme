using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace XCob
{
    /// <summary>
    /// Интерфейс для всех свойств (возможно не нужен, но на всякий случай)
    /// </summary>
    public interface IProperty
    {
        ActionManager ActionManager
        {
            get;
            set;
        }

        Object SelectedObject
        {
            get;
            set;
        }
    };

    public interface IPropertyMaker
    {
        IProperty CreateProperties(ActionManager actionManager, Object selected);
    }
}
