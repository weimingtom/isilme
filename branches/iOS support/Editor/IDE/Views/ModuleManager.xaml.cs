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
using Common.Views;
using Common;
using LevelEditor.Proxy;
using LevelEditor;

namespace IDE.Views
{
    /// <summary>
    /// Interaction logic for ModuleManager.xaml
    /// </summary>
    public partial class ModuleManager : ToolWindow
    {
        public ModuleManager()
        {
            InitializeComponent();
            LevelEditor.Isilme.Instance.Loaded += new EventHandler(OnEngineLoaded);

           // mModuleTree.DataContext = LevelEditor.Proxy.ModuleProxy.Instance;
            CommandBindings.Add(new CommandBinding(ApplicationCommands.Save, ExecuterdSaveCommand, CaneExecuteSaveCommand));
        }

        void OnEngineLoaded(object sender, EventArgs e)
        {
            System.Collections.ObjectModel.ObservableCollection<LevelEditor.Proxy.ModuleProxy> collection = new System.Collections.ObjectModel.ObservableCollection<LevelEditor.Proxy.ModuleProxy>();
            collection.Add(LevelEditor.Proxy.ModuleProxy.Instance);
            mModuleTree.DataContext = collection;
        }

        private void mModuleTree_MouseDoubleClick(object sender, MouseButtonEventArgs e)
        {
            EntryProxy entry = mModuleTree.SelectedItem as EntryProxy;
            if (entry != null)
            {
                // Execute command for opening entry editor
            }
        }

        private void mNewBtn_Click(object sender, RoutedEventArgs e)
        {
            NewFileWizard wizardWindow = new NewFileWizard();
            wizardWindow.ShowDialog();
        }

        private void ExecuterdSaveCommand(Object sender, RoutedEventArgs e)
        {
            Isilme.Instance.SaveModule("../Data/Master.imf");
        }

        private void CaneExecuteSaveCommand(Object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }
    }
}
