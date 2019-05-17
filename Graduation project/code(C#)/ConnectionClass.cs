using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WindowsFormsApplication1.App_Code
{
    class ConnectionClass
    {
        public static string GetConStr
        {
            get
            {
                return "server=.;database=CarSystemDB;uid=sa;pwd=123456";
            }
        }
    }
}
