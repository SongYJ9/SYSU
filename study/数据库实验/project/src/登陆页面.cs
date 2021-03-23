using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MySql.Data.MySqlClient;

namespace 数据库
{
    public partial class 登陆页面 : Form
    {
        public 登陆页面()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text == "")
            {
                MessageBox.Show("请输入用户名！", "提示");
            }
            else if (textBox2.Text == "")
            {
                MessageBox.Show("请输入密码！", "提示");
            }
            else
            {
                try
                {
                    MySqlConnection conn = new MySqlConnection("server=127.0.0.1;port=3306;user=" +
                        textBox1.Text + ";password=" + textBox2.Text + "; database=tsxs;");
                    conn.Open();
                    conn.Close();
                    主页面 b = new 主页面(textBox1.Text, textBox2.Text);
                    b.Show();
                    this.Hide();
                }
                catch
                {
                    MessageBox.Show("用户名或密码错误，请重新输入！", "提示");
                }
            }
        }
    }
}
