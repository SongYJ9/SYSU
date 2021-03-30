using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.OleDb;
using System.IO;
using System.Windows.Forms.DataVisualization.Charting;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace 人体行为2
{
    public partial class 数据录入 : Form
    {
        Dictionary<string, Socket> clientList = new Dictionary<string, Socket>();
        OleDbDataAdapter addx;
        OleDbConnection connx;
        string strx;
        DataTable dt2x;
        string[] splitsx, splitsx2;
        int i = 0;
        public 数据录入()
        {
            InitializeComponent();
        }

        public static DataTable OpenCSV(string filePath)//读取csv文件并返回datatable
        {
            DataTable dt = new DataTable();
            FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read);
            StreamReader sr = new StreamReader(fs, System.Text.Encoding.Default);
            //记录每次读取的一行记录
            string strLine = "";
            //记录每行记录中的各字段内容
            string[] aryLine;
            //标示列数
            int columnCount = 0;
            //标示是否是读取的第一行
            bool IsFirst = true;
            //逐行读取CSV中的数据
            while ((strLine = sr.ReadLine()) != null)
            {
                aryLine = strLine.Split(',');
                if (IsFirst == true)
                {
                    IsFirst = false;
                    columnCount = aryLine.Length;
                    for (int i = 0; i < columnCount; i++)
                    {
                        DataColumn dc = new DataColumn(aryLine[i]);
                        dt.Columns.Add(dc);
                    }
                }
                else
                {
                    DataRow dr = dt.NewRow();
                    for (int j = 0; j < columnCount; j++)
                    {
                        dr[j] = aryLine[j];
                    }
                    dt.Rows.Add(dr);
                }
            }
            sr.Close();
            fs.Close();
            return dt;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if(i == 1)
            {
                i = 0;
                DirectoryInfo TheFolder = new DirectoryInfo(@"..\DataFile\activitydata");
                int number = 1;
                int n = TheFolder.GetFiles().Length - 1;
                try
                {
                    foreach (FileInfo NextFile in TheFolder.GetFiles())
                    {
                        splitsx2 = NextFile.Name.Split('.');
                        if (splitsx2[splitsx2.Length - 1] == "csv")
                        {
                            splitsx = NextFile.Name.Split('_');
                            strx = splitsx[0];
                            connx = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\mdbData\" + strx + "_data.mdb");
                            addx = new OleDbDataAdapter("select * from 行为表", connx);
                            dt2x = new DataTable();
                            dt2x = OpenCSV(NextFile.FullName);
                            OleDbCommandBuilder cmdb = new OleDbCommandBuilder(addx);
                            cmdb.QuotePrefix = "[";
                            cmdb.QuoteSuffix = "]";
                            addx.Update(dt2x);
                            File.Delete(NextFile.FullName);
                            number++;
                            label3.Text = number.ToString();
                        }
                    }
                    data.i = 1;
                    this.Close();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                    foreach (FileInfo NextFile in TheFolder.GetFiles())
                    {
                        splitsx2 = NextFile.Name.Split('.');
                        if (splitsx2[splitsx2.Length - 1] == "csv")
                        {
                            File.Move(NextFile.FullName, Application.StartupPath + @"\bugCsv\" + NextFile.Name);
                        }
                    }
                    MessageBox.Show("已将不能自动录入的csv文件放入bugCsv文件夹中！");
                }
            }
        }

        private void 数据录入_Load(object sender, EventArgs e)
        {
            timer1.Enabled = true;
            i = 1;
        }
    }
}
