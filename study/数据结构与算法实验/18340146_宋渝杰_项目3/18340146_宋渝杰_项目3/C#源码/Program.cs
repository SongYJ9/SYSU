using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace project_3
{
    public struct data
    {
        static public int i = 0;
        static public string name = "";
        static public bool isMan = true;
        static public string nianfen = "";
        static public string name2 = "";
    }
    static class Program
    {
        /// <summary>
        /// 应用程序的主入口点。
        /// </summary>
        

        [STAThread]
        
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new 族谱());
        }
    }
}
