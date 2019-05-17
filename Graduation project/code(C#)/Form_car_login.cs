using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace WindowsFormsApplication1
{
    public partial class Form_car_login : Form
    {
        public Form_car_login()
        {
            InitializeComponent();
        }
        SqlCommand cmdd;
        SqlDataAdapter sda;
        SqlConnection conn;
        DataSet ds;
        /// <summary>
        /// 填充
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form_car_login_Load(object sender, EventArgs e)
        {
            conn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
            cmdd = new SqlCommand("select * from Car_Login", conn);
            sda = new SqlDataAdapter();
            sda.SelectCommand = cmdd;
            ds = new DataSet();
            sda.Fill(ds, "m");
            dataGridView1.DataSource = ds.Tables[0];
            dataGridView1.Columns[0].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            dataGridView1.Columns[1].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            dataGridView1.Columns[2].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
           
          
        }
    }
}
