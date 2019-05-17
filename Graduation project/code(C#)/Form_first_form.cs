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
    public partial class Form_first_form : Form
    {
        public Form_first_form()
        {
            InitializeComponent();
        }
        /// <summary>
        /// 退出
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void linkLabel2_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            this.Close();
        }
        /// <summary>
        /// 登陆
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            Form1 frm1 = new Form1();
            frm1.Show();
            this.Hide();
            
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            sec++;
            huanying += dian;
            label1.Text = huanying;
            if (sec >= 5)
            {
                sec = 0;
                timer1.Enabled = false;
                Form1 frm1 = new Form1();
                frm1.Show();
                this.Hide();
            }
        }
        string huanying = "欢迎进入";
        string dian = ".";
        int sec;
        private void Form_first_form_Load(object sender, EventArgs e)
        {
            label1.Text = huanying;
        }
    }
}
