using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Common.Views;

namespace Common
{
    public class EditorSelectionEventArgs : EventArgs
    {
        public EditorSelectionEventArgs()
        {
        }

        public IEditorWindow Editor
        {
            get;
            set;
        }

        public IProxyObject SelectedObject
        {
            get;
            set;
        }
    }

    public delegate void EditorSelectionEventHandler(object sender, EditorSelectionEventArgs args);
}
