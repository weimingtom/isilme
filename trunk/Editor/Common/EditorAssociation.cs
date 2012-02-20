using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common;
using Common.Views;

namespace Common
{
    /// <summary>
    /// Ассоциация с редактором
    /// </summary>
    public class EditorAssotiation<TEditor> : IEditorAssociation where TEditor : EditorWindow, new()
    {
        public EditorWindow CreateEditor()
        {
            TEditor editor =  new TEditor();
            return editor;
        }
    }
}
