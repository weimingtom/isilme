using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using Common.Views;
using System.Xml.Linq;

namespace Common
{
    public class EditorManager
    {
        #region Members

        /// <summary>
        /// Таблица отображений расширение-редактор
        /// </summary>
        Dictionary<String, IEditorAssociation> mExtensions = new Dictionary<string, IEditorAssociation>();

        Dictionary<String, IEditorAssociation> mTags = new Dictionary<String, IEditorAssociation>();

        /// <summary>
        /// Manager instance
        /// </summary>
        static EditorManager mInstance;

        #endregion

        #region Constructors

        public EditorManager()
        {
        }

        #endregion

        #region Properties

        /// <summary>
        /// Gets instance of editor manager
        /// </summary>
        public static EditorManager Instance
        {
            get
            {
                if (mInstance == null)
                    mInstance = new EditorManager();

                return mInstance;
            }
        }

        #endregion

        /// <summary>
        /// Возвращает редактор для файла
        /// </summary>
        /// <param name="fileName"></param>
        /// <returns></returns>
        public IEditorAssociation GetEditorForFile(String fileName)
        {
            String extension = Path.GetExtension(fileName);
            if (mExtensions.ContainsKey(extension))
                return mExtensions[extension];
            else
                return null;
        }

        /// <summary>
        /// Registers editor for tag
        /// </summary>
        /// <typeparam name="Teditor"></typeparam>
        /// <param name="tag"></param>
        public void RegisterEditorForTag<Teditor>(String tag) where Teditor : EditorWindow, new()
        {
           RegisterEditorForTag(new EditorAssotiation<Teditor>(), tag);
        }

        /// <summary>
        /// Registers editor for tag
        /// </summary>
        /// <param name="assotiation"></param>
        /// <param name="tag"></param>
        public void RegisterEditorForTag(IEditorAssociation assotiation, String tag)
        {
            mTags[tag] = assotiation;
        }

        /// <summary>
        /// Gets editor for tag
        /// </summary>
        /// <param name="tag">tag of editble data</param>
        /// <returns>editor window or null</returns>
        public EditorWindow GetEditorForTag(String tag)
        {
            if (mTags.ContainsKey(tag))
                return mTags[tag].CreateEditor();
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
