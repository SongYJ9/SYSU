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
    public partial class 主窗体 : Form
    {
        OleDbDataAdapter adp, add;
        DataTable dt;
        OleDbConnection conn;
        public 主窗体()
        {
            InitializeComponent();
        }

        private void 主窗体_Load(object sender, EventArgs e)
        {
            conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\人体行为数据库管理系统.mdb");//连接数据库
            this.toolStripStatusLabel2.Text = DateTime.Now.ToShortDateString();//右下角显示时间
            radioButton4.Checked = true;//选中“不显示”
        }

        private void RadioButton2_Click(object sender, EventArgs e)//选中“身体信息”单选框
        {
            if (radioButton2.Checked == true)
            {
                pictureBox1.Visible = false;
                dataGridView1.Visible = true;
                conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\人体行为数据库管理系统.mdb");
                add = new OleDbDataAdapter("select * from 身体信息", conn);
                dt = new DataTable();
                add.Fill(dt);
                dataGridView1.DataSource = dt;
                for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
                {
                    this.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
                }
            }
        }

        private void RadioButton3_Click(object sender, EventArgs e)//选中“健康问题信息”单选框
        {
            if (radioButton3.Checked == true)
            {
                pictureBox1.Visible = false;
                dataGridView1.Visible = true;
                conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\人体行为数据库管理系统.mdb");
                add = new OleDbDataAdapter("select * from 健康问题信息", conn);
                dt = new DataTable();
                add.Fill(dt);
                dataGridView1.DataSource = dt;
                for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
                {
                    this.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
                }
            }
        }

        private void DataGridView1_SelectionChanged(object sender, EventArgs e)//表格选中行改变
        {
            if (radioButton1.Checked == true)
            {
                try
                {
                    int index = dataGridView1.SelectedRows[0].Index;
                    pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + dataGridView1.Rows[index].Cells[6].Value.ToString());
                }
                catch { }
            }
        }

        private void 身体信息ToolStripMenuItem_Click(object sender, EventArgs e)//菜单栏选中“添加身体信息”
        {
            添加身体信息 a = new 添加身体信息();
            a.ShowDialog();
        }

        private void 基本个人信息ToolStripMenuItem_Click(object sender, EventArgs e)//菜单栏选中“添加基本个人信息”
        {
            添加基本个人信息 a = new 添加基本个人信息();
            a.ShowDialog();
        }

        private void 退出程序ToolStripMenuItem_Click(object sender, EventArgs e)//菜单栏选中“退出程序”
        {
            this.Close();
        }

        private void 健康问题信息ToolStripMenuItem_Click(object sender, EventArgs e)//菜单栏选中“添加健康问题信息”
        {
            添加健康问题信息 a = new 添加健康问题信息();
            a.ShowDialog();
        }

        private void ToolStripMenuItem1_Click(object sender, EventArgs e)//菜单栏选中“查询/修改数据”
        {
            查询修改数据 a = new 查询修改数据();
            a.ShowDialog();
        }

        private void 基本个人信息ToolStripMenuItem3_Click(object sender, EventArgs e)//菜单栏选中“删除单条数据”
        {
            删除数据 a = new 删除数据();
            a.ShowDialog();
        }

        private void 删除所有数据谨慎ToolStripMenuItem_Click(object sender, EventArgs e)//菜单栏选中“删除所有数据”
        {
            DialogResult dr = MessageBox.Show("是否删除所有数据？此过程无法撤销！！！", "警告:", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            if (dr == DialogResult.OK)   //如果单击“是”按钮
            {
                try
                {
                    conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\人体行为数据库管理系统.mdb");
                    adp = new OleDbDataAdapter("select * from 基本个人信息", conn);
                    dt = new DataTable();
                    adp.Fill(dt);
                    for(int i = 0; i < dt.Rows.Count; i++)
                    {
                        dataGridView1.Rows.Remove(dataGridView1.Rows[0]);
                    }
                    dt = (DataTable)dataGridView1.DataSource;
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(adp);
                    adp.Update(dt);//删除所有数据
                    pictureBox1.Image = null;
                    MessageBox.Show("删除成功！");
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                }
            }
        }

        private void 数据统计ToolStripMenuItem_Click(object sender, EventArgs e)//菜单栏选中“数据统计”
        {
            数据统计 a = new 数据统计();
            a.ShowDialog();
        }

        private void 主窗体_FormClosing(object sender, FormClosingEventArgs e)//即将关闭主窗口时
        {
            DialogResult dr = MessageBox.Show("是否退出?", "提示:", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);

            if (dr == DialogResult.OK)   //如果单击“是”按钮
            {
                e.Cancel = false;                 //关闭窗体
            }
            else if (dr == DialogResult.Cancel)
            {
                e.Cancel = true;                  //不执行操作
            }
        }

        private void 主窗体_FormClosed(object sender, FormClosedEventArgs e)//窗口关闭后关闭整个程序
        {
            Application.Exit();
        }

        private void RadioButton1_Click(object sender, EventArgs e)//选中“基本个人信息”单选框
        {
            if(radioButton1.Checked == true)
            {
                pictureBox1.Visible = true;
                dataGridView1.Visible = true;
                conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\人体行为数据库管理系统.mdb");
                add = new OleDbDataAdapter("select * from 基本个人信息", conn);
                dt = new DataTable();
                add.Fill(dt);
                dataGridView1.DataSource = dt;
                for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
                {
                    this.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
                }
                if(dataGridView1.Rows.Count > 1)
                {
                    pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + dataGridView1.Rows[0].Cells[6].Value.ToString());
                }
            }
        }

        private void RadioButton4_Click(object sender, EventArgs e)//选中“不显示”单选框
        {
            if (radioButton4.Checked == true)
            {
                dataGridView1.Visible = false;
                pictureBox1.Visible = false;
            }
        }
    }
}
