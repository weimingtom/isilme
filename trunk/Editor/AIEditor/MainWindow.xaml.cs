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
using Common;
using MyApplication1.Data;


namespace MyApplication1
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        Common.CommandManager mCommandManager = new Common.CommandManager();
        Data.AIRulesList mRules = new AIRulesList();

        public MainWindow()
        {
                       /* MyData d = new MyData();
            System.Collections.ObjectModel.ObservableCollection<MyData> l = new();

            d.Data = "dfdf";*/

            InitializeComponent();
            list.DataContext = mRules;
        }

        private void tabControl2_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void btnAdd_Click(object sender, RoutedEventArgs e)
        {
            AIRule rule = new AIRule();
            rule.ID = "3143";
            Commands.AddRule command = new Commands.AddRule(mRules, rule);
            mCommandManager.Execute(command);
        }

        private void btnDel_Click(object sender, RoutedEventArgs e)
        {
            if (list.SelectedIndex != -1)
                list.Items.RemoveAt(list.SelectedIndex);
            
            else
                MessageBox.Show("Выберите элемент");
        }

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            if (mCommandManager.UndoIsPossible())
            mCommandManager.Undo();
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            if (mCommandManager.RedoIsPossible())
                mCommandManager.Redo();
        }

        private void list_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (list.SelectedIndex != -1)
            {
                text.Text = list.SelectedItem.ToString();
                text2.Text = list.SelectedItem.ToString();
                text3.Text = list.SelectedItem.ToString();
            }
        }

    }


    public class MyData
    {
        String mData;
        public String Data
        {
            get
            {
                return mData;
            }
            set
            {
                mData = value;
            }
        }
    }
}
