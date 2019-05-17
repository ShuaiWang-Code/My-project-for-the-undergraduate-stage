using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.SqlClient;
using System.Globalization;

namespace WindowsFormsApplication1
{
    public partial class Form_beifen : Form
    {
        public Form_beifen()
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
        /// <summary>
        /// 备份
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            string Str_dar1 = "";
            string Str_dar = "";
            string houzhui = ".bak";
            string SaveFileName = DateTime.Now.Date.ToString("yyyy", DateTimeFormatInfo.InvariantInfo) +"年"+ DateTime.Now.Date.ToString("MM", DateTimeFormatInfo.InvariantInfo)+"月";
            SaveFileName += DateTime.Now.Date.ToString("dd", DateTimeFormatInfo.InvariantInfo) + "日" + DateTime.Now.ToString("HH", DateTimeFormatInfo.InvariantInfo) ;
            SaveFileName += "点"+DateTime.Now.ToString("mm", DateTimeFormatInfo.InvariantInfo) +"分"+ DateTime.Now.ToString("ss", DateTimeFormatInfo.InvariantInfo)+"秒";
            
            
            if (radioButton1.Checked == true)
            {
                Str_dar1 = "C:\\Users\\W\\Desktop\\";
                Str_dar = textBox1.Text.Trim();
                
            }

            if (radioButton2.Checked == true)
            {
                Str_dar1 = textBox2.Text.Trim();
                Str_dar = "";
            }

            if ((radioButton2.Checked == true) && (textBox2.Text == ""))
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
                //cmddd.CommandText = "backup database CarSystemDB to disk='"+"C:\\Users\\W\\Desktop"+Str_dar+".bat"+"'";
                //cmddd.CommandText = "backup database CarSystemDB to disk='C:\\Users\\W\\Desktop\\Test2.bak'";
                //cmddd.CommandText = "backup database CarSystemDB to disk='"+Str_dar+"'";
                
                cmddd.CommandText = "backup database CarSystemDB to disk= '" + Str_dar1+Str_dar +SaveFileName+ houzhui + "'";

                
                cmddd.ExecuteNonQuery();
                
                MessageBox.Show("备份成功！");

                connn.Close();
                login_beifen();
            }
            catch
            {
                    MessageBox.Show("备份失败！");
            }
            
        }
        /// <summary>
        /// 备份
        /// </summary>
        private void login_beifen()
        {
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                cmddd.CommandText = "insert into System_Login(管理员姓名,时间,事件) values('"+App_Code.ShareClass.Name+"','" + DateTime.Now.ToShortDateString() + "  " + DateTime.Now.ToLongTimeString() + "','备份')";
                cmddd.ExecuteNonQuery();
                //MessageBox.Show("注册成功！");

                connn.Close();
            }
            catch
            {
                MessageBox.Show("备份日志出错");
            }
        }


    }
}
