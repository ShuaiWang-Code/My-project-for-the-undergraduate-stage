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
    public partial class Form_xgmm : Form
    {
        public Form_xgmm()
        {
            InitializeComponent();
        }
        /// <summary>
        /// 载入界面显示当前用户名
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Form_xgmm_Load(object sender, EventArgs e)
        {
            textBox1.Text = App_Code.ShareClass.Name;
        }
        /// <summary>
        /// 退出修改密码界面
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            Form_Interface frm1 = new Form_Interface();
            this.Close();
            frm1.Show();
        }
        /// <summary>
        /// 确认修改密码
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(textBox2.Text.Trim()))
            {
                MessageBox.Show("请输入新密码！");

            }
            else
            {
                if (textBox2.Text.Trim() != textBox3.Text.Trim())
                {
                    MessageBox.Show("两次密码不一致！");
                }
                else
                {
                    try
                    {
                        SqlConnection mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                        SqlCommand mycmd = mycon.CreateCommand();

                        string sqlstr = "update Admin_Info";
                        mycmd.CommandText = sqlstr + " set 管理员密码 =@pwd where 管理员姓名 =@ID";
                        SqlParameter Id = new SqlParameter("@ID", SqlDbType.NVarChar);
                        SqlParameter Pwd = new SqlParameter("@pwd", SqlDbType.NVarChar);

                        mycmd.Parameters.Add(Pwd);
                        mycmd.Parameters.Add(Id);
                        Id.Value = textBox1.Text.Trim();
                        Pwd.Value = textBox2.Text.Trim();

                        mycon.Open();
                        int i = mycmd.ExecuteNonQuery();
                        mycon.Close();

                        if (i != 0)
                        {
                            login_xgmm();
                            MessageBox.Show("密码修改完成");
                            this.Hide();
                            Form_Interface frmif = new Form_Interface();
                            frmif.Show();
                        }
                        else
                        {
                            MessageBox.Show("密码修改错误！");
                        }

                    }
                    catch
                    {
                        MessageBox.Show("修改密码时，连接数据库出现问题");
                    }
                }
            }
        }
        /// <summary>
        /// 修改密码日志
        /// </summary>
        private void login_xgmm()
        {
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                cmddd.CommandText = "insert into System_Login(管理员姓名,时间,事件) values('注册用户','" + DateTime.Now.ToShortDateString() + "  " + DateTime.Now.ToLongTimeString() + "','修改密码')";
                cmddd.ExecuteNonQuery();
                //MessageBox.Show("注册成功！");

                connn.Close();
            }
            catch
            {
                MessageBox.Show("修改密码出错");
            } 
        }
    }

}
