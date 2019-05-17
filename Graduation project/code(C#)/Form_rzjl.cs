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
    public partial class Form_rzjl : Form
    {
        public Form_rzjl()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form_system_login frm1 = new Form_system_login();
            frm1.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form_car_login frm2 = new Form_car_login();
            frm2.Show();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Form_beifen frm1 = new Form_beifen();
            frm1.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Form_huanyuan frm2 = new Form_huanyuan();
            frm2.Show();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Form_bfsjsd frm1 = new Form_bfsjsd();
            frm1.Show();
        }
    }
}
