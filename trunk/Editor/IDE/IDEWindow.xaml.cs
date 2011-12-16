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
using System.IO;
using System.Reflection;
using System.Windows.Markup;
using LuaEditor.Views;
using QuestEditor.Views;
using LevelEditor.Views;

namespace IDE
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class IDEWindow : Window
    {
        #region Commands

        public static RoutedCommand SaveAll = new RoutedCommand();

        void CanExecuteNew(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        void ExecutedNew(object sender, ExecutedRoutedEventArgs e)
        {
        }

        void CanExecuteOpen(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        void ExecutedOpen(object sender, ExecutedRoutedEventArgs e)
        {
            OpenFileDialog dialog = new OpenFileDialog();
            if (dialog.ShowDialog() == true)
            {
                String filename = dialog.FileName;
                IEditorAssotioation assotiation =  ExtensionManager.GetEditorForFile(filename);
                EditorWindow editor = assotiation.CreateEditor();
                editor.FileName = filename;
                editor.Load();
                AddEditorWindow(editor);
            }
        }

        void CanExecuteSaveAll(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }

        void ExecutedSaveAll(object sender, ExecutedRoutedEventArgs e)
        {
            foreach (EditorWindow editor in mOpendDocuments)
                editor.Save();
        }

        #endregion

        #region Members

        /// <summary>
        /// Список всех инструментов
        /// </summary>
        List<IToolWindow> mTools = new List<IToolWindow>();

        /// <summary>
        /// Все открытые документы
        /// </summary>
        List<IEditorWindow> mOpendDocuments = new List<IEditorWindow>();

        /// <summary>
        /// Окно свойств
        /// </summary>
        PropertyWindow mPropertiesWindow = new PropertyWindow();

        /// <summary>
        /// Мэнеджер проетка
        /// </summary>
        ModuleManager mModuleManager = new ModuleManager();

        ExtensionManager mExtensionManager = new ExtensionManager();

        #endregion

        #region Prpperties

        /// <summary>
        /// Возвращает активный редактор
        /// </summary>
        public EditorWindow ActiveEditor
        {
            get
            {
                return mDockingManager.ActiveDocument as EditorWindow;
            }
        }

        /// <summary>
        /// Возвращает менеджер расширений
        /// </summary>
        public ExtensionManager ExtensionManager
        {
            get
            {
                return mExtensionManager;
            }
        }

        #endregion

        public IDEWindow()
        {
            InitializeComponent();

            // Регистрируем комманды
            CommandBindings.Add(new CommandBinding(ApplicationCommands.New, ExecutedNew, CanExecuteNew));
            CommandBindings.Add(new CommandBinding(ApplicationCommands.Open, ExecutedOpen, CanExecuteOpen));
            CommandBindings.Add(new CommandBinding(SaveAll, ExecutedSaveAll, CanExecuteSaveAll));

            // Регистрируем расширения
            ExtensionManager.RegisterExtension<TextEditorWindow>(".txt");
            ExtensionManager.RegisterExtension<LuaEditorWindow>(".lua");
            ExtensionManager.RegisterExtension<QuestEditorWindow>(".story");
            ExtensionManager.RegisterExtension<ConversationEditorWindow>(".conv");
            ExtensionManager.RegisterExtension<LevelEditorWindow>(".lvl");

            mToolWindowsMenu.DataContext = mTools;
            mWindowMenu.DataContext = mOpendDocuments;

            // Регистрируем панели инструментов
            AddToolWindow(mPropertiesWindow);
            AddToolWindow(mModuleManager);
            
            AddEditorWindow(new LevelEditorWindow() {FileName = "TestLevel.lvl"});
            AddEditorWindow(new EditorWindow() { FileName = "1.txt"});
            AddEditorWindow(new EditorWindow() { FileName="test.txt"});
            AddEditorWindow(new LuaEditor.Views.LuaEditorWindow() { FileName = "test.lua" });
            AddEditorWindow(new QuestEditor.Views.QuestEditorWindow() { FileName="story.txt"});
            AddEditorWindow(new QuestEditor.Views.ConversationEditorWindow() { FileName="test.conv"});
            ToolBar tb = LuaEditor.Resources.getToolbar();
            if (tb != null)
                mToolbarTray.ToolBars.Add(tb);

            Stream s = typeof(QuestEditor.Views.QuestEditorWindow).Assembly.GetManifestResourceStream("QuestEditor.Views.QuestToolbar.xaml");

            tb = QuestEditor.Views.QuestEditorWindow.getToolbar();
            if (tb != null)
                mToolbarTray.ToolBars.Add(tb);
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
            window.SelectionChanged += new EditorSelectionEventHandler(onEditor_SelectionChanged);
        }

        void onEditor_SelectionChanged(object sender, EditorSelectionEventArgs args)
        {
            mPropertiesWindow.SelectedObject = args.SelectedObject;
            mPropertiesWindow.CommandManager = args.Editor.CommandManager;
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

        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            AddEditorWindow(new LevelEditorWindow() { FileName = "1.lvl" });
        }
    }
}
