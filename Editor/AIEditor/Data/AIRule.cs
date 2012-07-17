using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;

namespace MyApplication1.Data
{
    /// <summary>
    /// Model of AI rule
    /// </summary>
    public class AIRule : Common.ProxyObject
    {
        #region Members
        String mID;
        #endregion

        #region Properties

        /// <summary>
        /// Gets or sets identifier of the rule
        /// </summary>
        public String ID
        {
            get
            {
                return mID;
            }
            set
            {
                mID = value;
                RaisePropertyChanged(this, "ID");
            }
        }

        #endregion

        AIAction Action;
        ActionTarget Target;
        Script Condition;
        Script Priority;

        #region Constructors
        #endregion

        #region Methods
        #endregion
    }
}
