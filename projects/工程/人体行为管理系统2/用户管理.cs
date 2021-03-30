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
    public partial class 用户管理 : Form
    {
        OleDbDataAdapter addx;
        OleDbConnection connx, connx2;
        string strx;
        DataTable dt2x;
        string[] splitsx, splitsx2;
        string str = "", str2 = "";
        string[] splits, splits2, splits3, sp, sp2, sp3, sp4, sp5;
        OpenFileDialog dlgOpenFile;
        OleDbDataAdapter add, add2, add3, adp, adp2, adp4, adp5, adx, adx2, adx3, adxz;
        DataTable dt, dt2, dt3, dt4, dt5, dt6, dt7, dt8, dtx, dtx2, dtx3, dt51, dt61, dtxz, ddt, ddt2, ddt3;
        OleDbConnection conn, conn2, conn3;
        DateTime DT;
        int fir = 1, las = 1, wei, count = 0, fir2 = 1, las2 = 1, wei2, count2 = 0;
        int[] arr = new int[1000], arr2 = new int[1000];
        int y, M, d, h, m, s, p = 0, y2, M2, d2, h2, m2, s2;
        int y3, M3, d3;
        int c1, c2, e1, e2;
        Thread myServer;
        Socket server;
        Dictionary<string, Socket> clientList = new Dictionary<string, Socket>();
        public 用户管理()
        {
            InitializeComponent();
        }

        public void baogao(int r)
        {
            string Id = dt8.Rows[r][0].ToString();
            conn3 = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\mdbData\" + Id + "_data.mdb");
            adxz = new OleDbDataAdapter("select * from 行为表 where Yea = " + dateTimePicker3.Value.Year.ToString() + " and Mon = " + dateTimePicker3.Value.Month.ToString() + " and Day = " + dateTimePicker3.Value.Day.ToString(), conn3);
            dtxz = new DataTable();
            adxz.Fill(dtxz);
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
            dt51 = new DataTable();
            adp4.Fill(dt51);
            for (j = 0; j < dtxz.Rows.Count; j++)
            {
                if (dtxz.Rows[j][7].ToString() == "sitting") i1++;
                else if (dtxz.Rows[j][7].ToString() == "standing") i2++;
                else if (dtxz.Rows[j][7].ToString() == "slowwalk") i3++;
                else if (dtxz.Rows[j][7].ToString() == "fastwalk") i4++;
                else if (dtxz.Rows[j][7].ToString() == "upstair") i5++;
                else if (dtxz.Rows[j][7].ToString() == "downstair") i6++;
                else if (dtxz.Rows[j][7].ToString() == "slowrun") i7++;
                else if (dtxz.Rows[j][7].ToString() == "fastrun") i8++;
                if (i8 > Double.Parse(dt51.Rows[0][2].ToString()) * 1800 && arr[0] == 0 && dt51.Rows[0][2].ToString() != "0")
                {
                    s1 = (dtxz.Rows[j][4].ToString().Length > 1 ? dtxz.Rows[j][4].ToString() : "0" + dtxz.Rows[j][4].ToString()) + ":" + (dtxz.Rows[j][5].ToString().Length > 1 ? dtxz.Rows[j][5].ToString() : "0" + dtxz.Rows[j][5].ToString());
                    arr[0] = 1;
                }
                if (i7 > Double.Parse(dt51.Rows[0][4].ToString()) * 1800 && arr[1] == 0 && dt51.Rows[0][4].ToString() != "0")
                {
                    s2 = (dtxz.Rows[j][4].ToString().Length > 1 ? dtxz.Rows[j][4].ToString() : "0" + dtxz.Rows[j][4].ToString()) + ":" + (dtxz.Rows[j][5].ToString().Length > 1 ? dtxz.Rows[j][5].ToString() : "0" + dtxz.Rows[j][5].ToString());
                    arr[1] = 1;
                }
                if (i5 > Double.Parse(dt51.Rows[0][6].ToString()) * 1800 && arr[2] == 0 && dt51.Rows[0][6].ToString() != "0")
                {
                    s3 = (dtxz.Rows[j][4].ToString().Length > 1 ? dtxz.Rows[j][4].ToString() : "0" + dtxz.Rows[j][4].ToString()) + ":" + (dtxz.Rows[j][5].ToString().Length > 1 ? dtxz.Rows[j][5].ToString() : "0" + dtxz.Rows[j][5].ToString());
                    arr[2] = 1;
                }
                if (i6 > Double.Parse(dt51.Rows[0][8].ToString()) * 1800 && arr[3] == 0 && dt51.Rows[0][8].ToString() != "0")
                {
                    s4 = (dtxz.Rows[j][4].ToString().Length > 1 ? dtxz.Rows[j][4].ToString() : "0" + dtxz.Rows[j][4].ToString()) + ":" + (dtxz.Rows[j][5].ToString().Length > 1 ? dtxz.Rows[j][5].ToString() : "0" + dtxz.Rows[j][5].ToString());
                    arr[3] = 1;
                }
                if (i4 > Double.Parse(dt51.Rows[0][10].ToString()) * 1800 && arr[4] == 0 && dt51.Rows[0][10].ToString() != "0")
                {
                    s5 = (dtxz.Rows[j][4].ToString().Length > 1 ? dtxz.Rows[j][4].ToString() : "0" + dtxz.Rows[j][4].ToString()) + ":" + (dtxz.Rows[j][5].ToString().Length > 1 ? dtxz.Rows[j][5].ToString() : "0" + dtxz.Rows[j][5].ToString());
                    arr[4] = 1;
                }
                if (i3 > Double.Parse(dt51.Rows[0][12].ToString()) * 1800 && arr[5] == 0 && dt51.Rows[0][12].ToString() != "0")
                {
                    s6 = (dtxz.Rows[j][4].ToString().Length > 1 ? dtxz.Rows[j][4].ToString() : "0" + dtxz.Rows[j][4].ToString()) + ":" + (dtxz.Rows[j][5].ToString().Length > 1 ? dtxz.Rows[j][5].ToString() : "0" + dtxz.Rows[j][5].ToString());
                    arr[5] = 1;
                }
                if (i2 > Double.Parse(dt51.Rows[0][14].ToString()) * 1800 && arr[6] == 0 && dt51.Rows[0][14].ToString() != "0")
                {
                    s7 = (dtxz.Rows[j][4].ToString().Length > 1 ? dtxz.Rows[j][4].ToString() : "0" + dtxz.Rows[j][4].ToString()) + ":" + (dtxz.Rows[j][5].ToString().Length > 1 ? dtxz.Rows[j][5].ToString() : "0" + dtxz.Rows[j][5].ToString());
                    arr[6] = 1;
                }
                if (i1 > Double.Parse(dt51.Rows[0][16].ToString()) * 1800 && arr[7] == 0 && dt51.Rows[0][16].ToString() != "0")
                {
                    s8 = (dtxz.Rows[j][4].ToString().Length > 1 ? dtxz.Rows[j][4].ToString() : "0" + dtxz.Rows[j][4].ToString()) + ":" + (dtxz.Rows[j][5].ToString().Length > 1 ? dtxz.Rows[j][5].ToString() : "0" + dtxz.Rows[j][5].ToString());
                    arr[7] = 1;
                }
            }
            listBox2.Items.Add("快跑：" + Math.Round((i8 / 1800), 2).ToString() + "小时，" + ((arr[0] == 1 || i8 < Double.Parse(dt51.Rows[0][3].ToString()) * 1800) ? (arr[0] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("慢跑：" + Math.Round((i7 / 1800), 2).ToString() + "小时，" + ((arr[1] == 1 || i7 < Double.Parse(dt51.Rows[0][5].ToString()) * 1800) ? (arr[1] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("上楼：" + Math.Round((i5 / 1800), 2).ToString() + "小时，" + ((arr[2] == 1 || i5 < Double.Parse(dt51.Rows[0][7].ToString()) * 1800) ? (arr[2] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("下楼：" + Math.Round((i6 / 1800), 2).ToString() + "小时，" + ((arr[3] == 1 || i6 < Double.Parse(dt51.Rows[0][9].ToString()) * 1800) ? (arr[3] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("快走：" + Math.Round((i4 / 1800), 2).ToString() + "小时，" + ((arr[4] == 1 || i4 < Double.Parse(dt51.Rows[0][11].ToString()) * 1800) ? (arr[4] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("慢走：" + Math.Round((i3 / 1800), 2).ToString() + "小时，" + ((arr[5] == 1 || i3 < Double.Parse(dt51.Rows[0][13].ToString()) * 1800) ? (arr[5] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("站立：" + Math.Round((i2 / 1800), 2).ToString() + "小时，" + ((arr[6] == 1 || i2 < Double.Parse(dt51.Rows[0][15].ToString()) * 1800) ? (arr[6] == 1 ? "过量" : "缺乏") : "正常" + "。"));
            listBox2.Items.Add("静坐：" + Math.Round((i1 / 1800), 2).ToString() + "小时，" + ((arr[7] == 1 || i1 < Double.Parse(dt51.Rows[0][17].ToString()) * 1800) ? (arr[7] == 1 ? "过量" : "缺乏") : "正常" + "。"));
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
            dt61 = new DataTable();
            adp5.Fill(dt61);
            ddt = OpenCSV("健康文件_过量.csv");
            ddt2 = OpenCSV("健康文件_缺乏.csv");
            ddt3 = OpenCSV("健康文件_适量.csv");
            listBox1.Items.Add("");
            if (arr[0] == 1)
            {
                listBox1.Items.Add("今日快跑行为过量。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt.Rows[5][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[5][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt.Rows[5][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[5][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt.Rows[5][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[5][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt.Rows[5][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[5][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt.Rows[5][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[5][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt.Rows[5][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[5][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt.Rows[5][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[5][7].ToString() + "。");
                }
            }
            else if (i8 < Double.Parse(dt51.Rows[0][3].ToString()) * 1800)
            {
                listBox1.Items.Add("今日快跑行为缺乏。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt2.Rows[5][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[5][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt2.Rows[5][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[5][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt2.Rows[5][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[5][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt2.Rows[5][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[5][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt2.Rows[5][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[5][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt2.Rows[5][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[5][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt2.Rows[5][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[5][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日快跑行为正常。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt3.Rows[5][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[5][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt3.Rows[5][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[5][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt3.Rows[5][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[5][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt3.Rows[5][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[5][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt3.Rows[5][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[5][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt3.Rows[5][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[5][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt3.Rows[5][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[5][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[1] == 1)
            {
                listBox1.Items.Add("今日慢跑行为过量。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt.Rows[4][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[4][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt.Rows[4][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[4][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt.Rows[4][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[4][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt.Rows[4][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[4][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt.Rows[4][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[4][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt.Rows[4][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[4][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt.Rows[4][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[4][7].ToString() + "。");
                }
            }
            else if (i7 < Double.Parse(dt51.Rows[0][5].ToString()) * 1800)
            {
                listBox1.Items.Add("今日慢跑行为缺乏。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt2.Rows[4][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[4][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt2.Rows[4][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[4][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt2.Rows[4][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[4][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt2.Rows[4][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[4][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt2.Rows[4][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[4][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt2.Rows[4][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[4][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt2.Rows[4][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[4][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日慢跑行为正常。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt3.Rows[4][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[4][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt3.Rows[4][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[4][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt3.Rows[4][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[4][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt3.Rows[4][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[4][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt3.Rows[4][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[4][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt3.Rows[4][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[4][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt3.Rows[4][8].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[4][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[2] == 1)
            {
                listBox1.Items.Add("今日上楼行为过量。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt.Rows[6][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[6][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt.Rows[6][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[6][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt.Rows[6][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[6][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt.Rows[6][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[6][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt.Rows[6][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[6][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt.Rows[6][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[6][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt.Rows[6][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[6][7].ToString() + "。");
                }
            }
            else if (i5 < Double.Parse(dt51.Rows[0][7].ToString()) * 1800)
            {
                listBox1.Items.Add("今日上楼行为缺乏。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt2.Rows[6][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[6][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt2.Rows[6][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[6][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt2.Rows[6][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[6][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt2.Rows[6][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[6][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt2.Rows[6][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[6][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt2.Rows[6][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[6][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt2.Rows[6][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[6][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日上楼行为正常。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt3.Rows[6][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[6][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt3.Rows[6][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[6][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt3.Rows[6][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[6][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt3.Rows[6][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[6][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt3.Rows[6][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[6][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt3.Rows[6][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[6][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt3.Rows[6][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[6][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[3] == 1)
            {
                listBox1.Items.Add("今日下楼行为过量。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt.Rows[7][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[7][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt.Rows[7][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[7][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt.Rows[7][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[7][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt.Rows[7][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[7][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt.Rows[7][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[7][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt.Rows[7][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[7][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt.Rows[7][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[7][7].ToString() + "。");
                }
            }
            else if (i6 < Double.Parse(dt51.Rows[0][9].ToString()) * 1800)
            {
                listBox1.Items.Add("今日下楼行为缺乏。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt2.Rows[7][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[7][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt2.Rows[7][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[7][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt2.Rows[7][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[7][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt2.Rows[7][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[7][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt2.Rows[7][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[7][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt2.Rows[7][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[7][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt2.Rows[7][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[7][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日下楼行为正常。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt3.Rows[7][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[7][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt3.Rows[7][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[7][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt3.Rows[7][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[7][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt3.Rows[7][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[7][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt3.Rows[7][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[7][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt3.Rows[7][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[7][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt3.Rows[7][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[7][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[4] == 1)
            {
                listBox1.Items.Add("今日快走行为过量。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt.Rows[3][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[3][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt.Rows[3][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[3][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt.Rows[3][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[3][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt.Rows[3][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[3][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt.Rows[3][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[3][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt.Rows[3][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[3][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt.Rows[3][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[3][7].ToString() + "。");
                }
            }
            else if (i4 < Double.Parse(dt51.Rows[0][11].ToString()) * 1800)
            {
                listBox1.Items.Add("今日快走行为缺乏。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt2.Rows[3][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[3][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt2.Rows[3][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[3][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt2.Rows[3][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[3][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt2.Rows[3][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[3][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt2.Rows[3][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[3][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt2.Rows[3][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[3][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt2.Rows[3][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[3][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日快走行为正常。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt3.Rows[3][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[3][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt3.Rows[3][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[3][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt3.Rows[3][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[3][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt3.Rows[3][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[3][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt3.Rows[3][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[3][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt3.Rows[3][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[3][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt3.Rows[3][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[3][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[5] == 1)
            {
                listBox1.Items.Add("今日慢走行为过量。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt.Rows[2][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[2][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt.Rows[2][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[2][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt.Rows[2][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[2][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt.Rows[2][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[2][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt.Rows[2][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[2][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt.Rows[2][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[2][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt.Rows[2][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[2][7].ToString() + "。");
                }
            }
            else if (i3 < Double.Parse(dt51.Rows[0][13].ToString()) * 1800)
            {
                listBox1.Items.Add("今日慢走行为缺乏。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt2.Rows[2][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[2][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt2.Rows[2][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[2][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt2.Rows[2][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[2][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt2.Rows[2][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[2][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt2.Rows[2][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[2][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt2.Rows[2][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[2][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt2.Rows[2][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[2][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日慢走行为正常。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt3.Rows[2][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[2][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt3.Rows[2][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[2][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt3.Rows[2][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[2][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt3.Rows[2][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[2][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt3.Rows[2][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[2][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt3.Rows[2][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[2][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt3.Rows[2][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[2][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[6] == 1)
            {
                listBox1.Items.Add("今日站立行为过量。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt.Rows[1][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[1][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt.Rows[1][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[1][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt.Rows[1][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[1][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt.Rows[1][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[1][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt.Rows[1][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[1][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt.Rows[1][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[1][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt.Rows[1][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[1][7].ToString() + "。");
                }
            }
            else if (i2 < Double.Parse(dt51.Rows[0][15].ToString()) * 1800)
            {
                listBox1.Items.Add("今日站立行为缺乏。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt2.Rows[1][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[1][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt2.Rows[1][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[1][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt2.Rows[1][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[1][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt2.Rows[1][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[1][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt2.Rows[1][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[1][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt2.Rows[1][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[1][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt2.Rows[1][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[1][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日站立行为正常。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt3.Rows[1][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[1][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt3.Rows[1][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[1][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt3.Rows[1][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[1][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt3.Rows[1][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[1][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt3.Rows[1][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[1][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt3.Rows[1][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[1][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt3.Rows[1][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[1][7].ToString() + "。");
                }
            }
            listBox1.Items.Add("");
            if (arr[7] == 1)
            {
                listBox1.Items.Add("今日静坐行为过量。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt.Rows[0][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt.Rows[0][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt.Rows[0][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt.Rows[0][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt.Rows[0][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt.Rows[0][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt.Rows[0][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt.Rows[0][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt.Rows[0][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt.Rows[0][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt.Rows[0][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt.Rows[0][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt.Rows[0][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt.Rows[0][7].ToString() + "。");
                }
            }
            else if (i1 < Double.Parse(dt51.Rows[0][17].ToString()) * 1800)
            {
                listBox1.Items.Add("今日静坐行为缺乏。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt2.Rows[0][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt2.Rows[0][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt2.Rows[0][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt2.Rows[0][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt2.Rows[0][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt2.Rows[0][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt2.Rows[0][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt2.Rows[0][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt2.Rows[0][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt2.Rows[0][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt2.Rows[0][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt2.Rows[0][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt2.Rows[0][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt2.Rows[0][7].ToString() + "。");
                }
            }
            else
            {
                listBox1.Items.Add("今日静坐行为正常。");
                if (Int32.Parse(dt61.Rows[0][2].ToString()) > 0 && ddt3.Rows[0][1].ToString().Length != 0)
                {
                    listBox1.Items.Add("对肥胖问题的影响：" + ddt3.Rows[0][1].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][3].ToString()) > 0 && ddt3.Rows[0][2].ToString().Length != 0)
                {
                    listBox1.Items.Add("对糖尿病问题的影响：" + ddt3.Rows[0][2].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][4].ToString()) > 0 && ddt3.Rows[0][3].ToString().Length != 0)
                {
                    listBox1.Items.Add("对心脑血管问题的影响：" + ddt3.Rows[0][3].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][5].ToString()) > 0 && ddt3.Rows[0][4].ToString().Length != 0)
                {
                    listBox1.Items.Add("对呼吸疾病的影响：" + ddt3.Rows[0][4].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][6].ToString()) > 0 && ddt3.Rows[0][5].ToString().Length != 0)
                {
                    listBox1.Items.Add("对骨折的影响：" + ddt3.Rows[0][5].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][7].ToString()) > 0 && ddt3.Rows[0][6].ToString().Length != 0)
                {
                    listBox1.Items.Add("对关节置换的影响：" + ddt3.Rows[0][6].ToString() + "。");
                }
                if (Int32.Parse(dt61.Rows[0][8].ToString()) > 0 && ddt3.Rows[0][7].ToString().Length != 0)
                {
                    listBox1.Items.Add("对其他问题的影响：" + ddt3.Rows[0][7].ToString() + "。");
                }
            }
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
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
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
                    MessageBox.Show("行为监控收到消息！\n" + message);
                    System.IO.File.WriteAllText("monitoring.txt", message);
                }
            }
            catch (Exception ex)
            {
                //MessageBox.Show(ex.Message.ToString());
            }
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
        public int judgeDay(int y, int M)
        {
            if (M == 1 || M == 3 || M == 5 || M == 7 || M == 8 || M == 10 || M == 12) return 31;
            else if (M == 2)
            {
                if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) return 29;
                else return 28;
            }
            else return 30;
        }

        public void wulala(int cou,int r2 = 0)
        {
            int r = r2 + cou*15;
            for (int i = 0; i < dataGridView1.Rows.Count; i++)
            {
                dataGridView1.Rows[i].Height = 28;
            }
            label84.Text = dt.Rows[r][0].ToString();
            textBox1.Text = label84.Text;
            textBox31.Text = dt.Rows[r][1].ToString();
            DT = Convert.ToDateTime(dt.Rows[r][3].ToString());
            dateTimePicker4.Value = DT;
            int y = DateTime.Now.Year - DT.Year;
            label85.Text = y.ToString();
            if (dt.Rows[r][4].ToString() == "男") radioButton7.Checked = true;
            else radioButton6.Checked = true;
            if (dt.Rows[r][5].ToString() == "") pictureBox2.LoadAsync(Application.StartupPath + @"\photos\基本背景.png");
            else pictureBox2.LoadAsync(Application.StartupPath + @"\photos\" + dt.Rows[r][5].ToString());
            str = dt.Rows[r][5].ToString();
            label53.Text = dt3.Rows[r][0].ToString();
            label77.Text = dt3.Rows[r][1].ToString();
            textBox37.Text = dt3.Rows[r][2].ToString();
            textBox38.Text = dt3.Rows[r][3].ToString();
            label56.Text = dt3.Rows[r][4].ToString();
            textBox39.Text = dt3.Rows[r][5].ToString();
            textBox30.Text = dt3.Rows[r][6].ToString();
            textBox40.Text = dt3.Rows[r][7].ToString();
            textBox41.Text = dt3.Rows[r][8].ToString();
            textBox42.Text = dt3.Rows[r][9].ToString();
            numericUpDown1.Value = Int32.Parse(dt3.Rows[r][10].ToString());
            numericUpDown2.Value = Int32.Parse(dt3.Rows[r][11].ToString());
            label79.Text = dt5.Rows[r][0].ToString();
            label88.Text = dt5.Rows[r][1].ToString();
            numericUpDown18.Value = Int32.Parse(dt5.Rows[r][2].ToString());
            numericUpDown17.Value = Int32.Parse(dt5.Rows[r][3].ToString());
            numericUpDown16.Value = Int32.Parse(dt5.Rows[r][4].ToString());
            numericUpDown14.Value = Int32.Parse(dt5.Rows[r][5].ToString());
            numericUpDown13.Value = Int32.Parse(dt5.Rows[r][6].ToString());
            numericUpDown12.Value = Int32.Parse(dt5.Rows[r][7].ToString());
            numericUpDown15.Value = Int32.Parse(dt5.Rows[r][8].ToString());
        }

        public void tongji()
        {
            int r = dataGridView3.CurrentCell.RowIndex;
            if (dataGridView3.SelectedRows.Count == 1)
            {
                sp = dateTimePicker1.Text.Split('年', '月', '日');
                y = Int32.Parse(sp[0]);
                M = Int32.Parse(sp[1]);
                d = Int32.Parse(sp[2]);
                sp2 = dateTimePicker6.Text.Split('年', '月', '日');
                y2 = Int32.Parse(sp2[0]);
                M2 = Int32.Parse(sp2[1]);
                d2 = Int32.Parse(sp2[2]);
                sp3 = dateTimePicker7.Text.Split(':');
                h = Int32.Parse(sp3[0]);
                m = Int32.Parse(sp3[1]);
                s = Int32.Parse(sp3[2]);
                sp4 = dateTimePicker8.Text.Split(':');
                h2 = Int32.Parse(sp4[0]);
                m2 = Int32.Parse(sp4[1]);
                s2 = Int32.Parse(sp4[2]);
                if (y > y2 || (y == y2 && M > M2) || (y == y2 && M == M2 && d > d2))
                {
                    MessageBox.Show("起始日期应小于终止日期！");
                }
                else if ((d == d2 && h > h2) || (d == d2 && h == h2 && m > m2) || (d == d2 && h == h2 && m == m2 && s >= s2))
                {
                    MessageBox.Show("起始时间应小于终止时间！");
                }
                else
                {
                    string Id = dt8.Rows[r][0].ToString();
                    conn2 = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\mdbData\" + Id + "_data.mdb");
                    adx = new OleDbDataAdapter("select * from 行为表 where ( Yea > " + y.ToString() + " or ( Yea = " + y.ToString() + " and Mon > " + M.ToString() + " ) or ( Yea = " + y.ToString() + " and Mon = " + M.ToString() + " and Day > " + d.ToString() +
                        " ) or ( Yea = " + y.ToString() + " and Mon = " + M.ToString() + " and Day = " + d.ToString() + " and Hour > " + h.ToString() + " ) or ( Yea = " + y.ToString() + " and Mon = " + M.ToString() + " and Day = " + d.ToString() + " and Hour = " + h.ToString() +
                        " and Minute > " + m.ToString() + " ) or ( Yea = " + y.ToString() + " and Mon = " + M.ToString() + " and Day = " + d.ToString() + " and Hour = " + h.ToString() + " and Minute = " + m.ToString() + " and Second >= " + s.ToString() + " ) ) and ( Yea < " + y2.ToString() +
                        " or ( Yea = " + y2.ToString() + " and Mon < " + M2.ToString() + " ) or ( Yea = " + y2.ToString() + " and Mon = " + M2.ToString() + " and Day < " + d2.ToString() + " ) or ( Yea = " + y2.ToString() + " and Mon = " + M2.ToString() + " and Day = " + d2.ToString() +
                        " and Hour < " + h2.ToString() + " ) or ( Yea = " + y2.ToString() + " and Mon = " + M2.ToString() + " and Day = " + d2.ToString() + " and Hour = " + h2.ToString() + " and Minute < " + m2.ToString() + " ) or ( Yea = " + y2.ToString() + " and Mon = " + M2.ToString() +
                        " and Day = " + d2.ToString() + " and Hour = " + h2.ToString() + " and Minute = " + m2.ToString() + " and Second <= " + s2.ToString() + " ) )", conn2);
                    dtx = new DataTable();
                    adx.Fill(dtx);
                    connx2 = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + @"..\DataBase\人体行为.mdb");
                    adx3 = new OleDbDataAdapter("select * from 阈值设置 where ID = " + Id , connx2);
                    dtx3 = new DataTable();
                    adx3.Fill(dtx3);
                    int i;
                    double i1 = 0, i2 = 0, i3 = 0, i4 = 0, i5 = 0, i6 = 0, i7 = 0, i8 = 0;
                    for (i = 0; i < dtx.Rows.Count; i++)
                    {
                        if (dtx.Rows[i][7].ToString() == "sitting") i1++;
                        else if (dtx.Rows[i][7].ToString() == "standing") i2++;
                        else if (dtx.Rows[i][7].ToString() == "slowwalk") i3++;
                        else if (dtx.Rows[i][7].ToString() == "fastwalk") i4++;
                        else if (dtx.Rows[i][7].ToString() == "upstair") i5++;
                        else if (dtx.Rows[i][7].ToString() == "downstair") i6++;
                        else if (dtx.Rows[i][7].ToString() == "slowrun") i7++;
                        else if (dtx.Rows[i][7].ToString() == "fastrun") i8++;
                    }
                    chart2.Series[0].Points[0].YValues[0] = i1;
                    chart2.Series[0].Points[1].YValues[0] = i2;
                    chart2.Series[0].Points[2].YValues[0] = i3;
                    chart2.Series[0].Points[3].YValues[0] = i4;
                    chart2.Series[0].Points[4].YValues[0] = i5;
                    chart2.Series[0].Points[5].YValues[0] = i6;
                    chart2.Series[0].Points[6].YValues[0] = i7;
                    chart2.Series[0].Points[7].YValues[0] = i8;
                    chart2.Series[0].Points[0].IsEmpty = false;
                    if (i1 == 0 && i2 == 0 && i3 == 0 && i4 == 0 && i5 == 0 && i6 == 0 && i7 == 0 && i8 == 0)
                    {
                        chart1.Visible = label108.Visible = pictureBox3.Visible = pictureBox4.Visible = pictureBox5.Visible = false;
                        label119.Visible = label120.Visible = label121.Visible = false;
                    }
                    else
                    {
                        chart1.Visible = label108.Visible = pictureBox3.Visible = pictureBox4.Visible = pictureBox5.Visible = true;
                        label119.Visible = label120.Visible = label121.Visible = true;
                        i1 *= 2;
                        i2 *= 2;
                        i3 *= 2;
                        i4 *= 2;
                        i5 *= 2;
                        i6 *= 2;
                        i7 *= 2;
                        i8 *= 2;
                        int[] color = new int[8];
                        if(radioButton1.Checked == true)
                        {
                            if (dtx3.Rows[0][16].ToString() != "0" && i1 > Double.Parse(dtx3.Rows[0][16].ToString()) * 3600) color[0] = 1;
                            else if (dtx3.Rows[0][17].ToString() != "0" && i1 < Double.Parse(dtx3.Rows[0][17].ToString()) * 3600) color[0] = -1;
                            else color[0] = 0;
                            if (dtx3.Rows[0][14].ToString() != "0" && i2 > Double.Parse(dtx3.Rows[0][14].ToString()) * 3600) color[1] = 1;
                            else if (dtx3.Rows[0][15].ToString() != "0" && i2 < Double.Parse(dtx3.Rows[0][15].ToString()) * 3600) color[1] = -1;
                            else color[1] = 0;
                            if (dtx3.Rows[0][12].ToString() != "0" && i3 > Double.Parse(dtx3.Rows[0][12].ToString()) * 3600) color[2] = 1;
                            else if (dtx3.Rows[0][13].ToString() != "0" && i3 < Double.Parse(dtx3.Rows[0][13].ToString()) * 3600) color[2] = -1;
                            else color[2] = 0;
                            if (dtx3.Rows[0][10].ToString() != "0" && i4 > Double.Parse(dtx3.Rows[0][10].ToString()) * 3600) color[3] = 1;
                            else if (dtx3.Rows[0][11].ToString() != "0" && i4 < Double.Parse(dtx3.Rows[0][11].ToString()) * 3600) color[3] = -1;
                            else color[3] = 0;
                            if (dtx3.Rows[0][6].ToString() != "0" && i5 > Double.Parse(dtx3.Rows[0][6].ToString()) * 3600) color[4] = 1;//这是上楼的
                            else if (dtx3.Rows[0][7].ToString() != "0" && i5 < Double.Parse(dtx3.Rows[0][7].ToString()) * 3600) color[4] = -1;
                            else color[4] = 0;
                            if (dtx3.Rows[0][8].ToString() != "0" && i6 > Double.Parse(dtx3.Rows[0][8].ToString()) * 3600) color[5] = 1;//这是下楼的
                            else if (dtx3.Rows[0][9].ToString() != "0" && i6 < Double.Parse(dtx3.Rows[0][9].ToString()) * 3600) color[5] = -1;
                            else color[5] = 0;
                            if (dtx3.Rows[0][4].ToString() != "0" && i7 > Double.Parse(dtx3.Rows[0][4].ToString()) * 3600) color[6] = 1;
                            else if (dtx3.Rows[0][5].ToString() != "0" && i7 < Double.Parse(dtx3.Rows[0][5].ToString()) * 3600) color[6] = -1;
                            else color[6] = 0;
                            if (dtx3.Rows[0][2].ToString() != "0" && i8 > Double.Parse(dtx3.Rows[0][2].ToString()) * 3600) color[7] = 1;
                            else if (dtx3.Rows[0][3].ToString() != "0" && i8 < Double.Parse(dtx3.Rows[0][3].ToString()) * 3600) color[7] = -1;
                            else color[7] = 0;
                        }
                        else if(radioButton2.Checked == true)
                        {
                            if (dtx3.Rows[0][16].ToString() != "0" && i1 > Double.Parse(dtx3.Rows[0][16].ToString()) * 3600 * 7) color[0] = 1;
                            else if (dtx3.Rows[0][17].ToString() != "0" && i1 < Double.Parse(dtx3.Rows[0][17].ToString()) * 3600 * 7) color[0] = -1;
                            else color[0] = 0;
                            if (dtx3.Rows[0][14].ToString() != "0" && i2 > Double.Parse(dtx3.Rows[0][14].ToString()) * 3600 * 7) color[1] = 1;
                            else if (dtx3.Rows[0][15].ToString() != "0" && i2 < Double.Parse(dtx3.Rows[0][15].ToString()) * 3600 * 7) color[1] = -1;
                            else color[1] = 0;
                            if (dtx3.Rows[0][12].ToString() != "0" && i3 > Double.Parse(dtx3.Rows[0][12].ToString()) * 3600 * 7) color[2] = 1;
                            else if (dtx3.Rows[0][13].ToString() != "0" && i3 < Double.Parse(dtx3.Rows[0][13].ToString()) * 3600 * 7) color[2] = -1;
                            else color[2] = 0;
                            if (dtx3.Rows[0][10].ToString() != "0" && i4 > Double.Parse(dtx3.Rows[0][10].ToString()) * 3600 * 7) color[3] = 1;
                            else if (dtx3.Rows[0][11].ToString() != "0" && i4 < Double.Parse(dtx3.Rows[0][11].ToString()) * 3600 * 7) color[3] = -1;
                            else color[3] = 0;
                            if (dtx3.Rows[0][8].ToString() != "0" && i5 > Double.Parse(dtx3.Rows[0][8].ToString()) * 3600 * 7) color[4] = 1;
                            else if (dtx3.Rows[0][9].ToString() != "0" && i5 < Double.Parse(dtx3.Rows[0][9].ToString()) * 3600 * 7) color[4] = -1;
                            else color[4] = 0;
                            if (dtx3.Rows[0][6].ToString() != "0" && i6 > Double.Parse(dtx3.Rows[0][6].ToString()) * 3600 * 7) color[5] = 1;
                            else if (dtx3.Rows[0][7].ToString() != "0" && i6 < Double.Parse(dtx3.Rows[0][7].ToString()) * 3600 * 7) color[5] = -1;
                            else color[5] = 0;
                            if (dtx3.Rows[0][4].ToString() != "0" && i7 > Double.Parse(dtx3.Rows[0][4].ToString()) * 3600 * 7) color[6] = 1;
                            else if (dtx3.Rows[0][5].ToString() != "0" && i7 < Double.Parse(dtx3.Rows[0][5].ToString()) * 3600 * 7) color[6] = -1;
                            else color[6] = 0;
                            if (dtx3.Rows[0][2].ToString() != "0" && i8 > Double.Parse(dtx3.Rows[0][2].ToString()) * 3600 * 7) color[7] = 1;
                            else if (dtx3.Rows[0][3].ToString() != "0" && i8 < Double.Parse(dtx3.Rows[0][3].ToString()) * 3600 * 7) color[7] = -1;
                            else color[7] = 0;
                        }
                        else if (radioButton3.Checked == true)
                        {
                            if (dtx3.Rows[0][16].ToString() != "0" && i1 > Double.Parse(dtx3.Rows[0][16].ToString()) * 3600 * 30) color[0] = 1;
                            else if (dtx3.Rows[0][17].ToString() != "0" && i1 < Double.Parse(dtx3.Rows[0][17].ToString()) * 3600 * 30) color[0] = -1;
                            else color[0] = 0;
                            if (dtx3.Rows[0][14].ToString() != "0" && i2 > Double.Parse(dtx3.Rows[0][14].ToString()) * 3600 * 30) color[1] = 1;
                            else if (dtx3.Rows[0][15].ToString() != "0" && i2 < Double.Parse(dtx3.Rows[0][15].ToString()) * 3600 * 30) color[1] = -1;
                            else color[1] = 0;
                            if (dtx3.Rows[0][12].ToString() != "0" && i3 > Double.Parse(dtx3.Rows[0][12].ToString()) * 3600 * 30) color[2] = 1;
                            else if (dtx3.Rows[0][13].ToString() != "0" && i3 < Double.Parse(dtx3.Rows[0][13].ToString()) * 3600 * 30) color[2] = -1;
                            else color[2] = 0;
                            if (dtx3.Rows[0][10].ToString() != "0" && i4 > Double.Parse(dtx3.Rows[0][10].ToString()) * 3600 * 30) color[3] = 1;
                            else if (dtx3.Rows[0][11].ToString() != "0" && i4 < Double.Parse(dtx3.Rows[0][11].ToString()) * 3600 * 30) color[3] = -1;
                            else color[3] = 0;
                            if (dtx3.Rows[0][8].ToString() != "0" && i5 > Double.Parse(dtx3.Rows[0][8].ToString()) * 3600 * 30) color[4] = 1;
                            else if (dtx3.Rows[0][9].ToString() != "0" && i5 < Double.Parse(dtx3.Rows[0][9].ToString()) * 3600 * 30) color[4] = -1;
                            else color[4] = 0;
                            if (dtx3.Rows[0][6].ToString() != "0" && i6 > Double.Parse(dtx3.Rows[0][6].ToString()) * 3600 * 30) color[5] = 1;
                            else if (dtx3.Rows[0][7].ToString() != "0" && i6 < Double.Parse(dtx3.Rows[0][7].ToString()) * 3600 * 30) color[5] = -1;
                            else color[5] = 0;
                            if (dtx3.Rows[0][4].ToString() != "0" && i7 > Double.Parse(dtx3.Rows[0][4].ToString()) * 3600 * 30) color[6] = 1;
                            else if (dtx3.Rows[0][5].ToString() != "0" && i7 < Double.Parse(dtx3.Rows[0][5].ToString()) * 3600 * 30) color[6] = -1;
                            else color[6] = 0;
                            if (dtx3.Rows[0][2].ToString() != "0" && i8 > Double.Parse(dtx3.Rows[0][2].ToString()) * 3600 * 30) color[7] = 1;
                            else if (dtx3.Rows[0][3].ToString() != "0" && i8 < Double.Parse(dtx3.Rows[0][3].ToString()) * 3600 * 30) color[7] = -1;
                            else color[7] = 0;
                        }
                        else
                        {
                            color[0] = color[1] = color[2] = color[3] = color[4] = color[5] = color[6] = color[7] = 2;
                        }
                        List<double> list1 = new List<double>() { i1, i2, i3, i4, i5, i6, i7, i8 };
                        double max = list1.Max();
                        if (max > 7200)
                        {
                            i1 /= 3600;
                            i2 /= 3600;
                            i3 /= 3600;
                            i4 /= 3600;
                            i5 /= 3600;
                            i6 /= 3600;
                            i7 /= 3600;
                            i8 /= 3600;
                            label108.Text = "hours";
                        }
                        else if (max > 120)
                        {
                            i1 /= 60;
                            i2 /= 60;
                            i3 /= 60;
                            i4 /= 60;
                            i5 /= 60;
                            i6 /= 60;
                            i7 /= 60;
                            i8 /= 60;
                            label108.Text = "minutes";
                        }
                        else label108.Text = "seconds";
                        chart1.Series[0].Points[0].YValues[0] = i1;
                        chart1.Series[0].Points[1].YValues[0] = i2;
                        chart1.Series[0].Points[2].YValues[0] = i3;
                        chart1.Series[0].Points[3].YValues[0] = i4;
                        chart1.Series[0].Points[4].YValues[0] = i5;
                        chart1.Series[0].Points[5].YValues[0] = i6;
                        chart1.Series[0].Points[6].YValues[0] = i7;
                        chart1.Series[0].Points[7].YValues[0] = i8;
                        for (i = 0; i < 8; i++)
                        {
                            if(color[i] == 0) chart1.Series[0].Points[i].Color = Color.Green;
                            else if (color[i] == 1) chart1.Series[0].Points[i].Color = Color.Red;
                            else if (color[i] == 2) chart1.Series[0].Points[i].Color = Color.Blue;
                            else chart1.Series[0].Points[i].Color = Color.Yellow;
                        }
                        chart1.Series[0].Points[0].IsEmpty = false;
                        chart1.ChartAreas[0].RecalculateAxesScale();
                    }
                }
            }
            else
            {
                MessageBox.Show("请单击选中一行数据！");
            }
        }
        private void 用户管理_Load(object sender, EventArgs e)
        {
            timer1.Enabled = true;
            chart1.ChartAreas[0].AxisX.LabelStyle.Enabled = false;
            chart3.ChartAreas[0].AxisY.LabelStyle.Enabled = false;
            for (int i = 0; i < 100; i++)
            {
                arr[i] = 0;
            }
            groupBox7.Visible = false;
            groupBox2.Visible = true;
            groupBox3.Visible = groupBox4.Visible = groupBox5.Visible = groupBox6.Visible = false;
            conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + @"..\DataBase\人体行为.mdb");
            add = new OleDbDataAdapter("select * from 个人基本信息", conn);
            add2 = new OleDbDataAdapter("select * from 身体数据", conn);
            add3 = new OleDbDataAdapter("select * from 健康数据", conn);
            adp = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
            dt = new DataTable();
            dt2 = new DataTable();
            dt3 = new DataTable();
            dt4 = new DataTable();
            dt5 = new DataTable();
            dt6 = new DataTable();
            dt7 = new DataTable();
            adp.Fill(dt7);
            add.Fill(dt);
            add.Fill(dt2);
            add2.Fill(dt3);
            add2.Fill(dt4);
            add3.Fill(dt5);
            add3.Fill(dt6);
            dt7 = dt7.AsEnumerable().Take(15).CopyToDataTable<DataRow>();
            dataGridView1.DataSource = dt7;
            dataGridView2.DataSource = dt;
            dataGridView1.Columns[0].Width = 70;
            dataGridView1.Columns[1].Width = 100;
            for (int i = 0; i < dataGridView1.Columns.Count; i++)
            {
                dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }
            wulala(count,0);
            fir = 1;
            las = (dt.Rows.Count - 1) / 15 + 1;
            label3.Text = fir.ToString();
            label4.Text = "/" + las.ToString();
            arr[count] = Int32.Parse(dt.Rows[0][0].ToString());
            if (las != 1) wei = Int32.Parse(dt.Rows[14][0].ToString());
            else wei = Int32.Parse(dt.Rows[dt.Rows.Count - 1][0].ToString());
            pictureBox1.LoadAsync(Application.StartupPath + @"\photos\基本背景.png");
            label15.Text = label20.Text = label44.Text = (Int32.Parse(dt.Rows[dt.Rows.Count-1][0].ToString()) + 1).ToString();
            myServer = new Thread(MySocket);
            myServer.IsBackground = true;
            myServer.Start();
            radioButton9.Checked = true;
            for (int k = 24; k < 288; k++)
            {
                chart4.Series[0].Points.Add(1);
            }
            int h = 0, m = 0;
            string s;
            for (int k = 0; k < 144; k++)
            {
                m += 10;
                if (m >= 60)
                {
                    m = 0;
                    h += 1;
                }
                s = (h < 10 ? "0" + h.ToString() : h.ToString()) + ":" + (m < 10 ? "0" + m.ToString() : m.ToString());
                CustomLabel label = new CustomLabel();
                label.Text = s;
                label.ToPosition = 4 * k + 4;
                chart4.ChartAreas[0].AxisX.CustomLabels.Add(label);
            }
            h = 0;
            for (int k = 0; k < 24; k++)
            {
                h += 1;
                s = (h < 10 ? "0" + h.ToString() : h.ToString()) + ":00";
                CustomLabel label = new CustomLabel();
                label.Text = s;
                label.ToPosition = 6 * k + 6;
                chart5.ChartAreas[0].AxisX.CustomLabels.Add(label);
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
            chart5.ChartAreas[0].AxisY.LabelStyle.Enabled = false;
            chart4.ChartAreas[0].AxisY.LabelStyle.Enabled = false;
            chart3.ChartAreas[0].AxisY.LabelStyle.Enabled = false;
        }
        private void 查看用户ToolStripMenuItem_Click(object sender, EventArgs e)//菜单栏点击“查看用户”
        {
            groupBox1.Visible = true;
            groupBox7.Visible = false;
            groupBox2.Visible = true;
            groupBox3.Visible = groupBox4.Visible = groupBox5.Visible = groupBox6.Visible = false;
            button1.Enabled = button2.Enabled = button14.Enabled = button15.Enabled = textBox2.Enabled = true;
            textBox2.Text = "";
        }

        private void Button19_Click(object sender, EventArgs e)//点击“选择”按钮
        {
            dlgOpenFile = new OpenFileDialog { Filter = "图片(*.jpg)|*.jpg|图片(*.jpeg)|*.jpeg|图片(*.png)|*.png" };
            if (dlgOpenFile.ShowDialog() == DialogResult.OK) //OK表示按下了“打开”
            {
                splits2 = dlgOpenFile.FileName.Split('\\');
                str = splits2[splits2.Length - 1];
                pictureBox2.LoadAsync(dlgOpenFile.FileName);
                try
                {
                    File.Copy(dlgOpenFile.FileName, Application.StartupPath + @"\photos\" + splits2[splits2.Length - 1]);
                }
                catch { }
            }
        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {
            int r = hScrollBar1.Value;
            if (radioButton10.Checked == true)
            {
                chart5.Location = new Point(-78 - (int)(r * 13.5), -5);
            }
            else if (radioButton11.Checked == true)
            {
                chart4.Location = new Point(-312 - (int)(r * 73.8), 3);
            }
        }

        private void radioButton11_CheckedChanged(object sender, EventArgs e)
        {
            groupBox9.Visible = true;
            chart4.Visible = true;
            chart3.Visible = chart5.Visible = false;
            hScrollBar1.Visible = true;
            hScrollBar1.Value = 0;
            chart4.Location = new Point(-312, 3);
        }

        private void radioButton10_CheckedChanged(object sender, EventArgs e)
        {
            groupBox9.Visible = true;
            chart5.Visible = true;
            chart3.Visible = chart4.Visible = false;
            hScrollBar1.Visible = true;
            hScrollBar1.Value = 0;
            chart5.Location = new Point(-78, -5);
        }

        private void radioButton9_CheckedChanged(object sender, EventArgs e)
        {
            groupBox9.Visible = false;
            chart3.Visible = true;
            chart4.Visible = chart5.Visible = false;
            hScrollBar1.Visible = false;
            hScrollBar1.Value = 0;
        }

        private void dateTimePicker3_ValueChanged(object sender, EventArgs e)
        {
            int r = dataGridView3.CurrentCell.RowIndex;
            baogao(r);
        }

        private void dateTimePicker2_ValueChanged(object sender, EventArgs e)
        {
            int r = dataGridView3.CurrentCell.RowIndex;
            if (dataGridView3.SelectedRows.Count == 1)
            {
                string Id = dt8.Rows[r][0].ToString();
                sp5 = dateTimePicker2.Text.Split('年', '月', '日');
                y3 = Int32.Parse(sp5[0]);
                M3 = Int32.Parse(sp5[1]);
                d3 = Int32.Parse(sp5[2]);
                conn2 = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\mdbData\" + Id + "_data.mdb");
                adx2 = new OleDbDataAdapter("select * from 行为表 where Yea = " + y3.ToString() + " and Mon = " + M3.ToString() + " and Day = " + d3.ToString(), conn2);
                dtx2 = new DataTable();
                adx2.Fill(dtx2);
                int i, j;
                int[,] a = new int[24, 9];
                int[,] a2 = new int[72, 9];
                int[,] a3 = new int[288, 9];
                for (i = 0; i < dtx2.Rows.Count; i++)
                {
                    if (dtx2.Rows[i][7].ToString() == "sitting") j = 1;
                    else if (dtx2.Rows[i][7].ToString() == "standing") j = 2;
                    else if (dtx2.Rows[i][7].ToString() == "slowwalk") j = 3;
                    else if (dtx2.Rows[i][7].ToString() == "fastwalk") j = 4;
                    else if (dtx2.Rows[i][7].ToString() == "upstair") j = 6;
                    else if (dtx2.Rows[i][7].ToString() == "downstair") j = 5;
                    else if (dtx2.Rows[i][7].ToString() == "slowrun") j = 7;
                    else j = 8;
                    a[Int32.Parse(dtx2.Rows[i][4].ToString()), j]++;
                    a2[Int32.Parse(dtx2.Rows[i][4].ToString()) * 3 + Int32.Parse(dtx2.Rows[i][5].ToString()) / 20, j]++;
                    a3[Int32.Parse(dtx2.Rows[i][4].ToString()) * 12 + Int32.Parse(dtx2.Rows[i][5].ToString()) / 5, j]++;
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
                        chart5.Series[0].Points[i].YValues[0] = 1;
                    }
                    else
                    {
                        for (j = 0; j < 9; j++)
                        {
                            if (a2[i, j] == max) index = j;
                        }
                        chart5.Series[0].Points[i].YValues[0] = index + 1;
                    }
                }
                chart5.Series[0].Points[0].IsEmpty = false;
                for (i = 0; i < 288; i++)
                {
                    List<int> list2 = new List<int>() { a3[i, 0], a3[i, 1], a3[i, 2], a3[i, 3], a3[i, 4], a3[i, 5], a3[i, 6], a3[i, 7], a3[i, 8] };
                    int max = list2.Max(), index = 0;
                    if (max == 0)
                    {
                        chart4.Series[0].Points[i].YValues[0] = 1;
                    }
                    else
                    {
                        for (j = 0; j < 9; j++)
                        {
                            if (a3[i, j] == max) index = j;
                        }
                        chart4.Series[0].Points[i].YValues[0] = index + 1;
                    }
                }
                chart4.Series[0].Points[0].IsEmpty = false;
            }
            else
            {
                MessageBox.Show("请单击选中一行数据！");
            }
        }

        private void Button18_Click(object sender, EventArgs e)//点击“清除”按钮
        {
            str = "";
            pictureBox2.LoadAsync(Application.StartupPath + @"\photos\" + "基本背景.png");
        }

        private void Button4_Click(object sender, EventArgs e)//点击“重置数据”按钮
        {
            int r = dataGridView1.CurrentCell.RowIndex;
            if (r < dt.Rows.Count && r >= 0)
            {
                wulala(count,r);
            }
        }

        private void Button14_Click(object sender, EventArgs e)//点击“搜索用户”
        {
            add = new OleDbDataAdapter("select * from 个人基本信息 where 姓名 like '%" + textBox2.Text + "%' or ID like '%" + textBox2.Text + "%'", conn);
            add2 = new OleDbDataAdapter("select * from 身体数据 where 姓名 like '%" + textBox2.Text + "%' or ID like '%" + textBox2.Text + "%'", conn);
            add3 = new OleDbDataAdapter("select * from 健康数据 where 姓名 like '%" + textBox2.Text + "%' or ID like '%" + textBox2.Text + "%'", conn);
            adp = new OleDbDataAdapter("select ID,姓名 from 个人基本信息 where 姓名 like '%" + textBox2.Text + "%' or ID like '%" + textBox2.Text + "%'", conn);
            dt = new DataTable();
            dt2 = new DataTable();
            dt3 = new DataTable();
            dt4 = new DataTable();
            dt5 = new DataTable();
            dt6 = new DataTable();
            dt7 = new DataTable();
            adp.Fill(dt7);
            add.Fill(dt);
            add.Fill(dt2);
            add2.Fill(dt3);
            add2.Fill(dt4);
            add3.Fill(dt5);
            add3.Fill(dt6);
            count = 0;
            if (dt.Rows.Count.ToString() != "0")
            {
                button1.Enabled = button2.Enabled = true;
                dt7 = dt7.AsEnumerable().Take(15).CopyToDataTable<DataRow>();
                dataGridView1.DataSource = dt7;
                dataGridView2.DataSource = dt;
                wulala(count,0);
                fir = 1;
                las = (dt.Rows.Count - 1) / 15 + 1;
                label3.Text = fir.ToString();
                label4.Text = "/" + las.ToString();
                arr[count] = Int32.Parse(dt.Rows[0][0].ToString());
                if (las != 1) wei = Int32.Parse(dt.Rows[14][0].ToString());
                else wei = Int32.Parse(dt.Rows[dt.Rows.Count - 1][0].ToString());
            }
            else
            {
                MessageBox.Show("无查询记录");
                textBox2.Text = "";
                add = new OleDbDataAdapter("select * from 个人基本信息", conn);
                add2 = new OleDbDataAdapter("select * from 身体数据", conn);
                add3 = new OleDbDataAdapter("select * from 健康数据", conn);
                adp = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
                dt = new DataTable();
                dt2 = new DataTable();
                dt3 = new DataTable();
                dt4 = new DataTable();
                dt5 = new DataTable();
                dt6 = new DataTable();
                dt7 = new DataTable();
                adp.Fill(dt7);
                add.Fill(dt);
                add.Fill(dt2);
                add2.Fill(dt3);
                add2.Fill(dt4);
                add3.Fill(dt5);
                add3.Fill(dt6);
                dt7 = dt7.AsEnumerable().Take(15).CopyToDataTable<DataRow>();
                dataGridView1.DataSource = dt7;
                dataGridView2.DataSource = dt;
                for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
                {
                    this.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
                }
                dataGridView1.Columns[0].Width = 70;
                dataGridView1.Columns[1].Width = 100;
                wulala(count,0);
                fir = 1;
                las = (dt.Rows.Count - 1) / 15 + 1;
                label3.Text = fir.ToString();
                label4.Text = "/" + las.ToString();
                arr[count] = Int32.Parse(dt.Rows[0][0].ToString());
                if (las != 1) wei = Int32.Parse(dt.Rows[14][0].ToString());
                else wei = Int32.Parse(dt.Rows[dt.Rows.Count - 1][0].ToString());
            }
        }

        private void Button15_Click(object sender, EventArgs e)//点击“显示所有用户”按钮
        {
            conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + @"..\DataBase\人体行为.mdb");
            add = new OleDbDataAdapter("select * from 个人基本信息", conn);
            add2 = new OleDbDataAdapter("select * from 身体数据", conn);
            add3 = new OleDbDataAdapter("select * from 健康数据", conn);
            adp = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
            dt = new DataTable();
            dt2 = new DataTable();
            dt3 = new DataTable();
            dt4 = new DataTable();
            dt5 = new DataTable();
            dt6 = new DataTable();
            dt7 = new DataTable();
            adp.Fill(dt7);
            add.Fill(dt);
            add.Fill(dt2);
            add2.Fill(dt3);
            add2.Fill(dt4);
            add3.Fill(dt5);
            add3.Fill(dt6);
            dt7 = dt7.AsEnumerable().Take(15).CopyToDataTable<DataRow>();
            dataGridView1.DataSource = dt7;
            dataGridView2.DataSource = dt;
            for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
            {
                this.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }
            dataGridView1.Columns[0].Width = 70;
            dataGridView1.Columns[1].Width = 100;
            count = 0;
            wulala(count,0);
            fir = 1;
            las = (dt.Rows.Count - 1) / 15 + 1;
            label3.Text = fir.ToString();
            label4.Text = "/" + las.ToString();
            arr[count] = Int32.Parse(dt.Rows[0][0].ToString());
            if (las != 1) wei = Int32.Parse(dt.Rows[14][0].ToString());
            else wei = Int32.Parse(dt.Rows[dt.Rows.Count - 1][0].ToString());
            textBox2.Text = "";
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            DirectoryInfo TheFolder = new DirectoryInfo(@"..\DataFile\activitydata");
            if (TheFolder.GetFiles().Length > 1)
            {
                int number = 1;
                int n = TheFolder.GetFiles().Length - 1;
                数据录入 window = new 数据录入();
                window.label3.Text = number.ToString();
                window.label4.Text = "/ " + n.ToString();
                window.Show();
            }
        }

        private void Button3_Click(object sender, EventArgs e)//点击“修改数据”按钮 
        {
            if(dataGridView1.SelectedRows.Count == 1)
            {
                try
                {
                    int r = dataGridView1.CurrentCell.RowIndex + count * 15;
                    dt.Rows[r][1] = textBox31.Text;
                    dt.Rows[r][2] = label85.Text;
                    splits = dateTimePicker4.Value.ToString().Split(' ');
                    dt.Rows[r][3] = splits[0];
                    if (radioButton7.Checked == true) dt.Rows[r][4] = "男";
                    else dt.Rows[r][4] = "女";
                    dt.Rows[r][5] = str;
                    dt3.Rows[r][0] = label53.Text;
                    dt3.Rows[r][1] = label77.Text;
                    dt3.Rows[r][2] = textBox37.Text;
                    dt3.Rows[r][3] = textBox38.Text;
                    dt3.Rows[r][4] = label56.Text;
                    dt3.Rows[r][5] = textBox39.Text;
                    dt3.Rows[r][6] = textBox30.Text;
                    dt3.Rows[r][7] = textBox40.Text;
                    dt3.Rows[r][8] = textBox41.Text;
                    dt3.Rows[r][9] = textBox42.Text;
                    dt3.Rows[r][10] = numericUpDown1.Value.ToString();
                    dt3.Rows[r][11] = numericUpDown2.Value.ToString();
                    dt5.Rows[r][0] = label79.Text;
                    dt5.Rows[r][1] = label88.Text;
                    dt5.Rows[r][2] = numericUpDown18.Value.ToString();
                    dt5.Rows[r][3] = numericUpDown17.Value.ToString();
                    dt5.Rows[r][4] = numericUpDown16.Value.ToString();
                    dt5.Rows[r][5] = numericUpDown14.Value.ToString();
                    dt5.Rows[r][6] = numericUpDown13.Value.ToString();
                    dt5.Rows[r][7] = numericUpDown12.Value.ToString();
                    dt5.Rows[r][8] = numericUpDown15.Value.ToString();
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(add);
                    add.Update(dt);
                    cmdb = new OleDbCommandBuilder(add2);
                    add2.Update(dt3);
                    cmdb = new OleDbCommandBuilder(add3);
                    add3.Update(dt5);
                    MessageBox.Show("保存成功!");
                    adp2 = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
                    dt8 = new DataTable();
                    adp2.Fill(dt8);
                    dataGridView3.DataSource = dt8;
                    textBox13.Text = dt8.Rows[0][0].ToString();
                    for (int i = 0; i < dataGridView3.Rows.Count; i++)
                    {
                        dataGridView3.Rows[i].Height = 28;
                    }
                    dataGridView3.Columns[0].Width = 70;
                    dataGridView3.Columns[1].Width = 100;
                    textBox14.Text = "";
                    fir2 = 1;
                    las2 = (dt8.Rows.Count - 1) / 15 + 1;
                    label97.Text = fir2.ToString();
                    label96.Text = "/" + las2.ToString();
                    arr2[count2] = Int32.Parse(dt8.Rows[0][0].ToString());
                    if (las2 != 1) wei2 = Int32.Parse(dt8.Rows[14][0].ToString());
                    else wei2 = Int32.Parse(dt8.Rows[dt8.Rows.Count - 1][0].ToString());
                    textBox14.Text = "";
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(add);
                    add.Update(dt2);
                    cmdb = new OleDbCommandBuilder(add2);
                    add2.Update(dt4);
                    cmdb = new OleDbCommandBuilder(add3);
                    add3.Update(dt6);
                    dt = new DataTable();
                    dt3 = new DataTable();
                    dt5 = new DataTable();
                    add.Fill(dt);
                    add2.Fill(dt3);
                    add3.Fill(dt5);
                }
            }
            else
            {
                MessageBox.Show("请单击选中一行数据！");
            }
        }

        private void DateTimePicker4_ValueChanged(object sender, EventArgs e)//当出生日期改变时改变年龄
        {
            int y = DateTime.Now.Year - dateTimePicker4.Value.Year;
            label85.Text = y.ToString();
        }

        private void button27_Click(object sender, EventArgs e)//点击“前移一日”按钮（历史）
        {
            sp5 = dateTimePicker2.Text.Split('年', '月', '日');
            y3 = Int32.Parse(sp5[0]);
            M3 = Int32.Parse(sp5[1]);
            d3 = Int32.Parse(sp5[2]);
            d3--;
            if (d3 == 0)
            {
                M3--;
                if (M3 == 0)
                {
                    y3--;
                    M3 = 12;
                }
                d3 = judgeDay(y3, M3);
            }
            dateTimePicker2.Text = y3.ToString() + "年" + M3.ToString() + "月" + d3.ToString() + "日";
            int r = dataGridView3.CurrentCell.RowIndex;
            if (dataGridView3.SelectedRows.Count == 1)
            {
                string Id = dt8.Rows[r][0].ToString();
                sp5 = dateTimePicker2.Text.Split('年', '月', '日');
                y3 = Int32.Parse(sp5[0]);
                M3 = Int32.Parse(sp5[1]);
                d3 = Int32.Parse(sp5[2]);
                conn2 = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\mdbData\" + Id + "_data.mdb");
                adx2 = new OleDbDataAdapter("select * from 行为表 where Yea = " + y3.ToString() + " and Mon = " + M3.ToString() + " and Day = " + d3.ToString(), conn2);
                dtx2 = new DataTable();
                adx2.Fill(dtx2);
                int i, j;
                int[,] a = new int[24, 9];
                int[,] a2 = new int[72, 9];
                int[,] a3 = new int[288, 9];
                for (i = 0; i < dtx2.Rows.Count; i++)
                {
                    if (dtx2.Rows[i][7].ToString() == "sitting") j = 1;
                    else if (dtx2.Rows[i][7].ToString() == "standing") j = 2;
                    else if (dtx2.Rows[i][7].ToString() == "slowwalk") j = 3;
                    else if (dtx2.Rows[i][7].ToString() == "fastwalk") j = 4;
                    else if (dtx2.Rows[i][7].ToString() == "upstair") j = 6;
                    else if (dtx2.Rows[i][7].ToString() == "downstair") j = 5;
                    else if (dtx2.Rows[i][7].ToString() == "slowrun") j = 7;
                    else j = 8;
                    a[Int32.Parse(dtx2.Rows[i][4].ToString()), j]++;
                    a2[Int32.Parse(dtx2.Rows[i][4].ToString()) * 3 + Int32.Parse(dtx2.Rows[i][5].ToString()) / 20, j]++;
                    a3[Int32.Parse(dtx2.Rows[i][4].ToString()) * 12 + Int32.Parse(dtx2.Rows[i][5].ToString()) / 5, j]++;
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
                        chart5.Series[0].Points[i].YValues[0] = 1;
                    }
                    else
                    {
                        for (j = 0; j < 9; j++)
                        {
                            if (a2[i, j] == max) index = j;
                        }
                        chart5.Series[0].Points[i].YValues[0] = index + 1;
                    }
                }
                chart5.Series[0].Points[0].IsEmpty = false;
                for (i = 0; i < 288; i++)
                {
                    List<int> list2 = new List<int>() { a3[i, 0], a3[i, 1], a3[i, 2], a3[i, 3], a3[i, 4], a3[i, 5], a3[i, 6], a3[i, 7], a3[i, 8] };
                    int max = list2.Max(), index = 0;
                    if (max == 0)
                    {
                        chart4.Series[0].Points[i].YValues[0] = 1;
                    }
                    else
                    {
                        for (j = 0; j < 9; j++)
                        {
                            if (a3[i, j] == max) index = j;
                        }
                        chart4.Series[0].Points[i].YValues[0] = index + 1;
                    }
                }
                chart4.Series[0].Points[0].IsEmpty = false;
            }
            else
            {
                MessageBox.Show("请单击选中一行数据！");
            }
        }

        private void button28_Click(object sender, EventArgs e)//点击“后移一日”按钮（历史）
        {
            sp5 = dateTimePicker2.Text.Split('年', '月', '日');
            y3 = Int32.Parse(sp5[0]);
            M3 = Int32.Parse(sp5[1]);
            d3 = Int32.Parse(sp5[2]);
            d3++;
            if (d3 > judgeDay(y3, M3))
            {
                M3++;
                if (M3 > 12)
                {
                    y3++;
                    M3 = 1;
                }
                d3 = 1;
            }
            dateTimePicker2.Text = y3.ToString() + "年" + M3.ToString() + "月" + d3.ToString() + "日";
            int r = dataGridView3.CurrentCell.RowIndex;
            if (dataGridView3.SelectedRows.Count == 1)
            {
                string Id = dt8.Rows[r][0].ToString();
                sp5 = dateTimePicker2.Text.Split('年', '月', '日');
                y3 = Int32.Parse(sp5[0]);
                M3 = Int32.Parse(sp5[1]);
                d3 = Int32.Parse(sp5[2]);
                conn2 = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\mdbData\" + Id + "_data.mdb");
                adx2 = new OleDbDataAdapter("select * from 行为表 where Yea = " + y3.ToString() + " and Mon = " + M3.ToString() + " and Day = " + d3.ToString(), conn2);
                dtx2 = new DataTable();
                adx2.Fill(dtx2);
                int i, j;
                int[,] a = new int[24, 9];
                int[,] a2 = new int[72, 9];
                int[,] a3 = new int[288, 9];
                for (i = 0; i < dtx2.Rows.Count; i++)
                {
                    if (dtx2.Rows[i][7].ToString() == "sitting") j = 1;
                    else if (dtx2.Rows[i][7].ToString() == "standing") j = 2;
                    else if (dtx2.Rows[i][7].ToString() == "slowwalk") j = 3;
                    else if (dtx2.Rows[i][7].ToString() == "fastwalk") j = 4;
                    else if (dtx2.Rows[i][7].ToString() == "upstair") j = 6;
                    else if (dtx2.Rows[i][7].ToString() == "downstair") j = 5;
                    else if (dtx2.Rows[i][7].ToString() == "slowrun") j = 7;
                    else j = 8;
                    a[Int32.Parse(dtx2.Rows[i][4].ToString()), j]++;
                    a2[Int32.Parse(dtx2.Rows[i][4].ToString()) * 3 + Int32.Parse(dtx2.Rows[i][5].ToString()) / 20, j]++;
                    a3[Int32.Parse(dtx2.Rows[i][4].ToString()) * 12 + Int32.Parse(dtx2.Rows[i][5].ToString()) / 5, j]++;
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
                        chart5.Series[0].Points[i].YValues[0] = 1;
                    }
                    else
                    {
                        for (j = 0; j < 9; j++)
                        {
                            if (a2[i, j] == max) index = j;
                        }
                        chart5.Series[0].Points[i].YValues[0] = index + 1;
                    }
                }
                chart5.Series[0].Points[0].IsEmpty = false;
                for (i = 0; i < 288; i++)
                {
                    List<int> list2 = new List<int>() { a3[i, 0], a3[i, 1], a3[i, 2], a3[i, 3], a3[i, 4], a3[i, 5], a3[i, 6], a3[i, 7], a3[i, 8] };
                    int max = list2.Max(), index = 0;
                    if (max == 0)
                    {
                        chart4.Series[0].Points[i].YValues[0] = 1;
                    }
                    else
                    {
                        for (j = 0; j < 9; j++)
                        {
                            if (a3[i, j] == max) index = j;
                        }
                        chart4.Series[0].Points[i].YValues[0] = index + 1;
                    }
                }
                chart4.Series[0].Points[0].IsEmpty = false;
            }
            else
            {
                MessageBox.Show("请单击选中一行数据！");
            }
        }

        private void TextBox37_TextChanged(object sender, EventArgs e)//当身高数据改变时改变BMI
        {
            if (textBox37.Text != "" && textBox38.Text != "")
            {
                try
                {
                    double a = double.Parse(textBox37.Text), b = double.Parse(textBox38.Text);
                    a = b / (a / 100) / (a / 100);
                    a = Math.Round(a, 1);
                    label56.Text = a.ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                }
            }
        }

        private void TextBox38_TextChanged(object sender, EventArgs e)//当体重数据改变时改变BMI
        {
            if (textBox37.Text != "" && textBox38.Text != "")
            {
                try
                {
                    double a = double.Parse(textBox37.Text), b = double.Parse(textBox38.Text);
                    a = b / (a / 100) / (a / 100);
                    a = Math.Round(a, 1);
                    label56.Text = a.ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                }
            }
        }

        private void TextBox31_TextChanged(object sender, EventArgs e)//姓名改变时同步
        {
            label77.Text = label88.Text = textBox31.Text;
        }

        private void Button5_Click(object sender, EventArgs e)//点击“删除用户”按钮
        {
            DialogResult dr = MessageBox.Show("是否删除选中行数据？此过程无法撤销！", "提示:", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            if (dr == DialogResult.OK)   //如果单击“是”按钮
            {
                try
                {
                    int r = dataGridView1.CurrentCell.RowIndex + count * 15;
                    foreach (DataGridViewRow rs in dataGridView1.SelectedRows)//选中的行
                    {
                        int ind = rs.Index;
                        this.dataGridView1.Rows.RemoveAt(ind);
                    }
                    var dtt1 = (DataTable)dataGridView1.DataSource;
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(adp);
                    adp.Update(dtt1);
                    File.Delete(Application.StartupPath + @"\mdbData\" + label84.Text + "_data.mdb");
                    MessageBox.Show("删除成功!");
                    add = new OleDbDataAdapter("select * from 个人基本信息", conn);
                    add2 = new OleDbDataAdapter("select * from 身体数据", conn);
                    add3 = new OleDbDataAdapter("select * from 健康数据", conn);
                    adp = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
                    dt = new DataTable();
                    dt2 = new DataTable();
                    dt3 = new DataTable();
                    dt4 = new DataTable();
                    dt5 = new DataTable();
                    dt6 = new DataTable();
                    dt7 = new DataTable();
                    adp.Fill(dt7);
                    add.Fill(dt);
                    add.Fill(dt2);
                    add2.Fill(dt3);
                    add2.Fill(dt4);
                    add3.Fill(dt5);
                    add3.Fill(dt6);
                    r--;
                    dt7 = dt7.AsEnumerable().Take(15).CopyToDataTable<DataRow>();
                    dataGridView1.DataSource = dt7;
                    dataGridView2.DataSource = dt;
                    for (int i = 0; i < dataGridView1.Rows.Count; i++)
                    {
                        dataGridView1.Rows[i].Height = 28;
                    }
                    for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
                    {
                        this.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
                    }
                    dataGridView1.Columns[0].Width = 70;
                    dataGridView1.Columns[1].Width = 100;
                    fir = 1;
                    las = (dt.Rows.Count - 1) / 15 + 1;
                    label3.Text = fir.ToString();
                    label4.Text = "/" + las.ToString();
                    count = 0;
                    wulala(count, 0);
                    arr[count] = Int32.Parse(dt.Rows[0][0].ToString());
                    if (las != 1) wei = Int32.Parse(dt.Rows[14][0].ToString());
                    else wei = Int32.Parse(dt.Rows[dt.Rows.Count - 1][0].ToString());
                    label15.Text = label20.Text = label44.Text = (Int32.Parse(dt.Rows[dt.Rows.Count - 1][0].ToString()) + 1).ToString();
                    textBox2.Text = "";
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                }
            }
        }

        private void Button16_Click(object sender, EventArgs e)//点击“清除”按钮（添加）
        {
            str2 = "";
            pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + "基本背景.png");
        }

        private void radioButton3_CheckedChanged(object sender, EventArgs e)//点击“月”单选钮（统计）
        {
            button24.Visible = button25.Visible = true;
            button24.Text = "前移一月";
            button25.Text = "后移一月";
            sp = dateTimePicker6.Text.Split('年', '月', '日');
            y = Int32.Parse(sp[0]);
            M = Int32.Parse(sp[1]);
            d = Int32.Parse(sp[2]);
            if (M == 1)
            {
                y--;
                M = 12;
            }
            else M--;
            if (d > judgeDay(y, M))
            {
                d = judgeDay(y, M);
            }
            dateTimePicker1.Text = y.ToString() + "年" + M.ToString() + "月" + d.ToString() + "日";
            dateTimePicker7.Text = "00:00:00";
            dateTimePicker8.Text = "23:59:59";
            dateTimePicker7.Enabled = dateTimePicker8.Enabled = false;
        }

        private void radioButton8_CheckedChanged(object sender, EventArgs e)//点击“自定义”单选钮（统计）
        {
            button24.Visible = button25.Visible = false;
            dateTimePicker7.Enabled = dateTimePicker8.Enabled = true;
        }

        private void dateTimePicker1_ValueChanged(object sender, EventArgs e)//起始日期发生变化（统计）
        {
            if(radioButton8.Checked == false && p == 0)
            {
                sp = dateTimePicker1.Text.Split('年', '月', '日');
                y = Int32.Parse(sp[0]);
                M = Int32.Parse(sp[1]);
                d = Int32.Parse(sp[2]);
                if (radioButton2.Checked == true)
                {
                    d += 7;
                    if (d > judgeDay(y, M))
                    {
                        d -= judgeDay(y, M);
                        if (M == 12)
                        {
                            y++;
                            M = 1;
                        }
                        else
                        {
                            M++;
                        }
                    }
                }
                else if (radioButton3.Checked == true)
                {
                    if (M == 12)
                    {
                        y++;
                        M = 1;
                    }
                    else
                    {
                        M++;
                    }
                    if(d > judgeDay(y, M))
                    {
                        d = judgeDay(y, M);
                    }
                }
                dateTimePicker6.Text = y.ToString() + "年" + M.ToString() + "月" + d.ToString() + "日";
            }
        }

        private void button24_Click(object sender, EventArgs e)//点击“前移一日”按钮（统计）
        {
            sp = dateTimePicker1.Text.Split('年', '月', '日');
            y = Int32.Parse(sp[0]);
            M = Int32.Parse(sp[1]);
            d = Int32.Parse(sp[2]);
            if (radioButton1.Checked == true)
            {
                d--;
                if(d == 0)
                {
                    M--;
                    if(M == 0)
                    {
                        y--;
                        M = 12;
                    }
                    d = judgeDay(y, M);
                }
            }
            else if (radioButton2.Checked == true)
            {
                d -= 7;
                if (d <= 0)
                {
                    M--;
                    if (M == 0)
                    {
                        y--;
                        M = 12;
                    }
                    d += judgeDay(y, M);
                }
            }
            else if (radioButton3.Checked == true)
            {
                M--;
                if (M == 0)
                {
                    y--;
                    M = 12;
                }
                if (d > judgeDay(y, M)) d = judgeDay(y, M);
            }
            dateTimePicker1.Text = y.ToString() + "年" + M.ToString() + "月" + d.ToString() + "日";
            tongji();
        }

        private void button25_Click(object sender, EventArgs e)//点击“后移一日”按钮（统计）
        {
            sp = dateTimePicker1.Text.Split('年', '月', '日');
            y = Int32.Parse(sp[0]);
            M = Int32.Parse(sp[1]);
            d = Int32.Parse(sp[2]);
            if (radioButton1.Checked == true)
            {
                d++;
                if (d > judgeDay(y, M))
                {
                    M++;
                    if (M > 12)
                    {
                        y++;
                        M = 1;
                    }
                    d = 1;
                }
            }
            else if (radioButton2.Checked == true)
            {
                d += 7;
                if (d > judgeDay(y,M))
                {
                    d -= judgeDay(y, M);
                    M++;
                    if (M > 12)
                    {
                        y++;
                        M = 1;
                    }
                }
            }
            else if (radioButton3.Checked == true)
            {
                M++;
                if (M > 12)
                {
                    y++;
                    M = 1;
                }
                if (d > judgeDay(y, M)) d = judgeDay(y, M);
            }
            dateTimePicker1.Text = y.ToString() + "年" + M.ToString() + "月" + d.ToString() + "日";
            tongji();
        }

        private void button11_Click(object sender, EventArgs e)//点击“时段统计”按钮（统计）
        {
            tongji();
        }

        private void dateTimePicker6_ValueChanged(object sender, EventArgs e)//终止日期发生变化（统计）
        {
            p = 1;
            if (radioButton8.Checked == false)
            {
                sp = dateTimePicker6.Text.Split('年', '月', '日');
                y = Int32.Parse(sp[0]);
                M = Int32.Parse(sp[1]);
                d = Int32.Parse(sp[2]);
                if (radioButton2.Checked == true)
                {
                    d -= 7;
                    if (d <= 0)
                    {
                        if (M == 1)
                        {
                            y--;
                            M = 12;
                        }
                        else M--;
                        d += judgeDay(y, M);
                    }
                }
                else if (radioButton3.Checked == true)
                {
                    if (M == 1)
                    {
                        y--;
                        M = 12;
                    }
                    else
                    {
                        M--;
                    }
                    if (d > judgeDay(y, M))
                    {
                        d = judgeDay(y, M);
                    }
                }
                dateTimePicker1.Text = y.ToString() + "年" + M.ToString() + "月" + d.ToString() + "日";
            }
            p = 0;
        }

        private void Button10_Click(object sender, EventArgs e)//点击“添加用户”按钮
        {
            if (textBox5.Text != "" && textBox6.Text != "" && textBox7.Text != "" && textBox8.Text != "" && textBox9.Text != "" && textBox10.Text != "" && textBox11.Text != "" && textBox12.Text != "")
            {
                try
                {
                    int i = dt.Rows.Count;
                    adx3 = new OleDbDataAdapter("select * from 阈值设置", conn);
                    dtx3 = new DataTable();
                    adx3.Fill(dtx3);
                    dt.Rows.Add();
                    dt.Rows[i][0] = label15.Text;
                    dt.Rows[i][1] = textBox5.Text;
                    dt.Rows[i][2] = label14.Text;
                    splits = dateTimePicker5.Value.ToString().Split(' ');
                    dt.Rows[i][3] = splits[0];
                    if (radioButton5.Checked == true) dt.Rows[i][4] = "男";
                    else dt.Rows[i][4] = "女";
                    dt.Rows[i][5] = str2;
                    dt3.Rows.Add();
                    dt3.Rows[i][0] = label20.Text;
                    dt3.Rows[i][1] = label2.Text;
                    dt3.Rows[i][2] = textBox6.Text;
                    dt3.Rows[i][3] = textBox7.Text;
                    dt3.Rows[i][4] = label22.Text;
                    dt3.Rows[i][5] = textBox8.Text;
                    dt3.Rows[i][6] = textBox9.Text;
                    dt3.Rows[i][7] = textBox10.Text;
                    dt3.Rows[i][8] = textBox11.Text;
                    dt3.Rows[i][9] = textBox12.Text;
                    dt3.Rows[i][10] = numericUpDown3.Value.ToString();
                    dt3.Rows[i][11] = numericUpDown4.Value.ToString();
                    dt5.Rows.Add();
                    dt5.Rows[i][0] = label44.Text;
                    dt5.Rows[i][1] = label43.Text;
                    dt5.Rows[i][2] = numericUpDown5.Value.ToString();
                    dt5.Rows[i][3] = numericUpDown6.Value.ToString();
                    dt5.Rows[i][4] = numericUpDown7.Value.ToString();
                    dt5.Rows[i][5] = numericUpDown8.Value.ToString();
                    dt5.Rows[i][6] = numericUpDown9.Value.ToString();
                    dt5.Rows[i][7] = numericUpDown10.Value.ToString();
                    dt5.Rows[i][8] = numericUpDown11.Value.ToString();
                    dtx3.Rows.Add();
                    dtx3.Rows[i][0] = label20.Text;
                    dtx3.Rows[i][1] = label2.Text;
                    for(int j = 2; j < 18; j++)
                    {
                        dtx3.Rows[i][j] = 0;
                    }
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(add);
                    add.Update(dt);
                    cmdb = new OleDbCommandBuilder(add2);
                    add2.Update(dt3);
                    cmdb = new OleDbCommandBuilder(add3);
                    add3.Update(dt5);
                    cmdb = new OleDbCommandBuilder(adx3);
                    adx3.Update(dtx3);
                    File.Copy(Application.StartupPath + @"\mdbData\basisData.mdb",Application.StartupPath + @"\mdbData\" + label15.Text + "_data.mdb");
                    MessageBox.Show("添加成功!");
                    label15.Text = label20.Text = label44.Text = (Int32.Parse(label15.Text) + 1).ToString();
                    adp = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
                    dt7 = new DataTable();
                    adp.Fill(dt7);
                    dt7 = dt7.AsEnumerable().Take(15).CopyToDataTable<DataRow>();
                    dataGridView1.DataSource = dt7;
                    dataGridView2.DataSource = dt;
                    for (int i2 = 0; i2 < dataGridView1.Rows.Count; i2++)
                    {
                        dataGridView1.Rows[i2].Height = 28;
                    }
                    if(dt.Rows.Count % 15 == 1)
                    {
                        las = (dt.Rows.Count - 1) / 15 + 1;
                        label4.Text = "/" + las.ToString();
                    }
                    textBox5.Text = textBox6.Text = textBox7.Text = textBox8.Text = textBox9.Text = textBox10.Text = textBox11.Text = textBox12.Text = "";
                    numericUpDown5.Value = numericUpDown6.Value = numericUpDown7.Value = numericUpDown8.Value = numericUpDown9.Value = numericUpDown10.Value = numericUpDown11.Value = 1;
                    label14.Text = label22.Text = "0";
                    label2.Text = label43.Text = "（自动显示）";
                    numericUpDown3.Value = numericUpDown4.Value = 0;
                    radioButton5.Checked = true;
                    str2 = "";
                    pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + "基本背景.png");
                    if (las != 1) wei = Int32.Parse(dt.Rows[14][0].ToString());
                    else wei = Int32.Parse(dt.Rows[dt.Rows.Count - 1][0].ToString());
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(add);
                    add.Update(dt2);
                    cmdb = new OleDbCommandBuilder(add2);
                    add2.Update(dt4);
                    cmdb = new OleDbCommandBuilder(add3);
                    add3.Update(dt6);
                    dt = new DataTable();
                    dt3 = new DataTable();
                    dt5 = new DataTable();
                    add.Fill(dt);
                    add2.Fill(dt3);
                    add3.Fill(dt5);
                }
            }
            else
            {
                MessageBox.Show("有部分信息为空！请填写全部信息！", "提示");
            }
        }

        private void DateTimePicker5_ValueChanged(object sender, EventArgs e)//出生日期变化时改变年龄（添加）
        {
            int y = DateTime.Now.Year - dateTimePicker5.Value.Year;
            label14.Text = y.ToString();
        }

        private void button20_Click(object sender, EventArgs e)//点击“前一页”按钮（统计）
        {
            if (label97.Text != "1")
            {
                count2--;
                adp2 = new OleDbDataAdapter("select ID,姓名 from 个人基本信息 where ID >= " + arr2[count2].ToString() + " and ( 姓名 like '%" + textBox14.Text + "%' or ID like '%" + textBox14.Text + "%' ) ", conn);
                dt8 = new DataTable();
                adp2.Fill(dt8);
                dataGridView3.DataSource = dt3;
                for (int i = 0; i < dataGridView3.Rows.Count; i++)
                {
                    dataGridView3.Rows[i].Height = 28;
                }
                if (dt8.Rows.Count > 14) wei2 = Int32.Parse(dt8.Rows[14][0].ToString());
                else wei2 = Int32.Parse(dt8.Rows[dt8.Rows.Count - 1][0].ToString());
                label97.Text = (Int32.Parse(label97.Text) - 1).ToString();
                textBox13.Text = dt8.Rows[0][0].ToString();
            }
        }

        private void button23_Click(object sender, EventArgs e)//点击“后一页”按钮（统计）
        {
            if (label96.Text != "/" + label97.Text)
            {
                adp2 = new OleDbDataAdapter("select ID,姓名 from 个人基本信息 where ID > " + wei2.ToString() + " and ( 姓名 like '%" + textBox14.Text + "%' or ID like '%" + textBox14.Text + "%' ) ", conn);
                dt8 = new DataTable();
                adp2.Fill(dt8);
                dataGridView3.DataSource = dt8;
                for (int i = 0; i < dataGridView3.Rows.Count; i++)
                {
                    dataGridView3.Rows[i].Height = 28;
                }
                arr2[++count2] = Int32.Parse(dt8.Rows[0][0].ToString());
                if (dt8.Rows.Count > 14) wei2 = Int32.Parse(dt8.Rows[14][0].ToString());
                else wei2 = Int32.Parse(dt8.Rows[dt8.Rows.Count - 1][0].ToString());
                label97.Text = (Int32.Parse(label97.Text) + 1).ToString();
                textBox13.Text = dt8.Rows[0][0].ToString();
            }
        }

        private void button21_Click(object sender, EventArgs e)//点击“搜索用户”按钮（统计）
        {
            adp2 = new OleDbDataAdapter("select ID,姓名 from 个人基本信息 where 姓名 like '%" + textBox14.Text + "%' or ID like '%" + textBox14.Text + "%'", conn);
            dt8 = new DataTable();
            adp2.Fill(dt8);
            if (dt8.Rows.Count.ToString() != "0")
            {
                button20.Enabled = button23.Enabled = true;
                dataGridView3.DataSource = dt8;
                textBox13.Text = dt8.Rows[0][0].ToString();
                count2 = 0;
                fir2 = 1;
                las2 = (dt8.Rows.Count - 1) / 15 + 1;
                label97.Text = fir2.ToString();
                label96.Text = "/" + las2.ToString();
                arr2[count2] = Int32.Parse(dt8.Rows[0][0].ToString());
                if (las2 != 1) wei2 = Int32.Parse(dt8.Rows[14][0].ToString());
                else wei2 = Int32.Parse(dt8.Rows[dt8.Rows.Count - 1][0].ToString());
                for (int i = 0; i < dataGridView3.Rows.Count; i++)
                {
                    dataGridView3.Rows[i].Height = 28;
                }
            }
            else
            {
                MessageBox.Show("无查询记录");
                textBox14.Text = "";
                adp2 = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
                dt8 = new DataTable();
                adp2.Fill(dt8);
                dataGridView3.DataSource = dt8;
                for (int i = 0; i < dataGridView3.Columns.Count; i++)
                {
                    dataGridView3.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
                }
                dataGridView3.Columns[0].Width = 70;
                dataGridView3.Columns[1].Width = 100;
                count2 = 0;
                fir2 = 1;
                las2 = (dt8.Rows.Count - 1) / 15 + 1;
                label97.Text = fir2.ToString();
                label96.Text = "/" + las2.ToString();
                arr2[count2] = Int32.Parse(dt8.Rows[0][0].ToString());
                if (las2 != 1) wei2 = Int32.Parse(dt8.Rows[14][0].ToString());
                else wei2 = Int32.Parse(dt8.Rows[dt8.Rows.Count - 1][0].ToString());
                for (int i = 0; i < dataGridView3.Rows.Count; i++)
                {
                    dataGridView3.Rows[i].Height = 28;
                }
                textBox13.Text = dt8.Rows[0][0].ToString();
            }
        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)//点击“日”单选钮（统计）
        {
            button24.Visible = button25.Visible = true;
            button24.Text = "前移一日";
            button25.Text = "后移一日";
            dateTimePicker1.Text = dateTimePicker6.Text;
            dateTimePicker7.Text = "00:00:00";
            dateTimePicker8.Text = "23:59:59";
            dateTimePicker7.Enabled = dateTimePicker8.Enabled = false;
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)//点击“周”单选钮（统计）
        {
            button24.Visible = button25.Visible = true;
            button24.Text = "前移一周";
            button25.Text = "后移一周";
            sp = dateTimePicker6.Text.Split('年', '月', '日');
            y = Int32.Parse(sp[0]);
            M = Int32.Parse(sp[1]);
            d = Int32.Parse(sp[2]);
            d -= 7;
            if(d <= 0)
            {
                if (M == 1)
                {
                    y--;
                    M = 12;
                }
                else M--;
                d += judgeDay(y, M);
            }
            dateTimePicker1.Text = y.ToString() + "年" + M.ToString() + "月" + d.ToString() + "日";
            dateTimePicker7.Text = "00:00:00";
            dateTimePicker8.Text = "23:59:59";
            dateTimePicker7.Enabled = dateTimePicker8.Enabled = false;
        }

        private void textBox14_TextChanged(object sender, EventArgs e)//搜索信息发生改变（统计）
        {
            if (textBox14.Text != "")
            {
                button20.Enabled = button23.Enabled = false;
            }
            else
            {
                button20.Enabled = button23.Enabled = true;
            }
        }

        private void TextBox5_TextChanged(object sender, EventArgs e)//名字发生变化时同步（添加）
        {
            label2.Text = label43.Text = textBox5.Text;
        }

        private void Button1_Click(object sender, EventArgs e)//点击“前一页”按钮
        {
            if(label3.Text != "1")
            {
                count--;
                adp = new OleDbDataAdapter("select ID,姓名 from 个人基本信息 where ID >= " + arr[count].ToString() + " and ( 姓名 like '%" + textBox2.Text + "%' or ID like '%" + textBox2.Text + "%' ) ", conn);
                dt7 = new DataTable();
                adp.Fill(dt7);
                dt7 = dt7.AsEnumerable().Take(15).CopyToDataTable<DataRow>();
                dataGridView1.DataSource = dt7;
                for (int i = 0; i < dataGridView1.Rows.Count; i++)
                {
                    dataGridView1.Rows[i].Height = 28;
                }
                if (dt.Rows.Count - count * 15 > 14) wei = Int32.Parse(dt.Rows[14 + count * 15][0].ToString());
                else wei = Int32.Parse(dt.Rows[dt.Rows.Count - 1][0].ToString());
                label3.Text = (Int32.Parse(label3.Text) - 1).ToString();
                wulala(count, 0);
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e)//搜索信息发生改变
        {
            if(textBox2.Text != "")
            {
                button1.Enabled = button2.Enabled = false;
            }
            else
            {
                button1.Enabled = button2.Enabled = true;
            }
        }

        private void dataGridView3_CellClick(object sender, DataGridViewCellEventArgs e)//选中单元格发生改变（统计）
        {
            int r2 = e.RowIndex;
            if (r2 < dt8.Rows.Count && r2 >= 0)
            {
                textBox13.Text = dt8.Rows[r2][0].ToString();
            }
            if (c1 == 1)
            {
                tongji();
            }
            else if (c2 == 1)
            {
                if(e1 == 1)
                {
                    int r = dataGridView3.CurrentCell.RowIndex;
                    if (dataGridView3.SelectedRows.Count == 1)
                    {
                        string Id = dt8.Rows[r][0].ToString();
                        sp5 = dateTimePicker2.Text.Split('年', '月', '日');
                        y3 = Int32.Parse(sp5[0]);
                        M3 = Int32.Parse(sp5[1]);
                        d3 = Int32.Parse(sp5[2]);
                        conn2 = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\mdbData\" + Id + "_data.mdb");
                        adx2 = new OleDbDataAdapter("select * from 行为表 where Yea = " + y3.ToString() + " and Mon = " + M3.ToString() + " and Day = " + d3.ToString(), conn2);
                        dtx2 = new DataTable();
                        adx2.Fill(dtx2);
                        int i, j;
                        int[,] a = new int[24, 9];
                        int[,] a2 = new int[72, 9];
                        int[,] a3 = new int[288, 9];
                        for (i = 0; i < dtx2.Rows.Count; i++)
                        {
                            if (dtx2.Rows[i][7].ToString() == "sitting") j = 1;
                            else if (dtx2.Rows[i][7].ToString() == "standing") j = 2;
                            else if (dtx2.Rows[i][7].ToString() == "slowwalk") j = 3;
                            else if (dtx2.Rows[i][7].ToString() == "fastwalk") j = 4;
                            else if (dtx2.Rows[i][7].ToString() == "upstair") j = 6;
                            else if (dtx2.Rows[i][7].ToString() == "downstair") j = 5;
                            else if (dtx2.Rows[i][7].ToString() == "slowrun") j = 7;
                            else j = 8;
                            a[Int32.Parse(dtx2.Rows[i][4].ToString()), j]++;
                            a2[Int32.Parse(dtx2.Rows[i][4].ToString()) * 3 + Int32.Parse(dtx2.Rows[i][5].ToString()) / 20, j]++;
                            a3[Int32.Parse(dtx2.Rows[i][4].ToString()) * 12 + Int32.Parse(dtx2.Rows[i][5].ToString()) / 5, j]++;
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
                                chart5.Series[0].Points[i].YValues[0] = 1;
                            }
                            else
                            {
                                for (j = 0; j < 9; j++)
                                {
                                    if (a2[i, j] == max) index = j;
                                }
                                chart5.Series[0].Points[i].YValues[0] = index + 1;
                            }
                        }
                        chart5.Series[0].Points[0].IsEmpty = false;
                        for (i = 0; i < 288; i++)
                        {
                            List<int> list2 = new List<int>() { a3[i, 0], a3[i, 1], a3[i, 2], a3[i, 3], a3[i, 4], a3[i, 5], a3[i, 6], a3[i, 7], a3[i, 8] };
                            int max = list2.Max(), index = 0;
                            if (max == 0)
                            {
                                chart4.Series[0].Points[i].YValues[0] = 1;
                            }
                            else
                            {
                                for (j = 0; j < 9; j++)
                                {
                                    if (a3[i, j] == max) index = j;
                                }
                                chart4.Series[0].Points[i].YValues[0] = index + 1;
                            }
                        }
                        chart4.Series[0].Points[0].IsEmpty = false;
                    }
                    else
                    {
                        MessageBox.Show("请单击选中一行数据！");
                    }
                }
                else if(e2 == 1)
                {
                    int r = dataGridView3.CurrentCell.RowIndex;
                    if (dataGridView3.SelectedRows.Count == 1)
                    {
                        baogao(r);
                    }
                    else
                    {
                        MessageBox.Show("请单击选中一行数据！");
                    }
                }
            }
        }

        private void button22_Click(object sender, EventArgs e)//点击“显示所有用户”按钮（统计）
        {
            adp2 = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
            dt8 = new DataTable();
            adp2.Fill(dt8);
            dataGridView3.DataSource = dt8;
            textBox13.Text = dt8.Rows[0][0].ToString();
            for (int i = 0; i < dataGridView3.Rows.Count; i++)
            {
                dataGridView3.Rows[i].Height = 28;
            }
            dataGridView3.Columns[0].Width = 70;
            dataGridView3.Columns[1].Width = 100;
            textBox14.Text = "";
            fir2 = 1;
            las2 = (dt8.Rows.Count - 1) / 15 + 1;
            label97.Text = fir2.ToString();
            label96.Text = "/" + las2.ToString();
            arr2[count2] = Int32.Parse(dt8.Rows[0][0].ToString());
            if (las2 != 1) wei2 = Int32.Parse(dt8.Rows[14][0].ToString());
            else wei2 = Int32.Parse(dt8.Rows[dt8.Rows.Count - 1][0].ToString());
            textBox14.Text = "";
        }

        private void TextBox6_TextChanged(object sender, EventArgs e)//当身高数据改变时改变BMI（添加）
        {
            if (textBox6.Text != "" && textBox7.Text != "")
            {
                try
                {
                    double a = double.Parse(textBox6.Text), b = double.Parse(textBox7.Text);
                    a = b / (a / 100) / (a / 100);
                    a = Math.Round(a, 1);
                    label22.Text = a.ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                }
            }
        }

        private void TextBox7_TextChanged(object sender, EventArgs e)//当体重数据改变时改变BMI（添加）
        {
            if (textBox6.Text != "" && textBox7.Text != "")
            {
                try
                {
                    double a = double.Parse(textBox6.Text), b = double.Parse(textBox7.Text);
                    a = b / (a / 100) / (a / 100);
                    a = Math.Round(a, 1);
                    label22.Text = a.ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                }
            }
        }

        private void Button9_Click(object sender, EventArgs e)//点击“重置数据”按钮（添加）
        {
            textBox5.Text = textBox6.Text = textBox7.Text = textBox8.Text = textBox9.Text = textBox10.Text = textBox11.Text = textBox12.Text = "";
            numericUpDown5.Value = numericUpDown6.Value = numericUpDown7.Value = numericUpDown8.Value = numericUpDown9.Value = numericUpDown10.Value = numericUpDown11.Value = 1;
            label14.Text = label22.Text = "（自动生成）";
            label2.Text = label43.Text = "（自动显示）";
            numericUpDown3.Value = numericUpDown4.Value = 0;
            radioButton5.Checked = true;
            str2 = "";
            pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + "基本背景.png");
        }

        private void Button2_Click(object sender, EventArgs e)//点击“后一页”按钮
        {
            if(label4.Text != "/" + label3.Text)
            {
                count++;
                adp = new OleDbDataAdapter("select ID,姓名 from 个人基本信息 where ID > " + wei.ToString() + " and ( 姓名 like '%" + textBox2.Text + "%' or ID like '%" + textBox2.Text + "%' ) ", conn);
                dt7 = new DataTable();
                adp.Fill(dt7);
                dt7 = dt7.AsEnumerable().Take(15).CopyToDataTable<DataRow>();
                dataGridView1.DataSource = dt7;
                for (int i = 0; i < dataGridView1.Rows.Count; i++)
                {
                    dataGridView1.Rows[i].Height = 28;
                }
                arr[count] = Int32.Parse(dt.Rows[0 + count*15][0].ToString());
                if (dt.Rows.Count - count * 15 > 14) wei = Int32.Parse(dt.Rows[14 + count * 15][0].ToString());
                else wei = Int32.Parse(dt.Rows[dt.Rows.Count - 1][0].ToString());
                label3.Text = (Int32.Parse(label3.Text) + 1).ToString();
                wulala(count, 0);
            }
        }

        private void Button17_Click(object sender, EventArgs e)//点击“选择”按钮（添加）
        {
            dlgOpenFile = new OpenFileDialog { Filter = "图片(*.jpg)|*.jpg|图片(*.jpeg)|*.jpeg|图片(*.png)|*.png" };
            if (dlgOpenFile.ShowDialog() == DialogResult.OK) //OK表示按下了“打开”
            {
                splits3 = dlgOpenFile.FileName.Split('\\');
                str2 = splits3[splits3.Length - 1];
                pictureBox1.LoadAsync(dlgOpenFile.FileName);
                try
                {
                    File.Copy(dlgOpenFile.FileName, Application.StartupPath + @"\photos\" + splits3[splits3.Length - 1]);
                }
                catch { }
            }
        }

        private void 添加用户ToolStripMenuItem_Click(object sender, EventArgs e)//菜单栏点击“添加用户”
        {
            groupBox1.Visible = true;
            groupBox7.Visible = false;
            groupBox3.Visible = true;
            groupBox2.Visible = groupBox4.Visible = groupBox5.Visible = groupBox6.Visible = false;
            conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + @"..\DataBase\人体行为.mdb");
            add = new OleDbDataAdapter("select * from 个人基本信息", conn);
            add2 = new OleDbDataAdapter("select * from 身体数据", conn);
            add3 = new OleDbDataAdapter("select * from 健康数据", conn);
            adp = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
            dt = new DataTable();
            dt2 = new DataTable();
            dt3 = new DataTable();
            dt4 = new DataTable();
            dt5 = new DataTable();
            dt6 = new DataTable();
            dt7 = new DataTable();
            adp.Fill(dt7);
            add.Fill(dt);
            add.Fill(dt2);
            add2.Fill(dt3);
            add2.Fill(dt4);
            add3.Fill(dt5);
            add3.Fill(dt6);
            dt7 = dt7.AsEnumerable().Take(15).CopyToDataTable<DataRow>();
            dataGridView1.DataSource = dt7;
            dataGridView2.DataSource = dt;
            for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
            {
                this.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }
            dataGridView1.Columns[0].Width = 70;
            dataGridView1.Columns[1].Width = 100;
            count = 0;
            wulala(count,0);
            pictureBox1.LoadAsync(Application.StartupPath + @"\photos\基本背景.png");
            fir = 1;
            las = (dt.Rows.Count - 1) / 15 + 1;
            label3.Text = fir.ToString();
            label4.Text = "/" + las.ToString();
            arr[count] = Int32.Parse(dt.Rows[0][0].ToString());
            if (las != 1) wei = Int32.Parse(dt.Rows[14][0].ToString());
            else wei = Int32.Parse(dt.Rows[dt.Rows.Count - 1][0].ToString());
            textBox2.Text = "";
            button1.Enabled = button2.Enabled = button14.Enabled = button15.Enabled = textBox2.Enabled = false;
        }

        private void DataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)//数据表选中格子发生改变时
        {
            int r = e.RowIndex;
            if (r < dt.Rows.Count - count * 15 && r >= 0)
            {
                wulala(count,r);
            }
        }

        private void 数据统计ToolStripMenuItem_Click(object sender, EventArgs e)//菜单栏点击“数据统计”
        {
            c1 = 1;
            c2 = 0;
            chart1.Visible = label108.Visible = pictureBox3.Visible = pictureBox4.Visible = pictureBox5.Visible = false;
            label119.Visible = label120.Visible = label121.Visible = false;
            adp2 = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
            dt8 = new DataTable();
            adp2.Fill(dt8);
            dataGridView3.DataSource = dt8;
            textBox13.Text = dt8.Rows[0][0].ToString();
            for (int i = 0; i < dataGridView3.Rows.Count; i++)
            {
                dataGridView3.Rows[i].Height = 28;
            }
            dataGridView3.Columns[0].Width = 70;
            dataGridView3.Columns[1].Width = 100;
            for (int i = 0; i < dataGridView3.Columns.Count; i++)
            {
                dataGridView3.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }
            fir2 = 1;
            las2 = (dt8.Rows.Count - 1) / 15 + 1;
            label97.Text = fir2.ToString();
            label96.Text = "/" + las2.ToString();
            arr2[count2] = Int32.Parse(dt8.Rows[0][0].ToString());
            if (las2 != 1) wei2 = Int32.Parse(dt8.Rows[14][0].ToString());
            else wei2 = Int32.Parse(dt8.Rows[dt8.Rows.Count - 1][0].ToString());
            groupBox7.Visible = true;
            groupBox1.Visible = false;
            groupBox4.Visible = true;
            groupBox3.Visible = groupBox2.Visible = groupBox5.Visible = groupBox6.Visible = false;
            radioButton1.Checked = true;
        }

        private void 历史记录ToolStripMenuItem_Click(object sender, EventArgs e)//菜单栏点击“历史记录”
        {
            c1 = 0;
            c2 = 1;
            e1 = 1;
            e2 = 0;
            adp2 = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
            dt8 = new DataTable();
            adp2.Fill(dt8);
            dataGridView3.DataSource = dt8;
            textBox13.Text = dt8.Rows[0][0].ToString();
            for (int i = 0; i < dataGridView3.Rows.Count; i++)
            {
                dataGridView3.Rows[i].Height = 28;
            }
            dataGridView3.Columns[0].Width = 70;
            dataGridView3.Columns[1].Width = 100;
            for (int i = 0; i < dataGridView3.Columns.Count; i++)
            {
                dataGridView3.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }
            fir2 = 1;
            las2 = (dt8.Rows.Count - 1) / 15 + 1;
            label97.Text = fir2.ToString();
            label96.Text = "/" + las2.ToString();
            arr2[count2] = Int32.Parse(dt8.Rows[0][0].ToString());
            if (las2 != 1) wei2 = Int32.Parse(dt8.Rows[14][0].ToString());
            else wei2 = Int32.Parse(dt8.Rows[dt8.Rows.Count - 1][0].ToString());
            groupBox7.Visible = true;
            groupBox1.Visible = false;
            groupBox5.Visible = true;
            groupBox3.Visible = groupBox4.Visible = groupBox2.Visible = groupBox6.Visible = false;
            int r = 0;
            if (dataGridView3.SelectedRows.Count == 1)
            {
                string Id = dt8.Rows[r][0].ToString();
                sp5 = dateTimePicker2.Text.Split('年', '月', '日');
                y3 = Int32.Parse(sp5[0]);
                M3 = Int32.Parse(sp5[1]);
                d3 = Int32.Parse(sp5[2]);
                conn2 = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\mdbData\" + Id + "_data.mdb");
                adx2 = new OleDbDataAdapter("select * from 行为表 where Yea = " + y3.ToString() + " and Mon = " + M3.ToString() + " and Day = " + d3.ToString(), conn2);
                dtx2 = new DataTable();
                adx2.Fill(dtx2);
                int i, j;
                int[,] a = new int[24, 9];
                int[,] a2 = new int[72, 9];
                int[,] a3 = new int[288, 9];
                for (i = 0; i < dtx2.Rows.Count; i++)
                {
                    if (dtx2.Rows[i][7].ToString() == "sitting") j = 1;
                    else if (dtx2.Rows[i][7].ToString() == "standing") j = 2;
                    else if (dtx2.Rows[i][7].ToString() == "slowwalk") j = 3;
                    else if (dtx2.Rows[i][7].ToString() == "fastwalk") j = 4;
                    else if (dtx2.Rows[i][7].ToString() == "upstair") j = 6;
                    else if (dtx2.Rows[i][7].ToString() == "downstair") j = 5;
                    else if (dtx2.Rows[i][7].ToString() == "slowrun") j = 7;
                    else j = 8;
                    a[Int32.Parse(dtx2.Rows[i][4].ToString()), j]++;
                    a2[Int32.Parse(dtx2.Rows[i][4].ToString()) * 3 + Int32.Parse(dtx2.Rows[i][5].ToString()) / 20, j]++;
                    a3[Int32.Parse(dtx2.Rows[i][4].ToString()) * 12 + Int32.Parse(dtx2.Rows[i][5].ToString()) / 5, j]++;
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
                        chart5.Series[0].Points[i].YValues[0] = 1;
                    }
                    else
                    {
                        for (j = 0; j < 9; j++)
                        {
                            if (a2[i, j] == max) index = j;
                        }
                        chart5.Series[0].Points[i].YValues[0] = index + 1;
                    }
                }
                chart5.Series[0].Points[0].IsEmpty = false;
                for (i = 0; i < 288; i++)
                {
                    List<int> list2 = new List<int>() { a3[i, 0], a3[i, 1], a3[i, 2], a3[i, 3], a3[i, 4], a3[i, 5], a3[i, 6], a3[i, 7], a3[i, 8] };
                    int max = list2.Max(), index = 0;
                    if (max == 0)
                    {
                        chart4.Series[0].Points[i].YValues[0] = 1;
                    }
                    else
                    {
                        for (j = 0; j < 9; j++)
                        {
                            if (a3[i, j] == max) index = j;
                        }
                        chart4.Series[0].Points[i].YValues[0] = index + 1;
                    }
                }
                chart4.Series[0].Points[0].IsEmpty = false;
            }
        }

        private void 历史报告ToolStripMenuItem_Click(object sender, EventArgs e)//菜单栏点击“历史报告”
        {
            c1 = 0;
            c2 = 1;
            e2 = 1;
            e1 = 0;
            adp2 = new OleDbDataAdapter("select ID,姓名 from 个人基本信息", conn);
            dt8 = new DataTable();
            adp2.Fill(dt8);
            dataGridView3.DataSource = dt8;
            textBox13.Text = dt8.Rows[0][0].ToString();
            for (int i = 0; i < dataGridView3.Rows.Count; i++)
            {
                dataGridView3.Rows[i].Height = 28;
            }
            dataGridView3.Columns[0].Width = 70;
            dataGridView3.Columns[1].Width = 100;
            for (int i = 0; i < dataGridView3.Columns.Count; i++)
            {
                dataGridView3.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }
            fir2 = 1;
            las2 = (dt8.Rows.Count - 1) / 15 + 1;
            label97.Text = fir2.ToString();
            label96.Text = "/" + las2.ToString();
            arr2[count2] = Int32.Parse(dt8.Rows[0][0].ToString());
            if (las2 != 1) wei2 = Int32.Parse(dt8.Rows[14][0].ToString());
            else wei2 = Int32.Parse(dt8.Rows[dt8.Rows.Count - 1][0].ToString());
            groupBox7.Visible = true;
            groupBox1.Visible = false;
            groupBox6.Visible = true;
            groupBox3.Visible = groupBox4.Visible = groupBox5.Visible = groupBox2.Visible = false;
            baogao(0);
        }

        private void Button13_Click(object sender, EventArgs e)
        {
            groupBox6.Visible = false;
        }

        private void Button12_Click(object sender, EventArgs e)
        {
            groupBox5.Visible = false;
        }

        private void Button8_Click(object sender, EventArgs e)
        {
            groupBox4.Visible = false;
        }

        private void Button7_Click(object sender, EventArgs e)
        {
            groupBox3.Visible = false;
        }

        private void Button6_Click(object sender, EventArgs e)
        {
            groupBox2.Visible = false;
        }

        private void 用户管理_FormClosed(object sender, FormClosedEventArgs e)//关闭当前页面后
        {
            server.Close();
            主页面 a = new 主页面();
            a.Show();
            a.deng();
        }
    }
}
