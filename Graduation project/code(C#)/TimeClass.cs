using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WindowsFormsApplication1.App_Code
{
    class TimeClass
    {
        private static int _SHI;
        public static int SHI
        {
            get { return _SHI; }
            set { _SHI = value; }
        }

        private static int _FEN;
        public static int FEN
        {
            get { return _FEN; }
            set { _FEN = value; }
        }

        private static int _MIAO;
        public static int MIAO
        {
            get { return _MIAO; }
            set { _MIAO = value; }
        }
    }
}
