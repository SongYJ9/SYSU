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
    public partial class 删除数据 : Form
    {
        OleDbDataAdapter adp;
        DataTable dt;
        OleDbConnection conn;

        public 删除数据()
        {
            InitializeComponent();
        }

        private void 删除数据_Load(object sender, EventArgs e)
        {
            conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\人体行为数据库管理系统.mdb");
            adp = new OleDbDataAdapter("select * from 基本个人信息", conn);
            dt = new DataTable();
            adp.Fill(dt);
            dataGridView1.DataSource = dt;
            radioButton1.Checked = true;
        }

        private void RadioButton1_CheckedChanged(object sender, EventArgs e)//点击“基本个人信息”单选框
        {
            if (radioButton1.Checked == true)
            {
                adp = new OleDbDataAdapter("select * from 基本个人信息", conn);
                dt = new DataTable();
                adp.Fill(dt);
                dataGridView1.DataSource = dt;
            }
        }

        private void RadioButton2_CheckedChanged(object sender, EventArgs e)//点击“身体信息”单选框
        {
            if (radioButton2.Checked == true)
            {
                adp = new OleDbDataAdapter("select * from 身体信息", conn);
                dt = new DataTable();
                adp.Fill(dt);
                dataGridView1.DataSource = dt;
            }
        }

        private void RadioButton3_CheckedChanged(object sender, EventArgs e)//点击“健康问题信息”单选框
        {
            if (radioButton3.Checked == true)
            {
                adp = new OleDbDataAdapter("select * from 健康问题信息", conn);
                dt = new DataTable();
                adp.Fill(dt);
                dataGridView1.DataSource = dt;
            }
        }

        private void Button1_Click(object sender, EventArgs e)//点击“删除选中行数据”按钮
        {
            DialogResult dr = MessageBox.Show("是否删除选中行数据？此过程无法撤销！\n注：如果删除“基本个人信息”表的数据，其他表的相关数据也会一起删除", "提示:", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
            if (dr == DialogResult.OK)   //如果单击“是”按钮
            {
                try
                {
                    foreach (DataGridViewRow r in dataGridView1.SelectedRows)//选中的行
                    {
                        this.dataGridView1.Rows.Remove(r);
                    }
                    var dt = (DataTable)dataGridView1.DataSource;
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(adp);
                    adp.Update(dt);
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                }
            }
        }
    }
}
