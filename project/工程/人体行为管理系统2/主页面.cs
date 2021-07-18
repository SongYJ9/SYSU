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

namespace 人体行为2
{
    public partial class 主页面 : Form
    {
        public 主页面()
        {
            InitializeComponent();
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            行为监控 b = new 行为监控();
            b.Show();
            this.Hide();
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            用户管理 b = new 用户管理();
            b.Show();
            this.Hide();
        }

        private void Button3_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")
            {
                MessageBox.Show("请输入用户名！", "提示");
            }
            else if (textBox2.Text == "")
            {
                MessageBox.Show("请输入密码！", "提示");
            }
            else if ((textBox1.Text == "老师" || textBox1.Text == "laoshi") && textBox2.Text == "111")//账号密码
            {
                label2.Visible = label3.Visible = textBox1.Visible = textBox2.Visible = button3.Visible = false;
                button1.Visible = button2.Visible = true;
            }
            else
            {
                MessageBox.Show("用户名或密码错误，请重新输入！", "提示");
            }
        }

        private void 主页面_Load(object sender, EventArgs e)
        {
            label2.Visible = label3.Visible = textBox1.Visible = textBox2.Visible = button3.Visible = true;
            button1.Visible = button2.Visible = false;
        }

        private void 主页面_FormClosed(object sender, FormClosedEventArgs e)
        {
            System.Environment.Exit(0);
        }


        public void deng()
        {
            label2.Visible = label3.Visible = textBox1.Visible = textBox2.Visible = button3.Visible = false;
            button1.Visible = button2.Visible = true;
        }
    }
}
