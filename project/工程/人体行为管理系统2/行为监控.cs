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
    public partial class 行为监控 : Form
    {
        OleDbDataAdapter adp, adp2, adp3, adp4, adp5, adx;
        DataTable dt, dt2, dt3, dt4, dt5, dt6, dtx, ddt, ddt2, ddt3;
        OleDbConnection conn, conn2, conn3;
        Thread myServer;
        Socket server;
        int count = 0;
        int[] arr = new int[1000];
        int a, b, c;
        Dictionary<string, Socket> clientList = new Dictionary<string, Socket>();
        OleDbDataAdapter addx;
        OleDbConnection connx;
        string strx;
        DataTable dt2x;
        string[] splitsx, splitsx2;
        public 行为监控()
        {
            InitializeComponent(); 
            CheckForIllegalCrossThreadCalls = false;
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

        public void jiankong(int r)
        {
            string Id = dt2.Rows[r][0].ToString();
            conn3 = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\mdbData\" + Id + "_data.mdb");
            adx = new OleDbDataAdapter("select * from 行为表 where Yea = " + DateTime.Now.Year.ToString() + " and Mon = " + DateTime.Now.Month.ToString() + " and Day = " + DateTime.Now.Day.ToString(), conn3);
            dtx = new DataTable();
            adx.Fill(dtx);
            int i, j;
            listBox1.Items.Clear();
            listBox2.Items.Clear();
            listBox3.Items.Clear();
            int[] arr = new int[8];
            for (j = 0; j < 8; j++)
            {
                arr[j] = 0;
            }
            double i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0, i6 = 0, i7 = 0, i8 = 0;
            string s1 = "", s2 = "", s3 = "", s4 = "", s5 = "", s6 = "", s7 = "", s8 = "";
            adp4 = new OleDbDataAdapter("select * from 阈值设置 where ID = " + Id, conn);
            dt5 = new DataTable();
            adp4.Fill(dt5);
            for (j = 0; j < dtx.Rows.Count; j++)
            {
                if (dtx.Rows[j][7].ToString() == "sitting") i1++;
                else if (dtx.Rows[j][7].ToString() == "standing") i2++;
                else if (dtx.Rows[j][7].ToString() == "slowwalk") i3++;
                else if (dtx.Rows[j][7].ToString() == "fastwalk") i4++;
                else if (dtx.Rows[j][7].ToString() == "upstair") i5++;
                else if (dtx.Rows[j][7].ToString() == "downstair") i6++;
                else if (dtx.Rows[j][7].ToString() == "slowrun") i7++;
                else if (dtx.Rows[j][7].ToString() == "fastrun") i8++;
                if (i8 > Double.Parse(dt5.Rows[0][2].ToString()) * 1800 && arr[0] == 0 && dt5.Rows[0][2].ToString() != "0")
                {
                    s1 = (dtx.Rows[j][4].ToString().Length > 1 ? dtx.Rows[j][4].ToString() : "0" + dtx.Rows[j][4].ToString()) + ":" + (dtx.Rows[j][5].ToString().Length > 1 ? dtx.Rows[j][5].ToString() : "0" + dtx.Rows[j][5].ToString());
                    arr[0] = 1;
                }
                if (i7 > Double.Parse(dt5.Rows[0][4].ToString()) * 1800 && arr[1] == 0 && dt5.Rows[0][4].ToString() != "0")
                {
                    s2 = (dtx.Rows[j][4].ToString().Length > 1 ? dtx.Rows[j][4].ToString() : "0" + dtx.Rows[j][4].ToString()) + ":" + (dtx.Rows[j][5].ToString().Length > 1 ? dtx.Rows[j][5].ToString() : "0" + dtx.Rows[j][5].ToString());
                    arr[1] = 1;
                }
                if (i5 > Double.Parse(dt5.Rows[0][6].ToString()) * 1800 && arr[2] == 0 && dt5.Rows[0][6].ToString() != "0")
                {
                    s3 = (dtx.Rows[j][4].ToString().Length > 1 ? dtx.Rows[j][4].ToString() : "0" + dtx.Rows[j][4].ToString()) + ":" + (dtx.Rows[j][5].ToString().Length > 1 ? dtx.Rows[j][5].ToString() : "0" + dtx.Rows[j][5].ToString());
                    arr[2] = 1;
                }
                if (i6 > Double.Parse(dt5.Rows[0][8].ToString()) * 1800 && arr[3] == 0 && dt5.Rows[0][8].ToString() != "0")
                {
                    s4 = (dtx.Rows[j][4].ToString().Length > 1 ? dtx.Rows[j][4].ToString() : "0" + dtx.Rows[j][4].ToString()) + ":" + (dtx.Rows[j][5].ToString().Length > 1 ? dtx.Rows[j][5].ToString() : "0" + dtx.Rows[j][5].ToString());
                    arr[3] = 1;
                }
                if (i4 > Double.Parse(dt5.Rows[0][10].ToString()) * 1800 && arr[4] == 0 && dt5.Rows[0][10].ToString() != "0")
                {
                    s5 = (dtx.Rows[j][4].ToString().Length > 1 ? dtx.Rows[j][4].ToString() : "0" + dtx.Rows[j][4].ToString()) + ":" + (dtx.Rows[j][5].ToString().Length > 1 ? dtx.Rows[j][5].ToString() : "0" + dtx.Rows[j][5].ToString());
                    arr[4] = 1;
                }
                if (i3 > Double.Parse(dt5.Rows[0][12].ToString()) * 1800 && arr[5] == 0 && dt5.Rows[0][12].ToString() != "0")
                {
                    s6 = (dtx.Rows[j][4].ToString().Length > 1 ? dtx.Rows[j][4].ToString() : "0" + dtx.Rows[j][4].ToString()) + ":" + (dtx.Rows[j][5].ToString().Length > 1 ? dtx.Rows[j][5].ToString() : "0" + dtx.Rows[j][5].ToString());
                    arr[5] = 1;
                }
                if (i2 > Double.Parse(dt5.Rows[0][14].ToString()) * 1800 && arr[6] == 0 && dt5.Rows[0][14].ToString() != "0")
                {
                    s7 = (dtx.Rows[j][4].ToString().Length > 1 ? dtx.Rows[j][4].ToString() : "0" + dtx.Rows[j][4].ToString()) + ":" + (dtx.Rows[j][5].ToString().Length > 1 ? dtx.Rows[j][5].ToString() : "0" + dtx.Rows[j][5].ToString());
                    arr[6] = 1;
                }
                if (i1 > Double.Parse(dt5.Rows[0][16].ToString()) * 1800 && arr[7] == 0 && dt5.Rows[0][16].ToString() != "0")
                {
                    s8 = (dtx.Rows[j][4].ToString().Length > 1 ? dtx.Rows[j][4].ToString() : "0" + dtx.Rows[j][4].ToString()) + ":" + (dtx.Rows[j][5].ToString().Length > 1 ? dtx.Rows[j][5].ToString() : "0" + dtx.Rows[j][5].ToString());
                    arr[7] = 1;
                }
            }
            listBox2.Items.Add("快跑：" + Math.Round((i8 / 1800), 2).ToString() + "小时，" + ((arr[0] == 1 || i8 < Double.Parse(dt5.Rows[0][3].ToString()) * 1800) ? (arr[0] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("慢跑：" + Math.Round((i7 / 1800), 2).ToString() + "小时，" + ((arr[1] == 1 || i7 < Double.Parse(dt5.Rows[0][5].ToString()) * 1800) ? (arr[1] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("上楼：" + Math.Round((i5 / 1800), 2).ToString() + "小时，" + ((arr[2] == 1 || i5 < Double.Parse(dt5.Rows[0][7].ToString()) * 1800) ? (arr[2] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("下楼：" + Math.Round((i6 / 1800), 2).ToString() + "小时，" + ((arr[3] == 1 || i6 < Double.Parse(dt5.Rows[0][9].ToString()) * 1800) ? (arr[3] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("快走：" + Math.Round((i4 / 1800), 2).ToString() + "小时，" + ((arr[4] == 1 || i4 < Double.Parse(dt5.Rows[0][11].ToString()) * 1800) ? (arr[4] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("慢走：" + Math.Round((i3 / 1800), 2).ToString() + "小时，" + ((arr[5] == 1 || i3 < Double.Parse(dt5.Rows[0][13].ToString()) * 1800) ? (arr[5] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("站立：" + Math.Round((i2 / 1800), 2).ToString() + "小时，" + ((arr[6] == 1 || i2 < Double.Parse(dt5.Rows[0][15].ToString()) * 1800) ? (arr[6] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("静坐：" + Math.Round((i1 / 1800), 2).ToString() + "小时，" + ((arr[7] == 1 || i1 < Double.Parse(dt5.Rows[0][17].ToString()) * 1800) ? (arr[7] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            double sum = ((i1 + i2) * 60 + i3 * 168 + i4 * 469 + i5 * 235 + i6 * 134 + i7 * 469 + i8 * 603) / 1800;
            listBox1.Items.Add("今日总运动消耗热量 " + Math.Round(sum, 2).ToString() + "kcal。");
            if (arr[0] == 1)
            {
                listBox3.Items.Add(s1 + "，快跑行为过量，请注意减少快跑行为。");
            }
            if (arr[1] == 1)
            {
                listBox3.Items.Add(s2 + "，慢跑行为过量，请注意减少慢跑行为。");
            }
            if (arr[3] == 1)
            {
                listBox3.Items.Add(s4 + "，下楼行为过量，请注意减少下楼行为。");
            }
            if (arr[2] == 1)
            {
                listBox3.Items.Add(s3 + "，上楼行为过量，请注意减少上楼行为。");
            }
            if (arr[4] == 1)
            {
                listBox3.Items.Add(s5 + "，快走行为过量，请注意减少快走行为。");
            }
            if (arr[5] == 1)
            {
                listBox3.Items.Add(s6 + "，慢走行为过量，请注意减少慢走行为。");
            }
            if (arr[6] == 1)
            {
                listBox3.Items.Add(s7 + "，站立行为过量，请注意减少站立行为。");
            }
            if (arr[7] == 1)
            {
                listBox3.Items.Add(s8 + "，静坐行为过量，请注意减少静坐行为。");
            }
            adp5 = new OleDbDataAdapter("select * from 健康数据 where ID = " + Id, conn);
            dt6 = new DataTable();
            ddt = OpenCSV("健康文件_过量.csv");
            ddt2 = OpenCSV("健康文件_缺乏.csv");
            ddt3 = OpenCSV("健康文件_适量.csv");
            adp5.Fill(dt6);
            listBox1.Items.Add("");
            if (arr[0] == 1)
            {
                listBox1.Items.Add("今日快跑行为过量。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt.Rows[5][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[5][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt.Rows[5][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[5][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt.Rows[5][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[5][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt.Rows[5][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[5][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt.Rows[5][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[5][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt.Rows[5][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[5][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt.Rows[5][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[5][7].ToString() + "。");
                }
            }
            else if (i8 < Double.Parse(dt5.Rows[0][3].ToString()) * 1800)
            {
                listBox1.Items.Add("今日快跑行为缺乏。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt2.Rows[5][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[5][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt2.Rows[5][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[5][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt2.Rows[5][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[5][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt2.Rows[5][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[5][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt2.Rows[5][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[5][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt2.Rows[5][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[5][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt2.Rows[5][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[5][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日快跑行为正常。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt3.Rows[5][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[5][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt3.Rows[5][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[5][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt3.Rows[5][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[5][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt3.Rows[5][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[5][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt3.Rows[5][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[5][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt3.Rows[5][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[5][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt3.Rows[5][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[5][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[1] == 1)
            {
                listBox1.Items.Add("今日慢跑行为过量。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt.Rows[4][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[4][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt.Rows[4][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[4][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt.Rows[4][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[4][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt.Rows[4][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[4][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt.Rows[4][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[4][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt.Rows[4][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[4][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt.Rows[4][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[4][7].ToString() + "。");
                }
            }
            else if (i7 < Double.Parse(dt5.Rows[0][5].ToString()) * 1800)
            {
                listBox1.Items.Add("今日慢跑行为缺乏。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt2.Rows[4][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[4][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt2.Rows[4][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[4][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt2.Rows[4][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[4][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt2.Rows[4][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[4][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt2.Rows[4][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[4][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt2.Rows[4][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[4][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt2.Rows[4][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[4][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日慢跑行为正常。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt3.Rows[4][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[4][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt3.Rows[4][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[4][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt3.Rows[4][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[4][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt3.Rows[4][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[4][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt3.Rows[4][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[4][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt3.Rows[4][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[4][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt3.Rows[4][8].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[4][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[2] == 1)
            {
                listBox1.Items.Add("今日上楼行为过量。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt.Rows[6][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[6][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt.Rows[6][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[6][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt.Rows[6][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[6][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt.Rows[6][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[6][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt.Rows[6][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[6][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt.Rows[6][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[6][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt.Rows[6][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[6][7].ToString() + "。");
                }
            }
            else if (i5 < Double.Parse(dt5.Rows[0][7].ToString()) * 1800)
            {
                listBox1.Items.Add("今日上楼行为缺乏。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt2.Rows[6][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[6][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt2.Rows[6][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[6][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt2.Rows[6][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[6][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt2.Rows[6][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[6][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt2.Rows[6][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[6][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt2.Rows[6][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[6][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt2.Rows[6][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[6][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日上楼行为正常。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt3.Rows[6][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[6][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt3.Rows[6][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[6][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt3.Rows[6][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[6][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt3.Rows[6][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[6][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt3.Rows[6][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[6][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt3.Rows[6][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[6][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt3.Rows[6][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[6][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[3] == 1)
            {
                listBox1.Items.Add("今日下楼行为过量。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt.Rows[7][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[7][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt.Rows[7][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[7][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt.Rows[7][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[7][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt.Rows[7][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[7][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt.Rows[7][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[7][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt.Rows[7][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[7][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt.Rows[7][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[7][7].ToString() + "。");
                }
            }
            else if (i6 < Double.Parse(dt5.Rows[0][9].ToString()) * 1800)
            {
                listBox1.Items.Add("今日下楼行为缺乏。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt2.Rows[7][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[7][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt2.Rows[7][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[7][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt2.Rows[7][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[7][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt2.Rows[7][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[7][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt2.Rows[7][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[7][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt2.Rows[7][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[7][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt2.Rows[7][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[7][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日下楼行为正常。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt3.Rows[7][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[7][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt3.Rows[7][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[7][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt3.Rows[7][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[7][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt3.Rows[7][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[7][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt3.Rows[7][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[7][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt3.Rows[7][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[7][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt3.Rows[7][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[7][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[4] == 1)
            {
                listBox1.Items.Add("今日快走行为过量。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt.Rows[3][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[3][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt.Rows[3][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[3][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt.Rows[3][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[3][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt.Rows[3][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[3][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt.Rows[3][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[3][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt.Rows[3][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[3][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt.Rows[3][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[3][7].ToString() + "。");
                }
            }
            else if (i4 < Double.Parse(dt5.Rows[0][11].ToString()) * 1800)
            {
                listBox1.Items.Add("今日快走行为缺乏。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt2.Rows[3][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[3][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt2.Rows[3][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[3][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt2.Rows[3][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[3][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt2.Rows[3][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[3][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt2.Rows[3][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[3][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt2.Rows[3][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[3][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt2.Rows[3][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[3][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日快走行为正常。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt3.Rows[3][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[3][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt3.Rows[3][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[3][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt3.Rows[3][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[3][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt3.Rows[3][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[3][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt3.Rows[3][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[3][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt3.Rows[3][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[3][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt3.Rows[3][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[3][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[5] == 1)
            {
                listBox1.Items.Add("今日慢走行为过量。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt.Rows[2][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[2][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt.Rows[2][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[2][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt.Rows[2][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[2][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt.Rows[2][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[2][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt.Rows[2][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[2][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt.Rows[2][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[2][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt.Rows[2][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[2][7].ToString() + "。");
                }
            }
            else if (i3 < Double.Parse(dt5.Rows[0][13].ToString()) * 1800)
            {
                listBox1.Items.Add("今日慢走行为缺乏。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt2.Rows[2][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[2][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt2.Rows[2][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[2][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt2.Rows[2][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[2][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt2.Rows[2][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[2][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt2.Rows[2][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[2][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt2.Rows[2][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[2][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt2.Rows[2][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[2][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日慢走行为正常。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt3.Rows[2][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[2][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt3.Rows[2][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[2][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt3.Rows[2][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[2][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt3.Rows[2][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[2][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt3.Rows[2][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[2][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt3.Rows[2][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[2][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt3.Rows[2][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[2][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[6] == 1)
            {
                listBox1.Items.Add("今日站立行为过量。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt.Rows[1][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[1][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt.Rows[1][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[1][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt.Rows[1][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[1][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt.Rows[1][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[1][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt.Rows[1][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[1][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt.Rows[1][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[1][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt.Rows[1][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[1][7].ToString() + "。");
                }
            }
            else if (i2 < Double.Parse(dt5.Rows[0][15].ToString()) * 1800)
            {
                listBox1.Items.Add("今日站立行为缺乏。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt2.Rows[1][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[1][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt2.Rows[1][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[1][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt2.Rows[1][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[1][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt2.Rows[1][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[1][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt2.Rows[1][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[1][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt2.Rows[1][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[1][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt2.Rows[1][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[1][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日站立行为正常。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt3.Rows[1][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[1][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt3.Rows[1][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[1][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt3.Rows[1][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[1][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt3.Rows[1][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[1][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt3.Rows[1][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[1][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt3.Rows[1][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[1][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt3.Rows[1][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[1][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[7] == 1)
            {
                listBox1.Items.Add("今日静坐行为过量。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt.Rows[0][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[0][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt.Rows[0][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[0][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt.Rows[0][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[0][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt.Rows[0][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[0][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt.Rows[0][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[0][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt.Rows[0][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[0][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt.Rows[0][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[0][7].ToString() + "。");
                }
            }
            else if (i1 < Double.Parse(dt5.Rows[0][17].ToString()) * 1800)
            {
                listBox1.Items.Add("今日静坐行为缺乏。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt2.Rows[0][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[0][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt2.Rows[0][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[0][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt2.Rows[0][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[0][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt2.Rows[0][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[0][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt2.Rows[0][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[0][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt2.Rows[0][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[0][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt2.Rows[0][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[0][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日静坐行为正常。");
                if (Int32.Parse(dt6.Rows[0][2].ToString()) > 0 && ddt3.Rows[0][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[0][1].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][3].ToString()) > 0 && ddt3.Rows[0][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[0][2].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][4].ToString()) > 0 && ddt3.Rows[0][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[0][3].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][5].ToString()) > 0 && ddt3.Rows[0][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[0][4].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][6].ToString()) > 0 && ddt3.Rows[0][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[0][5].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][7].ToString()) > 0 && ddt3.Rows[0][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[0][6].ToString() + "。");
                }
                if (Int32.Parse(dt6.Rows[0][8].ToString()) > 0 && ddt3.Rows[0][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[0][7].ToString() + "。");
                }
            }
            int[,] a = new int[24, 9];
            int[,] a2 = new int[72, 9];
            int[,] a3 = new int[288, 9];
            for (i = 0; i < dtx.Rows.Count; i++)
            {
                if (dtx.Rows[i][7].ToString() == "sitting") j = 1;
                else if (dtx.Rows[i][7].ToString() == "standing") j = 2;
                else if (dtx.Rows[i][7].ToString() == "slowwalk") j = 3;
                else if (dtx.Rows[i][7].ToString() == "fastwalk") j = 4;
                else if (dtx.Rows[i][7].ToString() == "upstair") j = 6;
                else if (dtx.Rows[i][7].ToString() == "downstair") j = 5;
                else if (dtx.Rows[i][7].ToString() == "slowrun") j = 7;
                else j = 8;
                a[Int32.Parse(dtx.Rows[i][4].ToString()), j]++;
                a2[Int32.Parse(dtx.Rows[i][4].ToString()) * 3 + Int32.Parse(dtx.Rows[i][5].ToString()) / 20, j]++;
                a3[Int32.Parse(dtx.Rows[i][4].ToString()) * 12 + Int32.Parse(dtx.Rows[i][5].ToString()) / 5, j]++;
            }
            for (i = 0; i < 24; i++)
            {
                List<int> list2 = new List<int>() { a[i, 0], a[i, 1], a[i, 2], a[i, 3], a[i, 4], a[i, 5], a[i, 6], a[i, 7], a[i, 8] };
                int max = list2.Max(), index = 0;
                if (max == 0)
                {
                    chart3.Series[0].Points[i].YValues[0] = 1;
                }
                else
                {
                    for (j = 0; j < 9; j++)
                    {
                        if (a[i, j] == max) index = j;
                    }
                    chart3.Series[0].Points[i].YValues[0] = index + 1;
                }
            }
            chart3.Series[0].Points[0].IsEmpty = false;
            for (i = 0; i < 72; i++)
            {
                List<int> list2 = new List<int>() { a2[i, 0], a2[i, 1], a2[i, 2], a2[i, 3], a2[i, 4], a2[i, 5], a2[i, 6], a2[i, 7], a2[i, 8] };
                int max = list2.Max(), index = 0;
                if (max == 0)
                {
                    chart1.Series[0].Points[i].YValues[0] = 1;
                }
                else
                {
                    for (j = 0; j < 9; j++)
                    {
                        if (a2[i, j] == max) index = j;
                    }
                    chart1.Series[0].Points[i].YValues[0] = index + 1;
                }
            }
            chart1.Series[0].Points[0].IsEmpty = false;
            for (i = 0; i < 288; i++)
            {
                List<int> list2 = new List<int>() { a3[i, 0], a3[i, 1], a3[i, 2], a3[i, 3], a3[i, 4], a3[i, 5], a3[i, 6], a3[i, 7], a3[i, 8] };
                int max = list2.Max(), index = 0;
                if (max == 0)
                {
                    chart2.Series[0].Points[i].YValues[0] = 1;
                }
                else
                {
                    for (j = 0; j < 9; j++)
                    {
                        if (a3[i, j] == max) index = j;
                    }
                    chart2.Series[0].Points[i].YValues[0] = index + 1;
                }
            }
            chart2.Series[0].Points[0].IsEmpty = false;
            groupBox2.Visible = true;
        }

        void MySocket()
        {
            try
            {
                server = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);
                server.Bind(new IPEndPoint(IPAddress.Parse("127.0.0.3"), 8000));
                Thread t = new Thread(ReciveMsg);//开启接收消息线程
                t.Start();
            }
            catch(Exception ex)
            {
                //MessageBox.Show(ex.Message.ToString());
            }
        }

        void ReciveMsg(object o)
        {
            try
            {
                while (true)
                {
                    EndPoint point = new IPEndPoint(IPAddress.Any, 0);//用来保存发送方的ip和端口号
                    byte[] buffer = new byte[1024];
                    int length = server.ReceiveFrom(buffer, ref point);//接收数据
                    string message = Encoding.UTF8.GetString(buffer, 0, length);
                    MessageBox.Show("收到消息！\n" + message);
                    System.IO.File.WriteAllText("monitoring.txt", message);
                    string[] split = message.Split('{','[');
                    string[] split2 = split[2].Split(',',']');
                    string sss = "";
                    for (int i = 0; i < split2.Length - 1; i++)
                    {
                        sss += split2[i];
                        if(i + 2 < split2.Length)
                        {
                            sss += " or Id =";
                        }
                    }
                    if(sss != "")
                    {
                        adp = new OleDbDataAdapter("select ID,姓名 from 个人基本信息 where ID = " + sss, conn);
                        adp2 = new OleDbDataAdapter("select * from 阈值设置 where ID = " + sss, conn);
                        dt = new DataTable();
                        dt2 = new DataTable();
                        dt3 = new DataTable();
                        int i,j;
                        adp.Fill(dt);
                        adp.Fill(dt2);
                        adp2.Fill(dt3);
                        dataGridView1.DataSource = dt2;
                        dataGridView1.Columns[0].Width = 70;
                        dataGridView1.Columns[1].Width = 100;
                        for (i = 0; i < dataGridView1.Rows.Count; i++)
                        {
                            dataGridView1.Rows[i].Height = 28;
                        }
                        yuzhishezhi(0, 0);
                        textBox1.Text = dt2.Rows[0][0].ToString();
                        jiankong(0);
                    }
                    else
                    {
                        dt2 = new DataTable();
                        dataGridView1.DataSource = dt2;
                        groupBox2.Visible = groupBox3.Visible = groupBox4.Visible = false;
                        textBox1.Text = "暂无监控用户";
                    }
                }
            }
            catch(Exception ex)
            {
                //MessageBox.Show(ex.Message.ToString());
            }
        }

        public void yuzhishezhi(int r1, int count)
        {
            int r = r1 + count * 15;
            label5.Text = dt3.Rows[r][0].ToString();
            label7.Text = dt3.Rows[r][1].ToString();
            textBox3.Text = dt3.Rows[r][2].ToString();
            textBox18.Text = dt3.Rows[r][3].ToString();
            textBox4.Text = dt3.Rows[r][4].ToString();
            textBox17.Text = dt3.Rows[r][5].ToString();
            textBox5.Text = dt3.Rows[r][6].ToString();
            textBox16.Text = dt3.Rows[r][7].ToString();
            textBox6.Text = dt3.Rows[r][8].ToString();
            textBox15.Text = dt3.Rows[r][9].ToString();
            textBox7.Text = dt3.Rows[r][10].ToString();
            textBox14.Text = dt3.Rows[r][11].ToString();
            textBox8.Text = dt3.Rows[r][12].ToString();
            textBox13.Text = dt3.Rows[r][13].ToString();
            textBox9.Text = dt3.Rows[r][14].ToString();
            textBox12.Text = dt3.Rows[r][15].ToString();
            textBox10.Text = dt3.Rows[r][16].ToString();
            textBox11.Text = dt3.Rows[r][17].ToString();
        }
        private void 行为监控_Load(object sender, EventArgs e)
        {
            timer1.Enabled = timer2.Enabled = true;
            a = 1;
            b = c = 0;
            groupBox2.Visible = true;
            groupBox3.Visible = groupBox4.Visible = false;
            chart3.ChartAreas[0].AxisY.LabelStyle.Enabled = false;
            conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + @"..\DataBase\人体行为.mdb");
            adp = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
            adp2 = new OleDbDataAdapter("select * from 阈值设置", conn);
            dt = new DataTable();
            dt2 = new DataTable();
            dt3 = new DataTable();
            adp.Fill(dt);
            adp.Fill(dt2);
            adp2.Fill(dt3);
            dataGridView1.DataSource = dt2;
            dataGridView1.Columns[0].Width = 70;
            dataGridView1.Columns[1].Width = 100;
            for (int i = 0; i < dataGridView1.Rows.Count; i++)
            {
                dataGridView1.Rows[i].Height = 28;
            }
            yuzhishezhi(0, count);
            dt2 = new DataTable();
            dataGridView1.DataSource = dt2;
            //设置这个线程是后台线程
            myServer = new Thread(MySocket);
            myServer.IsBackground = true;
            myServer.Start();
            textBox1.Text = "暂无监控用户";
            radioButton3.Checked = true;
            for(int k = 24; k < 288; k++)
            {
                chart2.Series[0].Points.Add(1);
            }
            int h=0, m=0;
            string s;
            for (int k = 0; k < 144; k++)
            {
                m += 10;
                if(m >= 60)
                {
                    m = 0;
                    h += 1;
                }
                s = (h < 10 ? "0" + h.ToString() : h.ToString()) + ":" + (m < 10 ? "0" + m.ToString() : m.ToString());
                CustomLabel label = new CustomLabel();
                label.Text = s;
                label.ToPosition = 4 * k + 4;
                chart2.ChartAreas[0].AxisX.CustomLabels.Add(label);
            }
            h = 0;
            for (int k = 0; k < 24; k++)
            {
                h += 1;
                s = (h < 10 ? "0" + h.ToString() : h.ToString()) + ":00";
                CustomLabel label = new CustomLabel();
                label.Text = s;
                label.ToPosition = 6 * k + 6;
                chart1.ChartAreas[0].AxisX.CustomLabels.Add(label);
            }
            h = 0;
            for (int k = 0; k < 6; k++)
            {
                h += 4;
                s = (h < 10 ? "0" + h.ToString() : h.ToString()) + ":00";
                CustomLabel label = new CustomLabel();
                label.Text = s;
                label.ToPosition = 8 * k + 8;
                chart3.ChartAreas[0].AxisX.CustomLabels.Add(label);
            }
            chart1.ChartAreas[0].AxisY.LabelStyle.Enabled = false;
            chart2.ChartAreas[0].AxisY.LabelStyle.Enabled = false;
            chart3.ChartAreas[0].AxisY.LabelStyle.Enabled = false;
            StreamReader sr = File.OpenText("monitoring.txt");
            string ss = sr.ReadLine();
            if(ss != null)
            {
                string[] split = ss.Split('{', '[');
                string[] split2 = split[2].Split(',', ']');
                string sss = "";
                for (int i = 0; i < split2.Length - 1; i++)
                {
                    sss += split2[i];
                    if (i + 2 < split2.Length)
                    {
                        sss += " or Id =";
                    }
                }
                if (sss != "")
                {
                    adp = new OleDbDataAdapter("select ID,姓名 from 个人基本信息 where ID = " + sss, conn);
                    adp2 = new OleDbDataAdapter("select * from 阈值设置 where ID = " + sss, conn);
                    dt = new DataTable();
                    dt2 = new DataTable();
                    dt3 = new DataTable();
                    adp.Fill(dt);
                    adp.Fill(dt2);
                    adp2.Fill(dt3);
                    dataGridView1.DataSource = dt2;
                    dataGridView1.Columns[0].Width = 70;
                    dataGridView1.Columns[1].Width = 100;
                    for (int i3 = 0; i3 < dataGridView1.Rows.Count; i3++)
                    {
                        dataGridView1.Rows[i3].Height = 28;
                    }
                    yuzhishezhi(0, 0);
                    textBox1.Text = dt2.Rows[0][0].ToString();
                    jiankong(0);
                }
                else
                {
                    dt2 = new DataTable();
                    dataGridView1.DataSource = dt2;
                    groupBox2.Visible = groupBox3.Visible = groupBox4.Visible = false;
                    textBox1.Text = "暂无监控用户";
                }
            }
            else
            {
                dt2 = new DataTable();
                dataGridView1.DataSource = dt2;
                groupBox2.Visible = groupBox3.Visible = groupBox4.Visible = false;
                textBox1.Text = "暂无监控用户";
            }
            for (int i = 0; i < dataGridView1.Columns.Count; i++)
            {
                dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }
            sr.Close();
        }

        private void 行为查看ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(dataGridView1.Rows.Count > 0)
            {
                a = 1;
                b = c = 0;
                groupBox2.Visible = true;
                groupBox3.Visible = groupBox4.Visible = false;
            }
        }

        private void textBox3_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox3.Text);
                textBox3.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox4_Leave(object sender, EventArgs e)
        {
            try 
            {
                double d = double.Parse(textBox4.Text);
                textBox4.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox5_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox5.Text);
                textBox5.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox6_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox6.Text);
                textBox6.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox7_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox7.Text);
                textBox7.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox8_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox8.Text);
                textBox8.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox9_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox9.Text);
                textBox9.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox10_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox10.Text);
                textBox10.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox11_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox11.Text);
                textBox11.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox12_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox12.Text);
                textBox12.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox13_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox13.Text);
                textBox13.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox14_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox14.Text);
                textBox14.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void button12_Click(object sender, EventArgs e)
        {
            groupBox2.Visible = false;
        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            int r = hScrollBar1.Value;
            if(radioButton2.Checked == true)
            {
                chart1.Location = new Point(-78 - (int)(r * 13.5), -5);
            }
            else if(radioButton1.Checked == true)
            {
                chart2.Location = new Point(-312 - (int)(r * 73.8), 3);
            }
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            label118.Text = "单位：20min";
            groupBox5.Visible = true;
            chart1.Visible = true;
            chart3.Visible = chart2.Visible = false;
            hScrollBar1.Visible = true;
            hScrollBar1.Value = 0; 
            chart1.Location = new Point(-78, -5);
        }

        private void 更新数据ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DirectoryInfo TheFolder = new DirectoryInfo(@"..\DataFile\activitydata");
            if (TheFolder.GetFiles().Length > 1)
            {
                timer3.Enabled = true;
                int number = 1;
                int n = TheFolder.GetFiles().Length - 1;
                数据录入 window = new 数据录入();
                window.label3.Text = number.ToString();
                window.label4.Text = "/ " + n.ToString();
                window.Show();
            }
            else
            {
                MessageBox.Show("数据库已是最新！");
            }
        }

        private void timer3_Tick(object sender, EventArgs e)
        {
            if(data.i == 1)
            {
                timer3.Enabled = false;
                if (dataGridView1.Rows.Count > 0)
                {
                    int r1 = dataGridView1.CurrentCell.RowIndex;
                    if (r1 < dt.Rows.Count - count * 15 && r1 >= 0)
                    {
                        textBox1.Text = dt.Rows[r1 + count * 15][0].ToString();
                        yuzhishezhi(r1, count);
                    }
                    int r = dataGridView1.CurrentCell.RowIndex;
                    if (dataGridView1.SelectedRows.Count == 1)
                    {
                        jiankong(r);
                    }
                }
            }
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)
        {
            label118.Text = "单位：1hour";
            groupBox5.Visible = false;
            chart3.Visible = true;
            chart1.Visible = chart2.Visible = false;
            hScrollBar1.Visible = false;
            hScrollBar1.Value = 0;
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            label118.Text = "单位：5min";
            groupBox5.Visible = true;
            chart2.Visible = true;
            chart3.Visible = chart1.Visible = false;
            hScrollBar1.Visible = true;
            hScrollBar1.Value = 0;
            chart2.Location = new Point(-312, 3);
        }


        private void textBox15_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox15.Text);
                textBox15.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox16_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox16.Text);
                textBox16.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void textBox17_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox17.Text);
                textBox17.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void timer2_Tick(object sender, EventArgs e)
        {
            DirectoryInfo TheFolder = new DirectoryInfo(@"..\DataFile\activitydata");
            if (TheFolder.GetFiles().Length > 1)
            {
                timer3.Enabled = true;
                int number = 1;
                int n = TheFolder.GetFiles().Length - 1;
                数据录入 window = new 数据录入();
                window.label3.Text = number.ToString();
                window.label4.Text = "/ " + n.ToString();
                window.Show();
            }
        }

        private void textBox18_Leave(object sender, EventArgs e)
        {
            try
            {
                double d = double.Parse(textBox18.Text);
                textBox18.Text = Math.Round(d, 1).ToString();
            }
            catch
            {
                MessageBox.Show("请输入浮点数格式！");
            }
        }

        private void button13_Click(object sender, EventArgs e)//点击“退出报告”按钮
        {
            groupBox4.Visible = false;
        }

        private void 预警设置ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(dataGridView1.Rows.Count > 0)
            {
                b = 1;
                a = c = 0;
                groupBox2.Visible = groupBox4.Visible = false;
                groupBox3.Visible = true;
            }
        }

        private void 健康报告ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(dataGridView1.Rows.Count > 0)
            {
                c = 1;
                a = b = 0;
                groupBox4.Visible = true;
                groupBox3.Visible = groupBox2.Visible = false;
            }
        }

        private void button8_Click(object sender, EventArgs e)//点击“退出设置”按钮
        {
            groupBox3.Visible = false;
        }

        private void button5_Click(object sender, EventArgs e)//点击“保存修改”按钮
        {
            try
            {
                int r = dataGridView1.CurrentCell.RowIndex;
                r = r + count * 15;
                dt3.Rows[r][2] = textBox3.Text;
                dt3.Rows[r][3] = textBox18.Text;
                dt3.Rows[r][4] = textBox4.Text;
                dt3.Rows[r][5] = textBox17.Text;
                dt3.Rows[r][6] = textBox5.Text;
                dt3.Rows[r][7] = textBox16.Text;
                dt3.Rows[r][8] = textBox6.Text;
                dt3.Rows[r][9] = textBox15.Text;
                dt3.Rows[r][10] = textBox7.Text;
                dt3.Rows[r][11] = textBox14.Text;
                dt3.Rows[r][12] = textBox8.Text;
                dt3.Rows[r][13] = textBox13.Text;
                dt3.Rows[r][14] = textBox9.Text;
                dt3.Rows[r][15] = textBox12.Text;
                dt3.Rows[r][16] = textBox10.Text;
                dt3.Rows[r][17] = textBox11.Text;
                OleDbCommandBuilder cmdb = new OleDbCommandBuilder(adp2);
                adp2.Update(dt3);
                MessageBox.Show("修改成功！");
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
            }
        }

        private void timer1_Tick(object sender, EventArgs e)//每隔一个小时监控一次
        {
            string str1 = DateTime.Now.Year.ToString(), str2 = DateTime.Now.Month.ToString(), str3 = DateTime.Now.Day.ToString(), Id;
            string warn = "", temp = "";
            int r = dt.Rows.Count, i, j;
            for(i = 0; i < r; i++)
            {
                Id = dt.Rows[i][0].ToString();
                conn2 = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\mdbData\" + Id + "_data.mdb");
                adp3 = new OleDbDataAdapter("select * from 行为表 where Yea = " + str1 + " and Mon = " + str2 + " and Day = " + str3, conn2);
                dt4 = new DataTable();
                adp3.Fill(dt4);
                int[] arr = new int[8];
                double i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0, i6 = 0, i7 = 0, i8 = 0;
                for (j = 0; j < dt4.Rows.Count; j++)
                {
                    if (dt4.Rows[j][7].ToString() == "sitting") i1++;
                    else if (dt4.Rows[j][7].ToString() == "standing") i2++;
                    else if (dt4.Rows[j][7].ToString() == "slowwalk") i3++;
                    else if (dt4.Rows[j][7].ToString() == "fastwalk") i4++;
                    else if (dt4.Rows[j][7].ToString() == "upstair") i5++;
                    else if (dt4.Rows[j][7].ToString() == "downstair") i6++;
                    else if (dt4.Rows[j][7].ToString() == "slowrun") i7++;
                    else if (dt4.Rows[j][7].ToString() == "fastrun") i8++;
                }
                adp4 = new OleDbDataAdapter("select * from 阈值设置 where ID = " + Id, conn);
                dt5 = new DataTable();
                adp4.Fill(dt5);
                if (i8 > Double.Parse(dt5.Rows[0][2].ToString()) * 1800) arr[0] = 1;
                if (i7 > Double.Parse(dt5.Rows[0][4].ToString()) * 1800) arr[1] = 1;
                if (i5 > Double.Parse(dt5.Rows[0][6].ToString()) * 1800) arr[2] = 1;
                if (i6 > Double.Parse(dt5.Rows[0][8].ToString()) * 1800) arr[3] = 1;
                if (i4 > Double.Parse(dt5.Rows[0][10].ToString()) * 1800) arr[4] = 1;
                if (i3 > Double.Parse(dt5.Rows[0][12].ToString()) * 1800) arr[5] = 1;
                if (i2 > Double.Parse(dt5.Rows[0][14].ToString()) * 1800) arr[6] = 1;
                if (i1 > Double.Parse(dt5.Rows[0][16].ToString()) * 1800) arr[7] = 1;
                if (arr[0] == 1)
                {
                    temp = "ID为 " + Id + "的用户【快跑】行为过量！目前已超时" + (Math.Round((i8 - Double.Parse(dt5.Rows[0][2].ToString()) * 1800) / 60,1)).ToString() + "分钟！\n";
                    warn += temp;
                }
                if (arr[1] == 1)
                {
                    temp = "ID为 " + Id + "的用户【慢跑】行为过量！目前已超时" + (Math.Round((i7 - Double.Parse(dt5.Rows[0][4].ToString()) * 1800) / 60, 1)).ToString() + "分钟！\n";
                    warn += temp;
                }
                if (arr[2] == 1)
                {
                    temp = "ID为 " + Id + "的用户【上楼】行为过量！目前已超时" + (Math.Round((i5 - Double.Parse(dt5.Rows[0][6].ToString()) * 1800) / 60, 1)).ToString() + "分钟！\n";
                    warn += temp;
                }
                if (arr[3] == 1)
                {
                    temp = "ID为 " + Id + "的用户【下楼】行为过量！目前已超时" + (Math.Round((i6 - Double.Parse(dt5.Rows[0][8].ToString()) * 1800) / 60, 1)).ToString() + "分钟！\n";
                    warn += temp;
                }
                if (arr[4] == 1)
                {
                    temp = "ID为 " + Id + "的用户【快走】行为过量！目前已超时" + (Math.Round((i4 - Double.Parse(dt5.Rows[0][10].ToString()) * 1800) / 60, 1)).ToString() + "分钟！\n";
                    warn += temp;
                }
                if (arr[5] == 1)
                {
                    temp = "ID为 " + Id + "的用户【慢走】行为过量！目前已超时" + (Math.Round((i3 - Double.Parse(dt5.Rows[0][12].ToString()) * 1800) / 60, 1)).ToString() + "分钟！\n";
                    warn += temp;
                }
                if (arr[6] == 1)
                {
                    temp = "ID为 " + Id + "的用户【站立】行为过量！目前已超时" + (Math.Round((i2 - Double.Parse(dt5.Rows[0][14].ToString()) * 1800) / 60, 1)).ToString() + "分钟！\n";
                    warn += temp;
                }
                if (arr[7] == 1)
                {
                    temp = "ID为 " + Id + "的用户【静坐】行为过量！目前已超时" + (Math.Round((i1 - Double.Parse(dt5.Rows[0][16].ToString()) * 1800) / 60, 1)).ToString() + "分钟！\n";
                    warn += temp;
                }
            }
            if (warn != "")
            {
                warn = "在" + str1 + "年" + str2 + "月" + str3 + "日：\n" + warn;
                MessageBox.Show(warn);
            }
        }
        private void button6_Click(object sender, EventArgs e)//点击“重置数据”按钮
        {
            int r = dataGridView1.CurrentCell.RowIndex;
            yuzhishezhi(r, count);
        }

        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            int r1 = e.RowIndex;
            if (r1 < dt.Rows.Count - count * 15 && r1 >= 0)
            {
                textBox1.Text = dt.Rows[r1 + count * 15][0].ToString();
                yuzhishezhi(r1, count);
            }
            int r = dataGridView1.CurrentCell.RowIndex;
            if (dataGridView1.SelectedRows.Count == 1)
            {
                jiankong(r);
            }
        }

        private void 行为监控_FormClosed(object sender, FormClosedEventArgs e)
        {
            server.Close();
            主页面 a = new 主页面();
            a.Show();
            a.deng();
        }
    }
}
