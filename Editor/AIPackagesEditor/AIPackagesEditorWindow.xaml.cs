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
using MyApplication1.Commands;
using MyApplication1.Data;

namespace AIPackagesEditor
{
    /// <summary>
    /// Interaction logic for AIPackagesEditorWIndow
    /// </summary>
    public partial class AIPackagesEditorWindow : EditorWindow
    {
        AIRulesList mRUles;

        /// <summary>
        /// Default constructor
        /// </summary>
        public AIPackagesEditorWindow()
        {
            InitializeComponent();
            mRUles = new AIRulesList();
            list.DataContext = mRUles;
        }

        private void btnAdd_Click(object sender, RoutedEventArgs e)
        {
            AIRule rule = new AIRule();
            rule.ID = "Rule_" + mRUles.Rules.Count;

            CommandManager.Execute(new AddRule(mRUles, rule));
        }
    }
}
