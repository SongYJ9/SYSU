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
    public partial class 族谱 : Form
    {
        public struct node
        {
            public string name;
            public int beifen;
            public bool isMan;
            public string nianfen;
            public string father;
            public string son;
            public bool check;
        }
        int number = 6;

        List<node> l = new List<node>();

        public 族谱()
        {
            InitializeComponent();
        }

        public void find(TreeNode n,string name)
        {
            if (n.Text == name) {
                treeView1.SelectedNode = n;
                SendKeys.SendWait("{TAB}");
            }
            else
            {
                for (int i = 0; i < n.Nodes.Count; i++)
                {
                    find(n.Nodes[i], name);
                }
            }
        }

        public void delete(node n, List<node> l2)
        {
            int i, j, index = 0;
            node n2 = n;
            n2.check = false;
            for (i = 0; i < l2.Count; i++)
            {
                if(l2[i].name == n2.name)
                {
                    index = i;
                }
            }
            l[index] = n2;
            string[] str = n2.son.Split(' ');
            for (i = 0; i < str.Length; i++)
            {
                for (j = 0; j < l2.Count; j++)
                {
                    if(l2[j].name == str[i])
                    {
                        delete(l2[j],l2);
                    }
                }
            }
        }
        private void button1_Click(object sender, EventArgs e)// 点击“添加子节点”按钮
        {
            if(treeView1.SelectedNode == null)
            {
                MessageBox.Show("请选择要添加子节点的节点!");
            }
            else
            {
                添加子节点 a = new 添加子节点();
                data.name2 = treeView1.SelectedNode.Text;
                a.ShowDialog();
            }
        }

        private void 族谱_Load(object sender, EventArgs e)
        {
            timer1.Enabled = true;
            node n = new node();
            n.name = "第一代1号";
            n.beifen = 1;
            n.isMan = true;
            n.father = "None";
            n.son = "第二代1号 第二代2号 第二代3号";
            n.nianfen = "1930-2002";
            n.check = true;
            l.Add(n);
            n = new node();
            n.name = "第二代1号";
            n.beifen = 2;
            n.isMan = true;
            n.father = "第一代";
            n.son = "None";
            n.nianfen = "1958-";
            n.check = true;
            l.Add(n);
            n = new node();
            n.name = "第二代2号";
            n.beifen = 2;
            n.isMan = false;
            n.father = "第一代";
            n.son = "第三代1号 第三代2号";
            n.nianfen = "1960-2018";
            n.check = true;
            l.Add(n);
            n = new node();
            n.name = "第二代3号";
            n.beifen = 2;
            n.isMan = true;
            n.father = "第一代";
            n.son = "None";
            n.nianfen = "1962-";
            n.check = true;
            l.Add(n);
            n = new node();
            n.name = "第三代1号";
            n.beifen = 3;
            n.isMan = true;
            n.father = "第二代2号";
            n.son = "None";
            n.nianfen = "1985-1999";
            n.check = true;
            l.Add(n);
            n = new node();
            n.name = "第三代2号";
            n.beifen = 3;
            n.isMan = false;
            n.father = "第二代2号";
            n.son = "None";
            n.nianfen = "1988-";
            n.check = true;
            l.Add(n);
            treeView1.ExpandAll();
        }


        private void treeView1_AfterSelect(object sender, TreeViewEventArgs e)
        {
            int i = Int32.Parse(treeView1.SelectedNode.Name);
            textBox1.Text = l[i].name;
            textBox2.Text = l[i].beifen.ToString();
            textBox3.Text = l[i].isMan ? "男" : "女";
            textBox4.Text = l[i].nianfen;
            textBox6.Text = l[i].father;
            richTextBox1.Text = l[i].son;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if(data.i == 1)
            {
                int j = treeView1.SelectedNode.Nodes.Count;
                treeView1.SelectedNode.Nodes.Add(data.name);
                treeView1.SelectedNode.Nodes[j].Name = number.ToString();
                treeView1.SelectedNode.Nodes[j].Tag = Int32.Parse(treeView1.SelectedNode.Tag.ToString()) + 1;
                if (l[Int32.Parse(treeView1.SelectedNode.Name)].son == "None")
                {
                    node n2 = new node();
                    n2.name = l[Int32.Parse(treeView1.SelectedNode.Name)].name;
                    n2.beifen = l[Int32.Parse(treeView1.SelectedNode.Name)].beifen;
                    n2.isMan = l[Int32.Parse(treeView1.SelectedNode.Name)].isMan;
                    n2.father = l[Int32.Parse(treeView1.SelectedNode.Name)].father;
                    n2.son = data.name;
                    n2.nianfen = l[Int32.Parse(treeView1.SelectedNode.Name)].nianfen;
                    n2.check = true;
                    l[Int32.Parse(treeView1.SelectedNode.Name)] = n2;
                }
                else
                {
                    node n2 = new node();
                    n2.name = l[Int32.Parse(treeView1.SelectedNode.Name)].name;
                    n2.beifen = l[Int32.Parse(treeView1.SelectedNode.Name)].beifen;
                    n2.isMan = l[Int32.Parse(treeView1.SelectedNode.Name)].isMan;
                    n2.father = l[Int32.Parse(treeView1.SelectedNode.Name)].father;
                    n2.son = l[Int32.Parse(treeView1.SelectedNode.Name)].son + " " + data.name;
                    n2.check = true;
                    n2.nianfen = l[Int32.Parse(treeView1.SelectedNode.Name)].nianfen;
                    l[Int32.Parse(treeView1.SelectedNode.Name)] = n2;
                }
                treeView1.SelectedNode.Expand();
                number++;
                node n = new node();
                n.name = data.name;
                n.beifen = Int32.Parse(treeView1.SelectedNode.Tag.ToString()) + 1;
                n.isMan = data.isMan;
                n.father = treeView1.SelectedNode.Text;
                n.son = "None";
                n.nianfen = data.nianfen;
                n.check = true;
                l.Add(n);
                int i = Int32.Parse(treeView1.SelectedNode.Name);
                textBox1.Text = l[i].name;
                textBox2.Text = l[i].beifen.ToString();
                textBox3.Text = l[i].isMan ? "男" : "女";
                textBox4.Text = l[i].nianfen;
                textBox6.Text = l[i].father;
                richTextBox1.Text = l[i].son;
                data.i = 0;
            }
        }

        private void button2_Click(object sender, EventArgs e)// 点击“删除该节点”按钮
        {
            if (treeView1.SelectedNode == null)
            {
                MessageBox.Show("请选择要删除的节点！");
            }
            else if(treeView1.SelectedNode == treeView1.Nodes[0])
            {
                MessageBox.Show("不能删除根节点！");
            }
            else
            {
                DialogResult dr = MessageBox.Show("是否删除该节点？此过程无法撤销！！！\n注：该节点的所有子节点也会被删除", "警告:", MessageBoxButtons.OKCancel, MessageBoxIcon.Information);
                if (dr == DialogResult.OK)   //如果单击“是”按钮
                {
                    int index = 0, index2 = 0;
                    for(int i = 0; i < l.Count; i++)
                    {
                        if (l[i].son.Contains(treeView1.SelectedNode.Text))
                        {
                            index = i;
                        }
                    }
                    node nn = new node();
                    nn.name = l[index].name;
                    nn.beifen = l[index].beifen;
                    nn.isMan = l[index].isMan;
                    nn.father = l[index].father;
                    nn.check = true;
                    string[] str = l[index].son.Split(' ');
                    for(int i = 0; i < str.Length; i++)
                    {
                        if (str[i] == treeView1.SelectedNode.Text) index2 = i;
                    }
                    nn.son = "";
                    for(int i = 0; i < str.Length; i++)
                    {
                        if(i != index2)
                        {
                            if (i == 0) nn.son += str[i];
                            else if (nn.son != "")
                            {
                                nn.son = nn.son + " " + str[i];
                            }
                            else
                            {
                                nn.son = nn.son + str[i];
                            }
                        }
                    }
                    if (nn.son == "") nn.son = "None";
                    l[index] = nn;
                    for (int i = 0; i < l.Count; i++)
                    {
                        if (l[i].name.Contains(treeView1.SelectedNode.Text))
                        {
                            index = i;
                        }
                    }
                    delete(l[index], l);
                    treeView1.SelectedNode.Remove();
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)// 点击“搜索节点”按钮
        {
            find(treeView1.Nodes[0], textBox5.Text);
        }

        private void button4_Click(object sender, EventArgs e)// 点击“数据统计”按钮
        {
            string str = "  年龄         辈分      性别         生卒                子代：\n\n";
            for(int i = 0; i < l.Count; i++)
            {
                if(l[i].check == true)
                {
                    str = str + l[i].name + "    " + l[i].beifen.ToString() + "    " + (l[i].isMan ? "   Man     " : "Woman  ") + "" + l[i].nianfen + "            " + l[i].son + "\n";
                }
            }
            MessageBox.Show(str);
        }
    }
}
