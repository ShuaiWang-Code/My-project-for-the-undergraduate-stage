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
    public partial class Form_cwgl_ss : Form
    {
        public Form_cwgl_ss()
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
        private void Form_cwgl_ss_Load(object sender, EventArgs e)
        {
            conn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
            cmdd = new SqlCommand("select * from Space_Info", conn);
            sda = new SqlDataAdapter();
            sda.SelectCommand = cmdd;
            ds = new DataSet();
            sda.Fill(ds, "m");
            dataGridView1.DataSource = ds.Tables[0]; 
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "")
            {
                conn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                cmdd = new SqlCommand("select * from Space_Info where 停入车辆车牌号=@name", conn);
                SqlParameter TName = new SqlParameter("@name", SqlDbType.NVarChar);
                cmdd.Parameters.Add(TName);
                TName.Value = textBox1.Text.Trim();
                sda = new SqlDataAdapter();
                sda.SelectCommand = cmdd;
                ds = new DataSet();
                sda.Fill(ds, "m");
                dataGridView1.DataSource = ds.Tables[0];

            }
            else
            {
                MessageBox.Show("搜索出错");
            }
        }
    }
}
