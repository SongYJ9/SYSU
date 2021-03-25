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
    public partial class 添加基本个人信息 : Form
    {
        string str = "";
        string[] splits;
        OpenFileDialog dlgOpenFile;
        OleDbDataAdapter add;
        DataTable dt, dt2;
        OleDbConnection conn;

        public 添加基本个人信息()
        {
            InitializeComponent();
        }

        private void Button4_Click(object sender, EventArgs e)//点击“取消”按钮
        {
            this.Close();
        }

        private void Button3_Click(object sender, EventArgs e)//点击“重置”按钮
        {
            textBox1.Text = textBox2.Text = textBox3.Text = textBox4.Text = textBox5.Text = str = "";
            pictureBox1.Image = null;
        }

        private void Button1_Click(object sender, EventArgs e)//点击“选择图片”按钮
        {
            dlgOpenFile = new OpenFileDialog { Filter = "图片(*.jpg)|*.jpg|图片(*.jpeg)|*.jpeg|图片(*.png)|*.png" };
            if (dlgOpenFile.ShowDialog() == DialogResult.OK) //OK表示按下了“打开”
            {
                splits = dlgOpenFile.FileName.Split('\\');
                str = splits[splits.Length - 1];//获取文件名
                pictureBox1.LoadAsync(dlgOpenFile.FileName);
                try
                {
                    File.Copy(dlgOpenFile.FileName, Application.StartupPath + @"\photos\" + splits[splits.Length - 1]);//复制图片保存到photos文件夹中
                }
                catch { }//如果文件夹中已存在该图片，则不做任何处理
            }
        }

        private void 添加基本个人信息_Load(object sender, EventArgs e)
        {
            conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\人体行为数据库管理系统.mdb");
            add = new OleDbDataAdapter("select * from 基本个人信息", conn);
            dt = new DataTable();
            dt2 = new DataTable();
            add.Fill(dt);
            add.Fill(dt2);
            radioButton1.Checked = true;
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
                    if (radioButton1.Checked == true)
                    {
                        dt.Rows[i][1] = "男";
                    }
                    else
                    {
                        dt.Rows[i][1] = "女";
                    }
                    dt.Rows[i][2] = textBox2.Text;
                    dt.Rows[i][3] = textBox5.Text;
                    dt.Rows[i][4] = textBox3.Text;
                    dt.Rows[i][5] = textBox4.Text;
                    dt.Rows[i][6] = str;//数据库中保存图片名，相当于保存图片路径
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(add);
                    add.Update(dt);
                    MessageBox.Show("保存成功!");
                    textBox1.Text = textBox2.Text = textBox3.Text = textBox4.Text = textBox5.Text = str = "";
                    pictureBox1.Image = null;
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
    }
}
