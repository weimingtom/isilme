using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common.Views;

namespace IDE
{
    /// <summary>
    /// Интерфейс ассоцииации редактора с файлом
    /// </summary>
    public interface IEditorAssotioation
    {
        EditorWindow CreateEditor();
    }
}
