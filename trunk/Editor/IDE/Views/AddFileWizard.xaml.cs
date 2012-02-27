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
using System.Windows.Shapes;

namespace IDE.Views
{
    /// <summary>
    /// Interaction logic for NewFileWizard.xaml
    /// </summary>
    public partial class NewFileWizard : Window
    {
        public NewFileWizard()
        {
            InitializeComponent();
            mFileTypeList.DataContext = LevelEditor.Proxy.ModuleProxy.Instance.Categories;
        }

        private void mCancelBtn_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = false;
            Close();
        }

        private void mOkBtn_Click(object sender, RoutedEventArgs e)
        {
            LevelEditor.Proxy.CategoryProxy category = mFileTypeList.SelectedItem as LevelEditor.Proxy.CategoryProxy;
            if (category.Factory != null)
            {
                LevelEditor.Proxy.EntryProxy entry = category.Factory.CreateNewEntry();
                category.AddEntry(entry);
                entry.FileName = "../Data/" + category.Name + "/" + mFileName.Text;
                DialogResult = true;
            }
            else
            {
                DialogResult = false;
            }
            Close();
        }
    }
}
