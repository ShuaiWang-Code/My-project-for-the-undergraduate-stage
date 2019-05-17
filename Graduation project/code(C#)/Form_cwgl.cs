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
    public partial class Form_cwgl : Form
    {
        public Form_cwgl()
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
        private void Form_cwgl_Load(object sender, EventArgs e)
        {
            conn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
            cmdd = new SqlCommand("select * from Space_Info", conn);
            sda = new SqlDataAdapter();
            sda.SelectCommand = cmdd;
            ds = new DataSet();
            sda.Fill(ds, "m");
            dataGridView1.DataSource = ds.Tables[0];

            if (App_Code.ShareClass.Type == "管理员")
            {
                button2.Visible = false;


            }
            else if (App_Code.ShareClass.Type == "超级管理员")
            {

                button2.Visible = true;


            }
            else
            {
                MessageBox.Show("管理员类型出错");
            }

            dataGridView1.Columns[0].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            dataGridView1.Columns[1].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            dataGridView1.Columns[2].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
        }
        /// <summary>
        /// 返回
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button3_Click(object sender, EventArgs e)
        {
            this.Close();
        }
        /// <summary>
        /// 刷新
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            conn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
            cmdd = new SqlCommand("select * from Space_Info", conn);
            sda = new SqlDataAdapter();
            sda.SelectCommand = cmdd;
            ds = new DataSet();
            sda.Fill(ds, "m");
            dataGridView1.DataSource = ds.Tables[0];
        }
        /// <summary>
        /// 删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            SqlConnection con;
            try
            {
                con = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmd = con.CreateCommand();
                con.Open();
                cmd.CommandText = "delete from Space_Info where 停入车辆车牌号 = @xingming";
                SqlParameter Xingming = new SqlParameter("@xingming", SqlDbType.NVarChar);
                cmd.Parameters.Add(Xingming);
                Xingming.Value = textBox4.Text.Trim();
                cmd.ExecuteNonQuery();
                login_cwxx();
                MessageBox.Show("删除成功，请刷新数据！");

                con.Close();
            }
            catch
            {
                MessageBox.Show("删除出错");
            }
        }
        /// <summary>
        /// 车位信息删除
        /// </summary>
        private void login_cwxx()
        {
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                cmddd.CommandText = "insert into System_Login(管理员姓名,时间,事件) values('注册用户','" + DateTime.Now.ToShortDateString() + "  " + DateTime.Now.ToLongTimeString() + "','车位信息删除')";
                cmddd.ExecuteNonQuery();
                //MessageBox.Show("注册成功！");

                connn.Close();
            }
            catch
            {
                MessageBox.Show("车位信息删除日志出错");
            } 
        }
        /// <summary>
        /// 选中到文本
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            textBox1.Text = dataGridView1.SelectedCells[0].Value.ToString();
            textBox2.Text = dataGridView1.SelectedCells[1].Value.ToString();
            textBox3.Text = dataGridView1.SelectedCells[2].Value.ToString();
            textBox4.Text = dataGridView1.SelectedCells[3].Value.ToString();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //Form_cwgl_ss frm1 = new Form_cwgl_ss();
            //frm1.Show();
            if (textBox5.Text != "")
            {
                conn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                cmdd = new SqlCommand("select * from Space_Info where " + comboBox1.Text + "=@name", conn);
                SqlParameter TName = new SqlParameter("@name", SqlDbType.NVarChar);
                cmdd.Parameters.Add(TName);
                TName.Value = textBox5.Text.Trim();
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
