﻿using System;
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
using LevelEditor.View;

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
                IEditorAssociation assotiation = EditorManager.Instance.GetEditorForFile(filename);
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
            //mModuleManager.mModuleTree.DataContext = ObjectManager.Instance.Editor.Level.Layers;

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

        #endregion

        public IDEWindow()
        {
            InitializeComponent();

            // Регистрируем комманды
            CommandBindings.Add(new CommandBinding(ApplicationCommands.New, ExecutedNew, CanExecuteNew));
            CommandBindings.Add(new CommandBinding(ApplicationCommands.Open, ExecutedOpen, CanExecuteOpen));
            CommandBindings.Add(new CommandBinding(SaveAll, ExecutedSaveAll, CanExecuteSaveAll));

            Common.FileCommands.OpenFile.CanExecuteTargets += new Func<bool>(OpenFile_CanExecuteTargets);
            Common.FileCommands.OpenFile.ExecuteTargets += new Action<object>(OpenFile_ExecuteTargets);

            // Регистрируем расширения
            EditorManager.Instance.RegisterExtension<TextEditorWindow>(".txt");
            EditorManager.Instance.RegisterExtension<ScriptEditorWindow>(".lua");
            EditorManager.Instance.RegisterExtension<QuestEditorWindow>(".story");
            EditorManager.Instance.RegisterExtension<LevelEditor.View.ConversationEditorWindow>(".conv");

            EditorManager.Instance.RegisterEditorForTag(new LevelEditorAssociation(), "Levels");
            EditorManager.Instance.RegisterEditorForTag<QuestEditorWindow>("Story");
            EditorManager.Instance.RegisterEditorForTag<ScriptEditorWindow>("Scripts");
            EditorManager.Instance.RegisterEditorForTag<LevelEditor.View.ConversationEditorWindow>("Conversations");
            EditorManager.Instance.RegisterExtension<AIPackagesEditor.AIPackagesEditorWindow>(".aip");
          //  ExtensionManager.RegisterExtension<LevelEditorWindow>(".lvl");

            mToolWindowsMenu.DataContext = mTools;
            mWindowMenu.DataContext = mOpendDocuments;

            // Регистрируем панели инструментов
            AddToolWindow(mPropertiesWindow);
            AddToolWindow(mModuleManager);
            AddToolWindow(LevelEditor.View.ObjectManager.Instance);
            AddToolWindow(LevelEditor.View.EntityPaletteTool.Instance);
            
            AddEditorWindow(LevelEditor.View.LevelEditorWindow.Instance);
      //      AddEditorWindow(new LevelEditorWindow() { FileName = "../Data/Levels/Level1.xml" });
            ToolBar tb;// = LuaEditor.Resources.getToolbar();
            //if (tb != null)
            //    mToolbarTray.ToolBars.Add(tb);

           // Stream s = typeof(QuestEditor.Views.QuestEditorWindow).Assembly.GetManifestResourceStream("QuestEditor.Views.QuestToolbar.xaml");

            tb = LevelEditor.View.QuestEditorToolBar.Instance; 
            mToolbarTray.ToolBars.Add(tb);

            tb = new LevelEditor.View.LevelEditorToolBar();
            mToolbarTray.ToolBars.Add(tb);

            tb =LevelEditor.View.ConversationEditorToolBar.Instance;
            mToolbarTray.ToolBars.Add(tb);

            tb = LevelEditor.View.ScriptToolBar.Instance;
            mToolbarTray.ToolBars.Add(tb);
        }

        void OpenFile_ExecuteTargets(object obj)
        {
            IEditableData data = obj as IEditableData;
            if (data != null)
            {
                foreach (EditorWindow w in mOpendDocuments)
                {
                    if (w.FileName.ToLower() == data.FileName.ToLower())
                    {
                        if (!w.IsVisible)
                        {
                            w.Show();
                        }

                        w.Activate();
                        return;
                    }
                }

                EditorWindow editor  = EditorManager.Instance.GetEditorForTag(data.EditorTag);
                if (editor == null)
                {
                    MessageBox.Show("There is no editor for this typeof content", "Warning", MessageBoxButton.OK);
                }
                else
                {
                    editor.Load(data);
                    editor.FileName = data.FileName;
                    AddEditorWindow(editor);
                }
            }
        }

        bool OpenFile_CanExecuteTargets()
        {
            return true;
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
            window.Closed += new EventHandler(onEditor_Closed);
        }

        void onEditor_Closed(object sender, EventArgs e)
        {
            IEditorWindow w = sender as IEditorWindow;
            if (mOpendDocuments.Contains(w))
                mOpendDocuments.Remove(w);
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

        protected override void OnClosed(EventArgs e)
        {
            base.OnClosed(e);
        }
    }
}
