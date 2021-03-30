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
    public partial class 添加健康问题信息 : Form
    {
        OleDbDataAdapter add;
        DataTable dt, dt2;
        OleDbConnection conn;
        public 添加健康问题信息()
        {
            InitializeComponent();
        }

        private void Button3_Click(object sender, EventArgs e)//点击“重置”按钮
        {
            textBox1.Text = textBox2.Text = textBox3.Text = textBox4.Text = textBox5.Text = textBox6.Text = textBox7.Text = textBox8.Text = textBox9.Text = textBox10.Text = "";
        }

        private void Button4_Click(object sender, EventArgs e)//点击“取消”按钮
        {
            this.Close();
        }

        private void Button2_Click(object sender, EventArgs e)//点击“保存”按钮
        {
            if (textBox1.Text != "")
            {
                try
                {
                    int i = dt.Rows.Count;
                    dt.Rows.Add();
                    dt.Rows[i][0] = textBox1.Text;
                    dt.Rows[i][1] = textBox2.Text;
                    dt.Rows[i][2] = textBox3.Text;
                    dt.Rows[i][3] = textBox4.Text;
                    dt.Rows[i][4] = textBox5.Text;
                    dt.Rows[i][5] = textBox6.Text;
                    dt.Rows[i][6] = textBox7.Text;
                    dt.Rows[i][7] = textBox8.Text;
                    dt.Rows[i][8] = textBox9.Text;
                    dt.Rows[i][9] = textBox10.Text;
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(add);
                    add.Update(dt);
                    MessageBox.Show("保存成功!");
                    textBox1.Text = textBox2.Text = textBox3.Text = textBox4.Text = textBox5.Text = textBox6.Text = textBox7.Text = textBox8.Text = textBox9.Text = textBox10.Text = "";
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(add);
                    add.Update(dt2);
                    dt = new DataTable();
                    add.Fill(dt);
                }
            }
            else
            {
                MessageBox.Show("姓名不能为空！", "提示");
            }
        }

        private void 添加健康问题信息_Load(object sender, EventArgs e)
        {
            conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\人体行为数据库管理系统.mdb");
            add = new OleDbDataAdapter("select * from 健康问题信息", conn);
            dt = new DataTable();
            dt2 = new DataTable();
            add.Fill(dt);
            add.Fill(dt2);
        }
    }
}
