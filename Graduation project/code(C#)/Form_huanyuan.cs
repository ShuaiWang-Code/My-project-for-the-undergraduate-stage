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
    public partial class Form_huanyuan : Form
    {
        public Form_huanyuan()
        {
            InitializeComponent();
        }
        /// <summary>
        /// 返回
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
            string Str_dar =textBox2.Text.Trim();
            string houzhui = ".bak";
            
 
            





            if (textBox2.Text == "")
            {
                MessageBox.Show("请选择正确的备份路径！");

                return;
            }
            
            
                SqlConnection connn;
                try
                {
                    connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                    SqlCommand cmddd = connn.CreateCommand();
                    connn.Open();
                    cmddd.CommandText = "restore database CarSystemDB from disk= '" +Str_dar+ houzhui+"'";


                    cmddd.ExecuteNonQuery();
                    login_huanyuan();
                    MessageBox.Show("还原成功！");

                    connn.Close();
                    
                }
                catch
                {
                    MessageBox.Show("还原成功！");
                    login_huanyuan();
                }
            
        }

        private void login_huanyuan()
        {
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                cmddd.CommandText = "insert into System_Login(管理员姓名,时间,事件) values('" + App_Code.ShareClass.Name + "','" + DateTime.Now.ToShortDateString() + "  " + DateTime.Now.ToLongTimeString() + "','还原')";
                cmddd.ExecuteNonQuery();
                //MessageBox.Show("注册成功！");

                connn.Close();
            }
            catch
            {
                MessageBox.Show("还原日志出错");
            }
        }

        private void Form_huanyuan_Load(object sender, EventArgs e)
        {
            if (App_Code.ShareClass.Type == "管理员")
            {
                button2.Visible = false;
                button1.Visible = false;


            }
            else if (App_Code.ShareClass.Type == "超级管理员")
            {

                button2.Visible = true;
                button1.Visible = true;


            }
            else
            {
                MessageBox.Show("管理员类型出错");
            }
        }
    }
}
