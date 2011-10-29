using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using AvalonDock;
using Common;
using Common.Views;
using IDE.Views;
using Microsoft.Win32;

namespace IDE
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class IDEWindow : Window
    {
        #region Members

        /// <summary>
        /// Список всех инструментов
        /// </summary>
        List<IToolWindow> mTools = new List<IToolWindow>();

        /// <summary>
        /// Все открытые документы
        /// </summary>
        List<EditorWindow> mOpendDocuments = new List<EditorWindow>();

        /// <summary>
        /// Окно свойств
        /// </summary>
        PropertyWindow mPropertiesWindow = new PropertyWindow();

        /// <summary>
        /// Мэнеджер проетка
        /// </summary>
        ModuleManager mModuleManager = new ModuleManager();

        #endregion

        #region Prpperties

        public EditorWindow ActiveEditor
        {
            get
            {
                return mDockingManager.ActiveDocument as EditorWindow;
            }
        }
        #endregion

        public IDEWindow()
        {
            InitializeComponent();

            mToolWindowsMenu.DataContext = mTools;
            mWindowMenu.DataContext = mOpendDocuments;

            AddToolWindow(mPropertiesWindow);
            AddToolWindow(mModuleManager);

            AddEditorWindow(new EditorWindow() { FileName = "1.txt"});
            AddEditorWindow(new EditorWindow() { FileName="test.txt"});
            AddEditorWindow(new QuestEditor.Views.QuestEditorWindow() { FileName="story.txt"});
        }

        #region Methods

        /// <summary>
        /// Добавляет окно инструментов
        /// </summary>
        /// <param name="window"></param>
        void AddToolWindow(ToolWindow window)
        {
            mTools.Add(window);
            window.Show(mDockingManager, AnchorStyle.Left);
            window.Activate();
        }

        void AddEditorWindow(EditorWindow window)
        {
            mOpendDocuments.Add(window);
            window.ShowAsDocument(mDockingManager);
            window.Activate();
        }

        #endregion

        /// <summary>
        /// Открывает панель инструментов, соответствующую пункту меню
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onToolWindowsMenu_Click(object sender, RoutedEventArgs e)
        {
            var selectedContent = ((MenuItem)e.OriginalSource).DataContext as ToolWindow;

            if (selectedContent.State != DockableContentState.Docked)
            {
                //show content as docked content
                selectedContent.Show(mDockingManager, AnchorStyle.Right);
            }

            selectedContent.Activate();
        }

        /// <summary>
        /// Отменяет последнее действие в активном окне
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onUndo_Click(object sender, RoutedEventArgs e)
        {
            ActiveEditor.Undo();
        }

        /// <summary>
        /// Повторяет ранее отмененное действие
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onRedo_Click(object sender, RoutedEventArgs e)
        {
            ActiveEditor.Redo();
        }

        /// <summary>
        /// Создает новый модуль
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onNewModule_Click(object sender, RoutedEventArgs e)
        {
        }

        /// <summary>
        /// Открывает существующий модуль
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onOpenModule_CLick(object sender, RoutedEventArgs e)
        {
        }

        /// <summary>
        /// Сохранить текущий документ
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onSave_Click(object sender, RoutedEventArgs e)
        {
            ActiveEditor.Save();
        }

        /// <summary>
        /// Сохраняет документ с заданным именем
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onSaveAs_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog dialog = new SaveFileDialog();
            if (dialog.ShowDialog() == true)
            {
                ActiveEditor.SaveAs(dialog.FileName);
            }
        }

        /// <summary>
        /// Сохранить все открытые документы
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void onSaveAll_Click(object sender, RoutedEventArgs e)
        {
            foreach (EditorWindow editor in mOpendDocuments)
                editor.Save();
        }
    }
}
