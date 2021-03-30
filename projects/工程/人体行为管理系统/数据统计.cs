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

namespace 人体行为管理系统2
{
    public partial class 数据统计 : Form
    {
        OleDbDataAdapter adp,adq,ads;
        DataTable dt,dt2,dt3;
        OleDbConnection conn;
        int i, j, k, l, x1, x2, x3, x4, x5, x6, x7, x8, x9;
        double max, min, sum, max2, min2, sum2, max3, min3, sum3, max4, min4, sum4;

        private void Button1_Click(object sender, EventArgs e)//点击“确定”按钮
        {
            this.Dispose();
        }

        public 数据统计()
        {
            InitializeComponent();
        }

        private void 数据统计_Load(object sender, EventArgs e)
        {
            conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\人体行为数据库管理系统.mdb");
            adp = new OleDbDataAdapter("select * from 基本个人信息", conn);
            dt = new DataTable();
            adp.Fill(dt);
            adq = new OleDbDataAdapter("select * from 身体信息", conn);
            dt2 = new DataTable();
            adq.Fill(dt2);
            ads = new OleDbDataAdapter("select * from 健康问题信息", conn);
            dt3 = new DataTable();
            ads.Fill(dt3);
            //基本个人信息
            i = dt.Rows.Count;
            textBox1.Text = i.ToString();
            if (i > 0)
            {
                j = k = 0;
                sum = 0;
                max = min = Convert.ToDouble(dt.Rows[0][2]);
                for (l = 0; l < i; l++)
                {
                    if (dt.Rows[l][1].ToString() == "男")
                    {
                        j++;
                    }
                    else
                    {
                        k++;
                    }
                    if (Convert.ToDouble(dt.Rows[l][2]) > max)
                    {
                        max = Convert.ToDouble(dt.Rows[l][2]);
                    }
                    if (Convert.ToDouble(dt.Rows[l][2]) < min)
                    {
                        min = Convert.ToDouble(dt.Rows[l][2]);
                    }
                    sum += Convert.ToDouble(dt.Rows[l][2]);
                }
                sum /= i;
                sum = Math.Round(sum, 1);
                textBox2.Text = j.ToString();
                textBox3.Text = k.ToString();
                textBox4.Text = max.ToString();
                textBox5.Text = min.ToString();
                textBox6.Text = sum.ToString();
            }
            //身体信息
            i = dt2.Rows.Count;
            textBox29.Text = i.ToString();
            if (i > 0)
            {
                sum = sum2 = sum3 = sum4 = 0;
                max = min = Convert.ToDouble(dt2.Rows[0][1]);
                max2 = min2 = Convert.ToDouble(dt2.Rows[0][2]);
                max3 = min3 = Convert.ToDouble(dt2.Rows[0][3]);
                max4 = min4 = Convert.ToDouble(dt2.Rows[0][4]);
                for (l = 0; l < i; l++)
                {
                    if (Convert.ToDouble(dt2.Rows[l][1]) > max)
                    {
                        max = Convert.ToDouble(dt2.Rows[l][1]);
                    }
                    if (Convert.ToDouble(dt2.Rows[l][1]) < min)
                    {
                        min = Convert.ToDouble(dt2.Rows[l][1]);
                    }
                    sum += Convert.ToDouble(dt2.Rows[l][1]);
                    if (Convert.ToDouble(dt2.Rows[l][2]) > max2)
                    {
                        max2 = Convert.ToDouble(dt2.Rows[l][2]);
                    }
                    if (Convert.ToDouble(dt2.Rows[l][2]) < min2)
                    {
                        min2 = Convert.ToDouble(dt2.Rows[l][2]);
                    }
                    sum2 += Convert.ToDouble(dt2.Rows[l][2]);
                    if (Convert.ToDouble(dt2.Rows[l][3]) > max3)
                    {
                        max3 = Convert.ToDouble(dt2.Rows[l][3]);
                    }
                    if (Convert.ToDouble(dt2.Rows[l][3]) < min3)
                    {
                        min3 = Convert.ToDouble(dt2.Rows[l][3]);
                    }
                    sum3 += Convert.ToDouble(dt2.Rows[l][3]);
                    if (Convert.ToDouble(dt2.Rows[l][4]) > max4)
                    {
                        max4 = Convert.ToDouble(dt2.Rows[l][4]);
                    }
                    if (Convert.ToDouble(dt2.Rows[l][4]) < min4)
                    {
                        min4 = Convert.ToDouble(dt2.Rows[l][4]);
                    }
                    sum4 += Convert.ToDouble(dt2.Rows[l][4]);
                }
                sum /= i;
                sum2 /= i;
                sum3 /= i;
                sum4 /= i;
                sum = Math.Round(sum, 1);
                sum2 = Math.Round(sum2, 1);
                sum3 = Math.Round(sum3, 1);
                sum4 = Math.Round(sum4, 1);
                textBox7.Text = max.ToString();
                textBox8.Text = min.ToString();
                textBox9.Text = sum.ToString();
                textBox10.Text = max2.ToString();
                textBox11.Text = min2.ToString();
                textBox12.Text = sum2.ToString();
                textBox13.Text = max3.ToString();
                textBox14.Text = min3.ToString();
                textBox15.Text = sum3.ToString();
                textBox16.Text = max4.ToString();
                textBox17.Text = min4.ToString();
                textBox18.Text = sum4.ToString();
            }
            //健康问题信息
            i = dt3.Rows.Count;
            textBox19.Text = i.ToString();
            if(i>0)
            {
                x1 = x2 = x3 = x4 = x5 = x6 = x7 = x8 = x9 = 0;
                for (l = 0; l < i; l++)
                {
                    if (dt3.Rows[l][1].ToString() != "" && dt3.Rows[l][1].ToString() != "无")
                    {
                        x1++;
                    }
                    if (dt3.Rows[l][2].ToString() != "" && dt3.Rows[l][2].ToString() != "无")
                    {
                        x2++;
                    }
                    if (dt3.Rows[l][3].ToString() != "" && dt3.Rows[l][3].ToString() != "无")
                    {
                        x3++;
                    }
                    if (dt3.Rows[l][4].ToString() != "" && dt3.Rows[l][4].ToString() != "无")
                    {
                        x4++;
                    }
                    if (dt3.Rows[l][5].ToString() != "" && dt3.Rows[l][5].ToString() != "无")
                    {
                        x5++;
                    }
                    if (dt3.Rows[l][6].ToString() != "" && dt3.Rows[l][6].ToString() != "无")
                    {
                        x6++;
                    }
                    if (dt3.Rows[l][7].ToString() != "" && dt3.Rows[l][7].ToString() != "无")
                    {
                        x7++;
                    }
                    if (dt3.Rows[l][8].ToString() != "" && dt3.Rows[l][8].ToString() != "无")
                    {
                        x8++;
                    }
                    if (dt3.Rows[l][9].ToString() != "" && dt3.Rows[l][9].ToString() != "无")
                    {
                        x9++;
                    }
                }
                textBox20.Text = x1.ToString();
                textBox21.Text = x2.ToString();
                textBox22.Text = x3.ToString();
                textBox23.Text = x4.ToString();
                textBox24.Text = x5.ToString();
                textBox25.Text = x6.ToString();
                textBox26.Text = x7.ToString();
                textBox27.Text = x8.ToString();
                textBox28.Text = x9.ToString();
            }
        }
    }
}
