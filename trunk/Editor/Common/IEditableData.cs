using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Common
{
    public interface IEditableData
    {
        /// <summary>
        /// Gets file name where data is stored
        /// </summary>
        String FileName
        {
            get;
        }

        /// <summary>
        /// Gets data for editing
        /// </summary>
        IProxyObject Data
        {
            get;
        }

        /// <summary>
        /// Gets tag that allows to choose editor
        /// </summary>
        String EditorTag
        {
            get;
        }
    }
}
