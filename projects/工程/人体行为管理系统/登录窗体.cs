using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace 人体行为管理系统2
{
    public partial class 登录窗体 : Form
    {
        public 登录窗体()
        {
            InitializeComponent();
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            if(textBox1.Text == "")
            {
                MessageBox.Show("请输入用户名！","提示");
            }
            else if(textBox2.Text == "")
            {
                MessageBox.Show("请输入密码！", "提示");
            }
            else if((textBox1.Text == "老师" || textBox1.Text == "laoshi") && textBox2.Text == "111")//账号密码
            {
                MessageBox.Show("登录成功！即将进入主页面...", "提示");
                主窗体 a = new 主窗体();
                a.Show();//显示主窗体
                this.Hide();
            }
            else
            {
                MessageBox.Show("用户名或密码错误，请重新输入！","提示");
            }
        }
    }
}
