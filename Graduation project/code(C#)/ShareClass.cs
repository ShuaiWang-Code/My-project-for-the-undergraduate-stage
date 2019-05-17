using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WindowsFormsApplication1.App_Code
{
    class ShareClass
    {
        private static string _ID;
        public static string ID
        {
            get { return _ID; }
            set { _ID = value; }
        }

        private static string _Type;
        public static string Type
        {
            get { return _Type; }
            set { _Type = value; }
        }

        private static string _Name;
        public static string Name
        {
            get { return _Name; }
            set { _Name = value; }
        }
    }
}
