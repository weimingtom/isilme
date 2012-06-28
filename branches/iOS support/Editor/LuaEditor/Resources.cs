using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Windows.Controls;
using System.Windows.Markup;
using System.Resources;
using System.Reflection;

namespace LuaEditor
{
    public static class Resources
    {
        static readonly string Prefix = typeof(Resources).FullName + ".";

        public static Stream OpenStream(string name)
        {
            Stream s = typeof(Resources).Assembly.GetManifestResourceStream("LuaEditor.Views.LuaToolbar.xaml");

            if (s == null)
                throw new FileNotFoundException("The resource file '" + name + "' was not found.");
            return s;
        }

        public static ToolBar getToolbar()
        {
            using (Stream s = Resources.OpenStream("LuaToolbar.xaml"))
            {
                ToolBar tb = XamlReader.Load(s, new ParserContext()) as ToolBar;
                return tb;
            }
            return null;
        }
    }
}
