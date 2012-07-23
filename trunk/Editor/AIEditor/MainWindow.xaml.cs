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
        int IDgenerator = 0;

        public MainWindow()
        {
            InitializeComponent();

            list.DataContext = mRules.Rules;

            ComboBoxItem cboxitem1 = new ComboBoxItem();
            cboxitem1.Content = "MoveTo";
            comboBox1.Items.Add(cboxitem1);
            ComboBoxItem cboxitem2 = new ComboBoxItem();
            cboxitem2.Content = "UseItem";
            comboBox1.Items.Add(cboxitem2);

            ComboBoxItem cboxitem3 = new ComboBoxItem();
            cboxitem3.Content = "RayCastQuery";
            comboBox2.Items.Add(cboxitem3);
            ComboBoxItem cboxitem4 = new ComboBoxItem();
            cboxitem4.Content = "GetByID";
            comboBox2.Items.Add(cboxitem4);
            ComboBoxItem cboxitem5 = new ComboBoxItem();
            cboxitem5.Content = "AABBQuery";
            comboBox2.Items.Add(cboxitem5);
            ComboBoxItem cboxitem6 = new ComboBoxItem();
            cboxitem6.Content = "RadiusQuery";
            comboBox2.Items.Add(cboxitem6);

            list.DataContext = mRules;
        }

        private void btnAdd_Click(object sender, RoutedEventArgs e)
        {
            AIRule rule = new AIRule();
            rule.ID = IDgenerator.ToString();
            IDgenerator++;
            Commands.AddRule command = new Commands.AddRule(mRules, rule);
            mCommandManager.Execute(command);
        }

        private void btnDel_Click(object sender, RoutedEventArgs e)
        {
            if (list.SelectedIndex != -1)
            {
                AIRule rule = new AIRule();
                foreach (AIRule r in mRules.Rules)
                {
                    if (r.ID == text.Text)
                        rule = r;
                }
                Commands.DelRule command = new Commands.DelRule(mRules, rule);
                mCommandManager.Execute(command);

            }
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
                AIRule rule = new AIRule();
                rule = mRules.Rules.ElementAt(list.SelectedIndex);
                text.Text = rule.ID;
                comboBox1.SelectedIndex = int.Parse(rule.Action.ID);
                text3.Text = rule.Priority.Code;
                text2.Text = rule.Condition.Code;
                comboBox2.SelectedIndex = int.Parse(rule.Target.Selector.ID);
            }
            else
            {
                text.Text = "";
                comboBox1.SelectedIndex = -1;
                text3.Text = "";
                text2.Text = "";
                comboBox2.SelectedIndex = -1;
            }
        }

        private void text_LostFocus(object sender, RoutedEventArgs e)
        {
            Commands.SetID command = new Commands.SetID(mRules.Rules.ElementAt(list.SelectedIndex), text.Text);
            mCommandManager.Execute(command);        
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
