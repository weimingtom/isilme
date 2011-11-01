using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Common.Views;
using System.Xml.Linq;

namespace IDE
{
    public class ExtensionManager
    {
        #region Members

        /// <summary>
        /// Таблица отображений расширение-редактор
        /// </summary>
        Dictionary<String, IEditorAssotioation> mExtensions = new Dictionary<string, IEditorAssotioation>();

        #endregion

        public ExtensionManager()
        {
        }

        /// <summary>
        /// Возвращает редактор для файла
        /// </summary>
        /// <param name="fileName"></param>
        /// <returns></returns>
        public IEditorAssotioation GetEditorForFile(String fileName)
        {
            String extension = Path.GetExtension(fileName);
            if (mExtensions.ContainsKey(extension))
                return mExtensions[extension];
            else
                return null;
        }

        /// <summary>
        /// Регистрирует редактор для указанного расширения
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="extension"></param>
        public void RegisterExtension<T>(String extension) where T : EditorWindow, new ()
        {
            mExtensions[extension] = new EditorAssotiation<T>();
        }

        /// <summary>
        /// Сохраняет настройки в XML-элемент
        /// </summary>
        /// <returns></returns>
        public XElement SaveToElement()
        {
            return null;
        }

        /// <summary>
        /// Загружает настройки из XML
        /// </summary>
        /// <param name="setttings"></param>
        public void Load(XElement setttings)
        {
        }
    }
}
