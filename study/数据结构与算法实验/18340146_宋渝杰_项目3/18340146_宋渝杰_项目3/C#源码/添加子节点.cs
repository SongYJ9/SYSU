using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace project_3
{
    public partial class 添加子节点 : Form
    {
        public 添加子节点()
        {
            InitializeComponent();
        }

        private void 添加子节点_Load(object sender, EventArgs e)
        {
            label1.Text = "正在给 " + data.name2 + " 添加子节点：";
            radioButton1.Checked = true;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if(textBox1.Text != "")
            {
                data.i = 1;
                data.name = textBox1.Text;
                if (radioButton1.Checked == true) data.isMan = true;
                else data.isMan = false;
                data.nianfen = (textBox2.Text.Length == 0 ? "None" : textBox2.Text);
                MessageBox.Show("添加成功!");
                this.Close();
            }
            else
            {
                MessageBox.Show("名字不能为空!");
            }
        }
    }
}
