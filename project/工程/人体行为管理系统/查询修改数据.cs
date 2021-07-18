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
    public partial class 查询修改数据 : Form
    {
        OleDbDataAdapter adp,adq;
        DataTable dt,dt2;
        OleDbConnection conn;
        string str = "";
        string[] splits,splits2;
        OpenFileDialog dlgOpenFile;

        private void ComboBox1_SelectedIndexChanged(object sender, EventArgs e)//ComboBox页面发生变化
        {
            if(tabControl1.SelectedIndex != comboBox1.SelectedIndex)
            {
                tabControl1.SelectedIndex = comboBox1.SelectedIndex;//带动TabPage页面变化
            }
        }

        private void TabControl1_SelectedIndexChanged(object sender, EventArgs e)//TabPage页面发生变化
        {
            comboBox1.Text = tabControl1.SelectedTab.Text;//带动ComboBox页面变化
            textBox1.Text = "";
            adp = new OleDbDataAdapter("select 姓名 from " + comboBox1.Text, conn);
            adq = new OleDbDataAdapter("select * from " + comboBox1.Text, conn);
            dt = new DataTable();
            dt2 = new DataTable();
            adp.Fill(dt);
            adq.Fill(dt2);
            dataGridView1.DataSource = dt;
            for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
            {
                this.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;//列不可排序，以免datatable出现错误
            }
            if(dt.Rows.Count > 0)
            {
                textBox2.Text = dt.Rows[0][0].ToString();
            }
            textBox27.Text = dt.Rows.Count.ToString();
            if (comboBox1.SelectedIndex == 0 && dt.Rows.Count > 0)
            {
                textBox3.Text = dt2.Rows[0][0].ToString();
                if (dt2.Rows[0][1].ToString() == "男")
                {
                    radioButton1.Checked = true;
                }
                else if (dt2.Rows[0][1].ToString() == "女")
                {
                    radioButton2.Checked = true;
                }
                textBox4.Text = dt2.Rows[0][2].ToString();
                textBox5.Text = dt2.Rows[0][4].ToString();
                textBox6.Text = dt2.Rows[0][5].ToString();
                splits = dt2.Rows[0][3].ToString().Split(' ');
                textBox7.Text = splits[0];
                str = dt2.Rows[0][6].ToString();
                pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + dt2.Rows[0][6].ToString());
            }
            else if (comboBox1.SelectedIndex == 1 && dt.Rows.Count > 0)
            {
                textBox8.Text = dt2.Rows[0][0].ToString();
                textBox9.Text = dt2.Rows[0][1].ToString();
                textBox10.Text = dt2.Rows[0][2].ToString();
                label11.Text = dt2.Rows[0][3].ToString();
                textBox11.Text = dt2.Rows[0][4].ToString();
                textBox12.Text = dt2.Rows[0][5].ToString();
                textBox13.Text = dt2.Rows[0][6].ToString();
                textBox14.Text = dt2.Rows[0][7].ToString();
                textBox15.Text = dt2.Rows[0][8].ToString();
                textBox16.Text = dt2.Rows[0][9].ToString();
            }
            else if (comboBox1.SelectedIndex == 2 && dt.Rows.Count > 0)
            {
                textBox26.Text = dt2.Rows[0][0].ToString();
                textBox25.Text = dt2.Rows[0][1].ToString();
                textBox24.Text = dt2.Rows[0][2].ToString();
                textBox23.Text = dt2.Rows[0][3].ToString();
                textBox22.Text = dt2.Rows[0][4].ToString();
                textBox21.Text = dt2.Rows[0][5].ToString();
                textBox20.Text = dt2.Rows[0][6].ToString();
                textBox19.Text = dt2.Rows[0][7].ToString();
                textBox18.Text = dt2.Rows[0][8].ToString();
                textBox17.Text = dt2.Rows[0][9].ToString();
            }
        }

        private void Button9_Click(object sender, EventArgs e)//点击“查询”按钮
        {
            adp = new OleDbDataAdapter("select 姓名 from " + comboBox1.Text +" where 姓名 like '%" + textBox1.Text + "%'", conn);
            adq = new OleDbDataAdapter("select * from " + comboBox1.Text + " where 姓名 like '%" + textBox1.Text + "%'", conn);
            dt = new DataTable();
            dt2 = new DataTable();
            adp.Fill(dt);
            adq.Fill(dt2);
            textBox27.Text = dt.Rows.Count.ToString();
            if(textBox27.Text != "0")
            {
                dataGridView1.DataSource = dt;
                for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
                {
                    this.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
                }
                textBox2.Text = dt.Rows[0][0].ToString();
                if (comboBox1.SelectedIndex == 0 && dt.Rows.Count > 0)
                {
                    textBox3.Text = dt2.Rows[0][0].ToString();
                    if (dt2.Rows[0][1].ToString() == "男")
                    {
                        radioButton1.Checked = true;
                    }
                    else if (dt2.Rows[0][1].ToString() == "女")
                    {
                        radioButton2.Checked = true;
                    }
                    textBox4.Text = dt2.Rows[0][2].ToString();
                    textBox5.Text = dt2.Rows[0][4].ToString();
                    textBox6.Text = dt2.Rows[0][5].ToString();
                    splits = dt2.Rows[0][3].ToString().Split(' ');
                    textBox7.Text = splits[0];
                    str = dt2.Rows[0][6].ToString();
                    pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + dt2.Rows[0][6].ToString());
                }
                else if (comboBox1.SelectedIndex == 1 && dt.Rows.Count > 0)
                {
                    textBox8.Text = dt2.Rows[0][0].ToString();
                    textBox9.Text = dt2.Rows[0][1].ToString();
                    textBox10.Text = dt2.Rows[0][2].ToString();
                    label11.Text = dt2.Rows[0][3].ToString();
                    textBox11.Text = dt2.Rows[0][4].ToString();
                    textBox12.Text = dt2.Rows[0][5].ToString();
                    textBox13.Text = dt2.Rows[0][6].ToString();
                    textBox14.Text = dt2.Rows[0][7].ToString();
                    textBox15.Text = dt2.Rows[0][8].ToString();
                    textBox16.Text = dt2.Rows[0][9].ToString();
                }
                else if (comboBox1.SelectedIndex == 2 && dt.Rows.Count > 0)
                {
                    textBox26.Text = dt2.Rows[0][0].ToString();
                    textBox25.Text = dt2.Rows[0][1].ToString();
                    textBox24.Text = dt2.Rows[0][2].ToString();
                    textBox23.Text = dt2.Rows[0][3].ToString();
                    textBox22.Text = dt2.Rows[0][4].ToString();
                    textBox21.Text = dt2.Rows[0][5].ToString();
                    textBox20.Text = dt2.Rows[0][6].ToString();
                    textBox19.Text = dt2.Rows[0][7].ToString();
                    textBox18.Text = dt2.Rows[0][8].ToString();
                    textBox17.Text = dt2.Rows[0][9].ToString();
                }
            }
            else
            {
                MessageBox.Show("无查询记录");
                adp = new OleDbDataAdapter("select 姓名 from " + comboBox1.Text, conn);
                adq = new OleDbDataAdapter("select * from " + comboBox1.Text, conn);
                dt = new DataTable();
                dt2 = new DataTable();
                adp.Fill(dt);
                adq.Fill(dt2);
                dataGridView1.DataSource = dt;
                for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
                {
                    this.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
                }
                if (dt.Rows.Count > 0)
                {
                    textBox2.Text = dt.Rows[0][0].ToString();
                }
                textBox27.Text = dt.Rows.Count.ToString();
                if (comboBox1.SelectedIndex == 0 && dt.Rows.Count > 0)
                {
                    textBox3.Text = dt2.Rows[0][0].ToString();
                    if (dt2.Rows[0][1].ToString() == "男")
                    {
                        radioButton1.Checked = true;
                    }
                    else if (dt2.Rows[0][1].ToString() == "女")
                    {
                        radioButton2.Checked = true;
                    }
                    textBox4.Text = dt2.Rows[0][2].ToString();
                    textBox5.Text = dt2.Rows[0][4].ToString();
                    textBox6.Text = dt2.Rows[0][5].ToString();
                    splits = dt2.Rows[0][3].ToString().Split(' ');
                    textBox7.Text = splits[0];
                    str = dt2.Rows[0][6].ToString();
                    pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + dt2.Rows[0][6].ToString());
                }
                else if (comboBox1.SelectedIndex == 1 && dt.Rows.Count > 0)
                {
                    textBox8.Text = dt2.Rows[0][0].ToString();
                    textBox9.Text = dt2.Rows[0][1].ToString();
                    textBox10.Text = dt2.Rows[0][2].ToString();
                    label11.Text = dt2.Rows[0][3].ToString();
                    textBox11.Text = dt2.Rows[0][4].ToString();
                    textBox12.Text = dt2.Rows[0][5].ToString();
                    textBox13.Text = dt2.Rows[0][6].ToString();
                    textBox14.Text = dt2.Rows[0][7].ToString();
                    textBox15.Text = dt2.Rows[0][8].ToString();
                    textBox16.Text = dt2.Rows[0][9].ToString();
                }
                else if (comboBox1.SelectedIndex == 2 && dt.Rows.Count > 0)
                {
                    textBox26.Text = dt2.Rows[0][0].ToString();
                    textBox25.Text = dt2.Rows[0][1].ToString();
                    textBox24.Text = dt2.Rows[0][2].ToString();
                    textBox23.Text = dt2.Rows[0][3].ToString();
                    textBox22.Text = dt2.Rows[0][4].ToString();
                    textBox21.Text = dt2.Rows[0][5].ToString();
                    textBox20.Text = dt2.Rows[0][6].ToString();
                    textBox19.Text = dt2.Rows[0][7].ToString();
                    textBox18.Text = dt2.Rows[0][8].ToString();
                    textBox17.Text = dt2.Rows[0][9].ToString();
                }
            }
        }

        public 查询修改数据()
        {
            InitializeComponent();
        }

        private void DataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)//点击表的单元格时
        {
            int r = e.RowIndex;
            if(r<dt.Rows.Count && r >= 0)
            {
                textBox2.Text = dt.Rows[r][0].ToString();
                textBox27.Text = dt.Rows.Count.ToString();
                if (comboBox1.SelectedIndex == 0 && dt.Rows.Count > 0)
                {
                    textBox3.Text = dt2.Rows[r][0].ToString();
                    if (dt2.Rows[r][1].ToString() == "男")
                    {
                        radioButton1.Checked = true;
                    }
                    else if (dt2.Rows[r][1].ToString() == "女")
                    {
                        radioButton2.Checked = true;
                    }
                    textBox4.Text = dt2.Rows[r][2].ToString();
                    textBox5.Text = dt2.Rows[r][4].ToString();
                    textBox6.Text = dt2.Rows[r][5].ToString();
                    splits = dt2.Rows[r][3].ToString().Split(' ');
                    textBox7.Text = splits[0];
                    str = dt2.Rows[r][6].ToString();
                    pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + dt2.Rows[r][6].ToString());
                }
                else if (comboBox1.SelectedIndex == 1 && dt.Rows.Count > 0)
                {
                    textBox8.Text = dt2.Rows[r][0].ToString();
                    textBox9.Text = dt2.Rows[r][1].ToString();
                    textBox10.Text = dt2.Rows[r][2].ToString();
                    label11.Text = dt2.Rows[r][3].ToString();
                    textBox11.Text = dt2.Rows[r][4].ToString();
                    textBox12.Text = dt2.Rows[r][5].ToString();
                    textBox13.Text = dt2.Rows[r][6].ToString();
                    textBox14.Text = dt2.Rows[r][7].ToString();
                    textBox15.Text = dt2.Rows[r][8].ToString();
                    textBox16.Text = dt2.Rows[r][9].ToString();
                }
                else if (comboBox1.SelectedIndex == 2 && dt.Rows.Count > 0)
                {
                    textBox26.Text = dt2.Rows[r][0].ToString();
                    textBox25.Text = dt2.Rows[r][1].ToString();
                    textBox24.Text = dt2.Rows[r][2].ToString();
                    textBox23.Text = dt2.Rows[r][3].ToString();
                    textBox22.Text = dt2.Rows[r][4].ToString();
                    textBox21.Text = dt2.Rows[r][5].ToString();
                    textBox20.Text = dt2.Rows[r][6].ToString();
                    textBox19.Text = dt2.Rows[r][7].ToString();
                    textBox18.Text = dt2.Rows[r][8].ToString();
                    textBox17.Text = dt2.Rows[r][9].ToString();
                }
            }
        }

        private void Button7_Click(object sender, EventArgs e)//点击“上一页”按钮
        {
            try
            {
                if (dataGridView1.CurrentRow.Index > 0)//如果不是第一条数据
                {
                    dataGridView1.CurrentCell = dataGridView1[0, dataGridView1.CurrentCell.RowIndex - 1];
                    int r = dataGridView1.CurrentCell.RowIndex;
                    if (r < dt.Rows.Count)
                    {
                        textBox2.Text = dt.Rows[r][0].ToString();
                        textBox27.Text = dt.Rows.Count.ToString();
                        if (comboBox1.SelectedIndex == 0 && dt.Rows.Count > 0)
                        {
                            textBox3.Text = dt2.Rows[r][0].ToString();
                            if (dt2.Rows[r][1].ToString() == "男")
                            {
                                radioButton1.Checked = true;
                            }
                            else if (dt2.Rows[r][1].ToString() == "女")
                            {
                                radioButton2.Checked = true;
                            }
                            textBox4.Text = dt2.Rows[r][2].ToString();
                            textBox5.Text = dt2.Rows[r][4].ToString();
                            textBox6.Text = dt2.Rows[r][5].ToString();
                            splits = dt2.Rows[r][3].ToString().Split(' ');
                            textBox7.Text = splits[0];
                            str = dt2.Rows[r][6].ToString();
                            pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + dt2.Rows[r][6].ToString());
                        }
                        else if (comboBox1.SelectedIndex == 1 && dt.Rows.Count > 0)
                        {
                            textBox8.Text = dt2.Rows[r][0].ToString();
                            textBox9.Text = dt2.Rows[r][1].ToString();
                            textBox10.Text = dt2.Rows[r][2].ToString();
                            label11.Text = dt2.Rows[r][3].ToString();
                            textBox11.Text = dt2.Rows[r][4].ToString();
                            textBox12.Text = dt2.Rows[r][5].ToString();
                            textBox13.Text = dt2.Rows[r][6].ToString();
                            textBox14.Text = dt2.Rows[r][7].ToString();
                            textBox15.Text = dt2.Rows[r][8].ToString();
                            textBox16.Text = dt2.Rows[r][9].ToString();
                        }
                        else if (comboBox1.SelectedIndex == 2 && dt.Rows.Count > 0)
                        {
                            textBox26.Text = dt2.Rows[r][0].ToString();
                            textBox25.Text = dt2.Rows[r][1].ToString();
                            textBox24.Text = dt2.Rows[r][2].ToString();
                            textBox23.Text = dt2.Rows[r][3].ToString();
                            textBox22.Text = dt2.Rows[r][4].ToString();
                            textBox21.Text = dt2.Rows[r][5].ToString();
                            textBox20.Text = dt2.Rows[r][6].ToString();
                            textBox19.Text = dt2.Rows[r][7].ToString();
                            textBox18.Text = dt2.Rows[r][8].ToString();
                            textBox17.Text = dt2.Rows[r][9].ToString();
                        }
                    }
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
            }
        }

        private void Button8_Click(object sender, EventArgs e)//点击“下一页”按钮
        {
            try
            {
                if (dataGridView1.CurrentRow.Index < dt.Rows.Count - 1)//如果不是最后一条数据
                {
                    dataGridView1.CurrentCell = dataGridView1[0, dataGridView1.CurrentCell.RowIndex + 1];
                    int r = dataGridView1.CurrentCell.RowIndex;
                    if (r < dt.Rows.Count)
                    {
                        textBox2.Text = dt.Rows[r][0].ToString();
                        textBox27.Text = dt.Rows.Count.ToString();
                        if (comboBox1.SelectedIndex == 0 && dt.Rows.Count > 0)
                        {
                            textBox3.Text = dt2.Rows[r][0].ToString();
                            if (dt2.Rows[r][1].ToString() == "男")
                            {
                                radioButton1.Checked = true;
                            }
                            else if (dt2.Rows[r][1].ToString() == "女")
                            {
                                radioButton2.Checked = true;
                            }
                            textBox4.Text = dt2.Rows[r][2].ToString();
                            textBox5.Text = dt2.Rows[r][4].ToString();
                            textBox6.Text = dt2.Rows[r][5].ToString();
                            splits = dt2.Rows[r][3].ToString().Split(' ');
                            textBox7.Text = splits[0];
                            str = dt2.Rows[r][6].ToString();
                            pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + dt2.Rows[r][6].ToString());
                        }
                        else if (comboBox1.SelectedIndex == 1 && dt.Rows.Count > 0)
                        {
                            textBox8.Text = dt2.Rows[r][0].ToString();
                            textBox9.Text = dt2.Rows[r][1].ToString();
                            textBox10.Text = dt2.Rows[r][2].ToString();
                            label11.Text = dt2.Rows[r][3].ToString();
                            textBox11.Text = dt2.Rows[r][4].ToString();
                            textBox12.Text = dt2.Rows[r][5].ToString();
                            textBox13.Text = dt2.Rows[r][6].ToString();
                            textBox14.Text = dt2.Rows[r][7].ToString();
                            textBox15.Text = dt2.Rows[r][8].ToString();
                            textBox16.Text = dt2.Rows[r][9].ToString();
                        }
                        else if (comboBox1.SelectedIndex == 2 && dt.Rows.Count > 0)
                        {
                            textBox26.Text = dt2.Rows[r][0].ToString();
                            textBox25.Text = dt2.Rows[r][1].ToString();
                            textBox24.Text = dt2.Rows[r][2].ToString();
                            textBox23.Text = dt2.Rows[r][3].ToString();
                            textBox22.Text = dt2.Rows[r][4].ToString();
                            textBox21.Text = dt2.Rows[r][5].ToString();
                            textBox20.Text = dt2.Rows[r][6].ToString();
                            textBox19.Text = dt2.Rows[r][7].ToString();
                            textBox18.Text = dt2.Rows[r][8].ToString();
                            textBox17.Text = dt2.Rows[r][9].ToString();
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
            }
        }

        private void Button4_Click(object sender, EventArgs e)//点击“取消”按钮
        {
            this.Dispose();
        }

        private void Button3_Click(object sender, EventArgs e)//点击“重置”按钮
        {
            int r;
            if (dt.Rows.Count > 0)
            {
                r = dataGridView1.CurrentCell.RowIndex;
            }
            else
            {
                r = -1;
            }
            if (r < dt.Rows.Count)
            {
                textBox27.Text = dt.Rows.Count.ToString();
                if (comboBox1.SelectedIndex == 0 && dt.Rows.Count > 0)
                {
                    textBox3.Text = dt2.Rows[r][0].ToString();
                    if (dt2.Rows[r][1].ToString() == "男")
                    {
                        radioButton1.Checked = true;
                    }
                    else if (dt2.Rows[r][1].ToString() == "女")
                    {
                        radioButton2.Checked = true;
                    }
                    textBox4.Text = dt2.Rows[r][2].ToString();
                    textBox5.Text = dt2.Rows[r][4].ToString();
                    textBox6.Text = dt2.Rows[r][5].ToString();
                    splits = dt2.Rows[r][3].ToString().Split(' ');
                    textBox7.Text = splits[0];
                    str = dt2.Rows[r][6].ToString();
                    pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + dt2.Rows[r][6].ToString());
                }
                else if (comboBox1.SelectedIndex == 1 && dt.Rows.Count > 0)
                {
                    textBox8.Text = dt2.Rows[r][0].ToString();
                    textBox9.Text = dt2.Rows[r][1].ToString();
                    textBox10.Text = dt2.Rows[r][2].ToString();
                    label11.Text = dt2.Rows[r][3].ToString();
                    textBox11.Text = dt2.Rows[r][4].ToString();
                    textBox12.Text = dt2.Rows[r][5].ToString();
                    textBox13.Text = dt2.Rows[r][6].ToString();
                    textBox14.Text = dt2.Rows[r][7].ToString();
                    textBox15.Text = dt2.Rows[r][8].ToString();
                    textBox16.Text = dt2.Rows[r][9].ToString();
                }
                else if (comboBox1.SelectedIndex == 2 && dt.Rows.Count > 0)
                {
                    textBox26.Text = dt2.Rows[r][0].ToString();
                    textBox25.Text = dt2.Rows[r][1].ToString();
                    textBox24.Text = dt2.Rows[r][2].ToString();
                    textBox23.Text = dt2.Rows[r][3].ToString();
                    textBox22.Text = dt2.Rows[r][4].ToString();
                    textBox21.Text = dt2.Rows[r][5].ToString();
                    textBox20.Text = dt2.Rows[r][6].ToString();
                    textBox19.Text = dt2.Rows[r][7].ToString();
                    textBox18.Text = dt2.Rows[r][8].ToString();
                    textBox17.Text = dt2.Rows[r][9].ToString();
                }
            }
        }

        private void Button6_Click(object sender, EventArgs e)//点击“清除”按钮
        {
            str = "";
            pictureBox1.Image = null;
        }

        private void Button5_Click(object sender, EventArgs e)//点击“修改”按钮
        {
            try
            {
                int r = dataGridView1.CurrentCell.RowIndex;
                if (comboBox1.SelectedIndex == 0)
                {
                    dt2.Rows[r][0] = textBox3.Text;
                    if (radioButton1.Checked == true)
                    {
                        dt2.Rows[r][1] = "男";
                    }
                    else
                    {
                        dt2.Rows[r][1] = "女";
                    }
                    dt2.Rows[r][2] = textBox4.Text;
                    dt2.Rows[r][4] = textBox5.Text;
                    dt2.Rows[r][5] = textBox6.Text;
                    dt2.Rows[r][3] = textBox7.Text;
                    dt2.Rows[r][6] = str;
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(adq);
                    adq.Update(dt2);
                    MessageBox.Show("保存成功!");
                }
                else if (comboBox1.SelectedIndex == 1)
                {
                    dt2.Rows[r][0] = textBox8.Text;
                    dt2.Rows[r][1] = textBox9.Text;
                    dt2.Rows[r][2] = textBox10.Text;
                    dt2.Rows[r][3] = label11.Text;
                    dt2.Rows[r][4] = textBox11.Text;
                    dt2.Rows[r][5] = textBox12.Text;
                    dt2.Rows[r][6] = textBox13.Text;
                    dt2.Rows[r][7] = textBox14.Text;
                    dt2.Rows[r][8] = textBox15.Text;
                    dt2.Rows[r][9] = textBox16.Text;
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(adq);
                    adq.Update(dt2);
                    MessageBox.Show("保存成功!");
                }
                else if (comboBox1.SelectedIndex == 2)
                {
                    dt2.Rows[r][0] = textBox26.Text;
                    dt2.Rows[r][1] = textBox25.Text;
                    dt2.Rows[r][2] = textBox24.Text;
                    dt2.Rows[r][3] = textBox23.Text;
                    dt2.Rows[r][4] = textBox22.Text;
                    dt2.Rows[r][5] = textBox21.Text;
                    dt2.Rows[r][6] = textBox20.Text;
                    dt2.Rows[r][7] = textBox19.Text;
                    dt2.Rows[r][8] = textBox18.Text;
                    dt2.Rows[r][9] = textBox17.Text;
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(adq);
                    adq.Update(dt2);
                    MessageBox.Show("保存成功!");
                }
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message.ToString());
                adq = new OleDbDataAdapter("select * from " + comboBox1.Text + " where 姓名 like '%" + textBox1.Text + "%'", conn);
                adq.Fill(dt2);
            }
        }

        private void TextBox9_TextChanged(object sender, EventArgs e)//当身高信息改变时改变BMI
        {
            if (textBox9.Text != "" && textBox10.Text != "")
            {
                try
                {
                    double a = double.Parse(textBox9.Text), b = double.Parse(textBox10.Text);
                    a = b / (a / 100) / (a / 100);
                    a = Math.Round(a, 1);
                    label11.Text = a.ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                }
            }
        }

        private void TextBox10_TextChanged(object sender, EventArgs e)//当体重信息改变时改变BMI
        {
            if (textBox9.Text != "" && textBox10.Text != "")
            {
                try
                {
                    double a = double.Parse(textBox9.Text), b = double.Parse(textBox10.Text);
                    a = b / (a / 100) / (a / 100);
                    a = Math.Round(a, 1);
                    label11.Text = a.ToString();
                }
                catch (Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                }
            }
        }

        private void Button2_Click(object sender, EventArgs e)//点击“选择图片”按钮
        {
            dlgOpenFile = new OpenFileDialog { Filter = "图片(*.jpg)|*.jpg|图片(*.jpeg)|*.jpeg|图片(*.png)|*.png" };
            if (dlgOpenFile.ShowDialog() == DialogResult.OK) //OK表示按下了“打开”
            {
                splits2 = dlgOpenFile.FileName.Split('\\');
                str = splits2[splits2.Length - 1];
                pictureBox1.LoadAsync(dlgOpenFile.FileName);
                try
                {
                    File.Copy(dlgOpenFile.FileName, Application.StartupPath + @"\photos\" + splits[splits.Length - 1]);
                }
                catch { }
            }
        }

        private void 查询修改数据_Load(object sender, EventArgs e)
        {
            comboBox1.Text = "基本个人信息";
            conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\人体行为数据库管理系统.mdb");
            adp = new OleDbDataAdapter("select 姓名 from " + comboBox1.Text, conn);
            adq = new OleDbDataAdapter("select * from " + comboBox1.Text, conn);
            dt = new DataTable();
            dt2 = new DataTable();
            adp.Fill(dt);
            adq.Fill(dt2);
            dataGridView1.DataSource = dt;
            for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
            {
                this.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }
            textBox27.Text = dt.Rows.Count.ToString();
            if(dt.Rows.Count > 0)
            {
                textBox2.Text = dt.Rows[0][0].ToString();
                textBox3.Text = dt2.Rows[0][0].ToString();
                if (dt2.Rows[0][1].ToString() == "男")
                {
                    radioButton1.Checked = true;
                }
                else if (dt2.Rows[0][1].ToString() == "女")
                {
                    radioButton2.Checked = true;
                }
                textBox4.Text = dt2.Rows[0][2].ToString();
                textBox5.Text = dt2.Rows[0][4].ToString();
                textBox6.Text = dt2.Rows[0][5].ToString();
                splits = dt2.Rows[0][3].ToString().Split(' ');
                textBox7.Text = splits[0];
                str = dt2.Rows[0][6].ToString();
                pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + dt2.Rows[0][6].ToString());
            }
        }

        private void Button1_Click(object sender, EventArgs e)//点击“显示所有数据”按钮
        {
            adp = new OleDbDataAdapter("select 姓名 from " + comboBox1.Text, conn);
            adq = new OleDbDataAdapter("select * from " + comboBox1.Text, conn);
            dt = new DataTable();
            dt2 = new DataTable();
            adp.Fill(dt);
            adq.Fill(dt2);
            dataGridView1.DataSource = dt;
            for (int i = 0; i < this.dataGridView1.Columns.Count; i++)
            {
                this.dataGridView1.Columns[i].SortMode = DataGridViewColumnSortMode.NotSortable;
            }
            textBox1.Text = "";
            if (dt.Rows.Count > 0)
            {
                textBox2.Text = dt.Rows[0][0].ToString();
            }
            textBox27.Text = dt.Rows.Count.ToString();
            if (comboBox1.SelectedIndex == 0 && dt.Rows.Count > 0)
            {
                textBox3.Text = dt2.Rows[0][0].ToString();
                if (dt2.Rows[0][1].ToString() == "男")
                {
                    radioButton1.Checked = true;
                }
                else if (dt2.Rows[0][1].ToString() == "女")
                {
                    radioButton2.Checked = true;
                }
                textBox4.Text = dt2.Rows[0][2].ToString();
                textBox5.Text = dt2.Rows[0][4].ToString();
                textBox6.Text = dt2.Rows[0][5].ToString();
                splits = dt2.Rows[0][3].ToString().Split(' ');
                textBox7.Text = splits[0];
                str = dt2.Rows[0][6].ToString();
                pictureBox1.LoadAsync(Application.StartupPath + @"\photos\" + dt2.Rows[0][6].ToString());
            }
            else if (comboBox1.SelectedIndex == 1 && dt.Rows.Count > 0)
            {
                textBox8.Text = dt2.Rows[0][0].ToString();
                textBox9.Text = dt2.Rows[0][1].ToString();
                textBox10.Text = dt2.Rows[0][2].ToString();
                label11.Text = dt2.Rows[0][3].ToString();
                textBox11.Text = dt2.Rows[0][4].ToString();
                textBox12.Text = dt2.Rows[0][5].ToString();
                textBox13.Text = dt2.Rows[0][6].ToString();
                textBox14.Text = dt2.Rows[0][7].ToString();
                textBox15.Text = dt2.Rows[0][8].ToString();
                textBox16.Text = dt2.Rows[0][9].ToString();
            }
            else if (comboBox1.SelectedIndex == 2 && dt.Rows.Count > 0)
            {
                textBox26.Text = dt2.Rows[0][0].ToString();
                textBox25.Text = dt2.Rows[0][1].ToString();
                textBox24.Text = dt2.Rows[0][2].ToString();
                textBox23.Text = dt2.Rows[0][3].ToString();
                textBox22.Text = dt2.Rows[0][4].ToString();
                textBox21.Text = dt2.Rows[0][5].ToString();
                textBox20.Text = dt2.Rows[0][6].ToString();
                textBox19.Text = dt2.Rows[0][7].ToString();
                textBox18.Text = dt2.Rows[0][8].ToString();
                textBox17.Text = dt2.Rows[0][9].ToString();
            }
        }
    }
}
