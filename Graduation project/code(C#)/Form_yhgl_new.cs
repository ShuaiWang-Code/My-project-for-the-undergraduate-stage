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
    public partial class Form_yhgl_new : Form
    {
        public Form_yhgl_new()
        {
            InitializeComponent();
        }
        /// <summary>
        /// 返回用户管理
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            //Form_yhgl frm1 = new Form_yhgl();
            this.Close();
            //frm1.Show();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SqlConnection con;
            try
            {
                con = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmd = con.CreateCommand();
                con.Open();
                cmd.CommandText = "insert into User_Management(姓名,车牌号,用户类别) values('" + textBox1.Text.Trim() + "','" + textBox2.Text.Trim() + "','" + comboBox1.Text.Trim() + "')";
                cmd.ExecuteNonQuery();

                new_login();
                MessageBox.Show("添加新用户成功");

                con.Close();
                this.Close();
            }
            catch
            {
                MessageBox.Show("添加新用户出错");
            }
            
        }
        /// <summary>
        /// 添加新用户日志
        /// </summary>
        private void new_login()
        {
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                cmddd.CommandText = "insert into System_Login(管理员姓名,时间,事件) values('" + App_Code.ShareClass.Name.Trim() + "','" + DateTime.Now.ToShortDateString() + "  " + DateTime.Now.ToLongTimeString() + "','添加新用户')";
                cmddd.ExecuteNonQuery();
                //MessageBox.Show("登录成功！");

                connn.Close();
            }
            catch
            {
                MessageBox.Show("添加新用户日志出错");
            } 
        }  
    }
}
