using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace WindowsFormsApplication1
{
    public partial class Form_bfsjsd : Form
    {
        public Form_bfsjsd()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Form_bfsjsd_Load(object sender, EventArgs e)
        {
            textBox1.Text = App_Code.TimeClass.SHI.ToString();
            textBox2.Text = App_Code.TimeClass.FEN.ToString();
            textBox3.Text = App_Code.TimeClass.MIAO.ToString();

            if (App_Code.ShareClass.Type == "管理员")
            {
                button1.Visible = false;
                button2.Visible = false;
                //button4.Visible = false;


            }
            else if (App_Code.ShareClass.Type == "超级管理员")
            {

                button1.Visible = true;
                button2.Visible = true;
                //button4.Visible = true;


            }
            else
            {
                MessageBox.Show("管理员类型出错");
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if ((textBox1.Text != "") && (textBox2.Text != "") && (textBox3.Text != ""))
            {
                App_Code.TimeClass.SHI = Convert.ToInt32(textBox1.Text);
                App_Code.TimeClass.FEN = Convert.ToInt32(textBox2.Text);
                App_Code.TimeClass.MIAO = Convert.ToInt32(textBox3.Text);
                MessageBox.Show("设定成功");
                this.Close();
            }
            else
            {
                MessageBox.Show("不能为空！");
            }

        }
    }
}
