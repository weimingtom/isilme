using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Reflection;

namespace XCob
{
	public class ObjectPropertyGrid : PropertyGrid
	{
		#region Members

		ActionManager mActionManager;
		Object mTemp;

		#endregion

		public ActionManager ActionManager
		{
			get { return mActionManager; }
			set { mActionManager = value; }
		}

		protected override void OnSelectedObjectsChanged(EventArgs e)
		{
			base.OnSelectedObjectsChanged(e);
			mTemp = SelectedObject;
		}
		protected override void OnPropertyValueChanged(PropertyValueChangedEventArgs e)
		{
			base.OnPropertyValueChanged(e);

			//String property = e.ChangedItem.Label;
			//GridItem gridItem = e.ChangedItem;

			//while (gridItem.Parent.Parent.Parent != null)
			//{
			//    gridItem = gridItem.Parent;
			//    property = gridItem.Label;
			//}

			//Object oldValue = mTemp.GetType().InvokeMember(
			//    property,
			//    BindingFlags.Public |
			//    BindingFlags.NonPublic |
			//    BindingFlags.Instance |
			//    BindingFlags.GetProperty,
			//    null,
			//    mTemp,
			//    null
			//);

			//mActionManager.ExecuteCommand(new SetProperty(SelectedObject, property, gridItem.Value, oldValue));
			//mActionManager.ExecuteCommand(new SetProperty(mTemp, property, gridItem.Value));
			//mActionManager.FinaliseCommand();
		}
	}
}
