using System;
using System.Data;
using System.Data.OleDb;
using System.Windows.Forms;

namespace 人体行为管理系统2
{
    public partial class 添加身体信息 : Form
    {
        OleDbDataAdapter add;
        DataTable dt, dt2;
        OleDbConnection conn;
        public 添加身体信息()
        {
            InitializeComponent();
        }

        private void TextBox2_TextChanged(object sender, EventArgs e)//当身高信息改变时改变BMI
        {
            if (textBox2.Text != "" && textBox3.Text != "")
            {
                try
                {
                    double a = double.Parse(textBox2.Text), b = double.Parse(textBox3.Text);
                    a = b / (a / 100) / (a / 100);
                    a = Math.Round(a, 1);
                    label11.Text = a.ToString();
                }
                catch(Exception ex)
                {
                    MessageBox.Show(ex.Message.ToString());
                }
            }
        }

        private void TextBox3_TextChanged(object sender, EventArgs e)//当体重信息改变时改变BMI
        {
            if (textBox2.Text != "" && textBox3.Text != "")
            {
                try
                {
                    double a = double.Parse(textBox2.Text), b = double.Parse(textBox3.Text);
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

        private void 添加身体信息_Load(object sender, EventArgs e)
        {
            label11.Text = "";
            conn = new OleDbConnection(@"Provider=Microsoft.Jet.OLEDB.4.0;Data Source=" + Application.StartupPath + @"\人体行为数据库管理系统.mdb");
            add = new OleDbDataAdapter("select * from 身体信息", conn);
            dt = new DataTable();
            dt2 = new DataTable();
            add.Fill(dt);
            add.Fill(dt2);
        }

        private void Button3_Click(object sender, EventArgs e)//点击“重置”按钮
        {
            textBox1.Text = textBox2.Text = textBox3.Text = textBox4.Text = textBox5.Text = textBox6.Text = textBox7.Text = textBox8.Text = textBox9.Text = "";
            label11.Text = "";
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
                    dt.Rows[i][3] = label11.Text;
                    dt.Rows[i][4] = textBox4.Text;
                    dt.Rows[i][5] = textBox5.Text;
                    dt.Rows[i][6] = textBox6.Text;
                    dt.Rows[i][7] = textBox7.Text;
                    dt.Rows[i][8] = textBox8.Text;
                    dt.Rows[i][9] = textBox9.Text;
                    OleDbCommandBuilder cmdb = new OleDbCommandBuilder(add);
                    add.Update(dt);
                    MessageBox.Show("保存成功!");
                    textBox1.Text = textBox2.Text = textBox3.Text = textBox4.Text = textBox5.Text = textBox6.Text = textBox7.Text = textBox8.Text = textBox9.Text = "";
                    label11.Text = "";
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
