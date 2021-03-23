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
    public partial class 主页面 : Form
    {
        MySqlConnection conn;
        public 主页面(string s1, string s2)
        {
            InitializeComponent();
            conn = new MySqlConnection("server=127.0.0.1;port=3306;user=" + s1 + ";password=" + s2 + "; database=tsxs;");
        }

        private void 主页面_Load(object sender, EventArgs e)
        {
            conn.Open();
            MySqlCommand mySqlCommand = new MySqlCommand("use tsxs;", conn);
            int result = mySqlCommand.ExecuteNonQuery();
            label3.Text = label5.Text = label7.Text = label9.Text = label11.Text = label14.Text = 
                label17.Text = label18.Text = label31.Text = label36.Text = "";
            mySqlCommand = new MySqlCommand("select bname from book;", conn);
            MySqlDataReader mdr = mySqlCommand.ExecuteReader();
            while (mdr.Read())
            {
                comboBox2.Items.Add(mdr.GetString("bname"));
                comboBox3.Items.Add(mdr.GetString("bname"));
                comboBox4.Items.Add(mdr.GetString("bname"));
            }
            mdr.Close();
            comboBox1.Items.Add("供应商A");
            comboBox1.Items.Add("供应商B");
            comboBox1.Items.Add("供应商C");
            comboBox2.SelectedIndex = 0;
            comboBox3.SelectedIndex = 0;
            comboBox4.SelectedIndex = 0;
            groupBox1.Visible = true;
            groupBox2.Visible = groupBox3.Visible = groupBox4.Visible = false;
        }

        private void 主页面_FormClosed(object sender, FormClosedEventArgs e)
        {
            conn.Close();
            System.Environment.Exit(0);
        }

        private void 进货ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            groupBox1.Visible = true;
            groupBox2.Visible = groupBox3.Visible = groupBox4.Visible = false;
            comboBox2.SelectedIndex = 1;
            comboBox2.SelectedIndex = 0;
        }

        private void 退货ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            groupBox2.Visible = true;
            groupBox1.Visible = groupBox3.Visible = groupBox4.Visible = false;
            comboBox3.SelectedIndex = 1;
            comboBox3.SelectedIndex = 0;
        }

        private void 统计ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            groupBox4.Visible = true;
            groupBox1.Visible = groupBox2.Visible = groupBox3.Visible = false;
            dateTimePicker1.Value = DateTime.Now.AddMonths(-1);
        }

        private void 销售ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            groupBox3.Visible = true;
            groupBox1.Visible = groupBox2.Visible = groupBox4.Visible = false;
            comboBox4.SelectedIndex = 1;
            comboBox4.SelectedIndex = 0;
        }

        private void comboBox2_TextChanged(object sender, EventArgs e) // 进货书本变化
        {
            MySqlCommand mySqlCommand;
            MySqlDataReader mdr;
            mySqlCommand = new MySqlCommand("select * from book where bname = '" + comboBox2.Text + "';", conn);
            mdr = mySqlCommand.ExecuteReader();
            while (mdr.Read())
            {
                label18.Text = mdr.GetString("bprice");
                label3.Text = mdr.GetString("bnum");
            }
            mdr.Close();
            mySqlCommand = new MySqlCommand("select sum(bnum) from record where species != 1 and bname = '" + comboBox2.Text + "';", conn);
            mdr = mySqlCommand.ExecuteReader();
            while (mdr.Read())
            {
                label5.Text = mdr.GetString("sum(bnum)");
            }
            mdr.Close();
            mySqlCommand = new MySqlCommand("select * from supplier where bname = '" + comboBox2.Text + "';", conn);
            mdr = mySqlCommand.ExecuteReader();
            while (mdr.Read())
            {
                if (mdr.GetString("sname") == "供应商A") label7.Text = mdr.GetString("sprice");
                if (mdr.GetString("sname") == "供应商B") label9.Text = mdr.GetString("sprice");
                if (mdr.GetString("sname") == "供应商C") label11.Text = mdr.GetString("sprice");
            }
            mdr.Close();
            comboBox1.SelectedIndex = 1;
            comboBox1.SelectedIndex = 0;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e) // 进货供应商变化
        {
            if (comboBox1.SelectedIndex == 0) label14.Text = label7.Text;
            if (comboBox1.SelectedIndex == 1) label14.Text = label9.Text;
            if (comboBox1.SelectedIndex == 2) label14.Text = label11.Text;
        }

        private void label14_TextChanged(object sender, EventArgs e) // 进货单价变化
        {
            if (textBox2.Text != "")
            {
                try
                {
                    label17.Text = (double.Parse(textBox2.Text) * double.Parse(label14.Text)).ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                    label17.Text = "";
                }
            }
        }

        private void textBox2_TextChanged(object sender, EventArgs e) // 进货数量变化
        {
            if (textBox2.Text != "")
            {
                try
                {
                    label17.Text = (double.Parse(textBox2.Text) * double.Parse(label14.Text)).ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                    label17.Text = "";
                }
            }
        }

        private void button1_Click(object sender, EventArgs e) // 确定进货
        {
            MySqlCommand mySqlCommand = new MySqlCommand("update book set bnum = bnum + " + textBox2.Text + " where bname = '" + comboBox2.Text + "';", conn);
            int result = mySqlCommand.ExecuteNonQuery();
            string s = DateTime.Now.ToString("yyyy-MM-dd-hh-mm-ss");
            mySqlCommand = new MySqlCommand("insert into record values('" + s + "', '" + comboBox2.Text + "', 1, " + label14.Text + ", " + textBox2.Text + ");", conn);
            result = mySqlCommand.ExecuteNonQuery();
            MessageBox.Show("进货时间：" + s + "\n" +
                "进货书籍：" + comboBox2.Text + "\n" + 
                "进货商：" + comboBox1.Text + "\n" + 
                "进货单价：" + label14.Text + "\n" +
                "进货数量：" + textBox2.Text + "\n" +
                "进货总价：" + label17.Text, "进货单");
            comboBox2.SelectedIndex = 1;
            comboBox2.SelectedIndex = 0;
        }

        private void comboBox3_SelectedIndexChanged(object sender, EventArgs e) // 退货书本变化
        {
            MySqlCommand mySqlCommand = new MySqlCommand("select * from book where bname = '" + comboBox3.Text + "';", conn);
            MySqlDataReader mdr = mySqlCommand.ExecuteReader();
            while (mdr.Read())
            {
                label21.Text = mdr.GetString("bprice");
                label33.Text = mdr.GetString("bnum");
            }
            mdr.Close();
        }

        private void label21_TextChanged(object sender, EventArgs e) // 退货单价变化
        {
            if (textBox1.Text != "")
            {
                try
                {
                    label36.Text = (double.Parse(textBox1.Text) * double.Parse(label21.Text)).ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                    label36.Text = "";
                }
            }
        }

        private void textBox1_TextChanged(object sender, EventArgs e) // 退货数量变化
        {
            if (textBox1.Text != "")
            {
                try
                {
                    label36.Text = (double.Parse(textBox1.Text) * double.Parse(label21.Text)).ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                    label36.Text = "";
                }
            }
        }

        private void button2_Click(object sender, EventArgs e) // 确定退货
        {
            MySqlCommand mySqlCommand = new MySqlCommand("update book set bnum = bnum + " + textBox1.Text + " where bname = '" + comboBox3.Text + "';", conn);
            int result = mySqlCommand.ExecuteNonQuery();
            string s = DateTime.Now.ToString("yyyy-MM-dd-hh-mm-ss");
            mySqlCommand = new MySqlCommand("insert into record values('" + s + "', '" + comboBox3.Text + "', 2, " + label21.Text + ", -" + textBox1.Text + ");", conn);
            result = mySqlCommand.ExecuteNonQuery();
            MessageBox.Show("退货时间：" + s + "\n" +
                "退货书籍：" + comboBox3.Text + "\n" +
                "退货单价：" + label21.Text + "\n" +
                "退货数量：" + textBox1.Text + "\n" +
                "退货总价：" + label36.Text, "退货单");
            comboBox3.SelectedIndex = 1;
            comboBox3.SelectedIndex = 0;
        }

        private void comboBox4_SelectedIndexChanged(object sender, EventArgs e) // 销售书本变化
        {
            MySqlCommand mySqlCommand = new MySqlCommand("select * from book where bname = '" + comboBox4.Text + "';", conn);
            MySqlDataReader mdr = mySqlCommand.ExecuteReader();
            while (mdr.Read())
            {
                label28.Text = mdr.GetString("bprice");
                label29.Text = mdr.GetString("bnum");
            }
            mdr.Close();
        }

        private void label28_TextChanged(object sender, EventArgs e) // 销售单价变化
        {
            if (textBox3.Text != "")
            {
                try
                {
                    label31.Text = (double.Parse(textBox3.Text) * double.Parse(label28.Text)).ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                    label31.Text = "";
                }
            }
        }

        private void textBox3_TextChanged(object sender, EventArgs e) // 销售数量变化
        {
            if (textBox3.Text != "")
            {
                try
                {
                    label31.Text = (double.Parse(textBox3.Text) * double.Parse(label28.Text)).ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                    label31.Text = "";
                }
            }
        }

        private void button3_Click(object sender, EventArgs e) // 确定销售
        {
            if (int.Parse(textBox3.Text) <= int.Parse(label29.Text))
            {
                MySqlCommand mySqlCommand = new MySqlCommand("update book set bnum = bnum - " + textBox3.Text + " where bname = '" + comboBox4.Text + "';", conn);
                int result = mySqlCommand.ExecuteNonQuery();
                string s = DateTime.Now.ToString("yyyy-MM-dd-hh-mm-ss");
                mySqlCommand = new MySqlCommand("insert into record values('" + s + "', '" + comboBox4.Text + "', 0, " + label28.Text + ", " + textBox3.Text + ");", conn);
                result = mySqlCommand.ExecuteNonQuery();
                MessageBox.Show("销售时间：" + s + "\n" +
                    "销售书籍：" + comboBox4.Text + "\n" +
                    "销售单价：" + label28.Text + "\n" +
                    "销售数量：" + textBox3.Text + "\n" +
                    "销售总价：" + label31.Text, "销售单");
                comboBox4.SelectedIndex = 1;
                comboBox4.SelectedIndex = 0;
            }
            else
            {
                MessageBox.Show("库存不足！", "警告");
            }
        }

        private void dateTimePicker1_ValueChanged(object sender, EventArgs e) // 统计
        {
            DataTable dt = new DataTable();
            dt.Columns.Add("书籍名称", typeof(String));
            dt.Columns.Add("进货量", typeof(int));
            dt.Columns.Add("进货总额", typeof(double));
            dt.Columns.Add("销售量", typeof(int));
            dt.Columns.Add("销售总额", typeof(double));
            dt.Columns.Add("净利润", typeof(double));
            MySqlCommand mySqlCommand = new MySqlCommand("select bname, sum(bnum), sum(bprice*bnum) from record where species = 1 and " +
                "stime >= '" + dateTimePicker1.Value.Year + "-" + dateTimePicker1.Value.Month + "-00-00-00-00' and " +
                "stime <= '" + dateTimePicker1.Value.Year + "-" + dateTimePicker1.Value.Month + "-31-23-59-59' group by bname order by bname;", conn);
            MySqlDataReader mdr = mySqlCommand.ExecuteReader();
            while (mdr.Read())
            {
                dt.Rows.Add();
                dt.Rows[dt.Rows.Count - 1][0] = mdr.GetString("bname");
                dt.Rows[dt.Rows.Count - 1][1] = mdr.GetInt32("sum(bnum)");
                dt.Rows[dt.Rows.Count - 1][2] = mdr.GetDouble("sum(bprice*bnum)");
            }
            mdr.Close();
            mySqlCommand = new MySqlCommand("select bname, sum(bnum), sum(bprice*bnum) from record where species != 1 and " +
                "stime >= '" + dateTimePicker1.Value.Year + "-" + dateTimePicker1.Value.Month + "-00-00-00-00' and " +
                "stime <= '" + dateTimePicker1.Value.Year + "-" + dateTimePicker1.Value.Month + "-31-23-59-59' group by bname order by bname;", conn);
            mdr = mySqlCommand.ExecuteReader();
            int i = 0, cou = -1;
            double sum = 0, ma = -1e6;
            while (mdr.Read())
            {
                dt.Rows[i][3] = mdr.GetInt32("sum(bnum)");
                dt.Rows[i][4] = mdr.GetDouble("sum(bprice*bnum)");
                i++;
            }
            mdr.Close();
            dataGridView1.DataSource = dt;
            for (i = 0; i < dt.Rows.Count; i++)
            {
                dt.Rows[i][5] = double.Parse(dt.Rows[i][4].ToString()) - double.Parse(dt.Rows[i][2].ToString());
                if (double.Parse(dt.Rows[i][5].ToString()) > ma)
                {
                    ma = double.Parse(dt.Rows[i][5].ToString());
                    cou = i;
                }
                sum += double.Parse(dt.Rows[i][5].ToString());
                dataGridView1.Rows[i].Height = 50;
            }
            if (cou != -1)
            {
                label38.Text = sum.ToString();
                label39.Text = dt.Rows[cou][0].ToString();
            }
            else
            {
                label38.Text = label39.Text = "";
            }
            for (i = 0; i < dataGridView1.Columns.Count; i++)
            {
                dataGridView1.Columns[i].Width = 70;
                //dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }
        }

        private void dataGridView1_Sorted(object sender, EventArgs e)
        {
            for (int i = 0; i < dataGridView1.Rows.Count; i++)
            {
                dataGridView1.Rows[i].Height = 50;
            }
        }
    }
}
