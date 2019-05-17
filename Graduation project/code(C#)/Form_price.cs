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
    public partial class Form_price : Form
    {
        public Form_price()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Close();
            //Form_Interface frm1 = new Form_Interface();
            //frm1.Show();
        }

        private void Form_price_Load(object sender, EventArgs e)
        {
            SqlConnection mycon;
            string index1, index2, index3;



            try
            {
                mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand mycmd = mycon.CreateCommand();
                SqlDataReader mydr;
                mycon.Open();
                mycmd.CommandText = "select 临时,月租,长租 from Price_Set";
                SqlParameter TName = new SqlParameter("@name", SqlDbType.NVarChar);
                mycmd.Parameters.Add(TName);
                TName.Value = textBox2.Text.Trim();

                mydr = mycmd.ExecuteReader();

                if (mydr.Read())
                {
                    index1 = mydr.GetString(0);
                    index2 = mydr.GetString(1);
                    index3 = mydr.GetString(2);
                   

                    textBox1.Text = index1.Trim();
                    textBox2.Text = index2.Trim();
                    textBox3.Text = index3.Trim();
                    
                    //linshi = Convert.ToInt32(index1);
                    //a_rest = Convert.ToInt32(index2);
                    //b_park = Convert.ToInt32(index3);
                    







                }
                else
                {
                    MessageBox.Show("费率信息出错！");
                }
                mycon.Close();
            }
            catch
            {
                MessageBox.Show("费率信息...数据库出问题！！！");
            }

            textBox3.ReadOnly = true;

            if (App_Code.ShareClass.Type == "管理员")
            {
                button1.Visible = false;
                button2.Visible = false;
                textBox1.ReadOnly = true;
                textBox2.ReadOnly = true;
                //button4.Visible = false;


            }
            else if (App_Code.ShareClass.Type == "超级管理员")
            {

                button1.Visible = true;
                button2.Visible = true;
                textBox1.ReadOnly = false;
                textBox2.ReadOnly = false;
                //button4.Visible = true;


            }
            else
            {
                MessageBox.Show("管理员类型出错");
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                SqlConnection mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand mycmd = mycon.CreateCommand();

                string sqlstr = "update Price_Set";
                mycmd.CommandText = sqlstr + " set 临时 =@name,月租=@number where 长租 ='0'";

                SqlParameter Name = new SqlParameter("@name", SqlDbType.NVarChar);
                SqlParameter Number = new SqlParameter("@number", SqlDbType.NVarChar);
                //SqlParameter Lei = new SqlParameter("@lei", SqlDbType.NVarChar);

                mycmd.Parameters.Add(Name);
                mycmd.Parameters.Add(Number);
               // mycmd.Parameters.Add(Lei);


                Name.Value = textBox1.Text.Trim();
                Number.Value = textBox2.Text.Trim();
                //Lei.Value = textBox3.Text.Trim();

                mycon.Open();
                int i = mycmd.ExecuteNonQuery();
                mycon.Close();

                if (i != 0)
                {
                    MessageBox.Show("费率修改完成");
                    login_xgfl();
                    this.Close();

                }
                else
                {
                    MessageBox.Show("费率修改错误！");
                }

            }
            catch
            {
                MessageBox.Show("修改费率。。。连接数据库出现问题");
            }
            
        }
        /// <summary>
        /// 修改费率日志
        /// </summary>
        private void login_xgfl()
        {
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                cmddd.CommandText = "insert into System_Login(管理员姓名,时间,事件) values('"+App_Code.ShareClass.Name+"','" + DateTime.Now.ToShortDateString() + "  " + DateTime.Now.ToLongTimeString() + "','修改费率')";
                cmddd.ExecuteNonQuery();
                //MessageBox.Show("注册成功！");

                connn.Close();
            }
            catch
            {
                MessageBox.Show("修改费率日志出错");
            } 
        }
    }




}
