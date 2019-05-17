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
    public partial class Form_yhgl : Form
    {
        public Form_yhgl()
        {
            InitializeComponent();
        }
        /// <summary>
        /// 填充
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        SqlCommand cmdd;
        SqlDataAdapter sda;
        SqlConnection conn;
        DataSet ds;
        private void Form_yhgl_Load(object sender, EventArgs e)
        {
            conn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
            cmdd = new SqlCommand("select * from User_Management", conn);
            sda = new SqlDataAdapter();
            sda.SelectCommand = cmdd;
            ds = new DataSet();
            sda.Fill(ds, "m");
            dataGridView1.DataSource = ds.Tables[0];

            if (App_Code.ShareClass.Type == "管理员")
            {
                button1.Visible = false;
                button3.Visible = false;
                button4.Visible = false;
                

            }
            else if (App_Code.ShareClass.Type == "超级管理员")
            {

                button1.Visible = true;
                button3.Visible = true;
                button4.Visible = true;
                

            }
            else
            {
                MessageBox.Show("管理员类型出错");
            }
        }
        /// <summary>
        /// 修改用户信息
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {

            if ((textBox1.Text != "") && (textBox2.Text != "") && (textBox3.Text != ""))
            {
                try
                {
                    SqlConnection mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                    SqlCommand mycmd = mycon.CreateCommand();

                    string sqlstr = "update User_Management";
                    mycmd.CommandText = sqlstr + " set 姓名 =@name,车牌号=@number,用户类别=@lei where 车牌号=@number";
                    
                    SqlParameter Name = new SqlParameter("@name", SqlDbType.NVarChar);
                    SqlParameter Number = new SqlParameter("@number", SqlDbType.NVarChar);
                    SqlParameter Lei = new SqlParameter("@lei", SqlDbType.NVarChar);

                    mycmd.Parameters.Add(Name);
                    mycmd.Parameters.Add(Number);
                    mycmd.Parameters.Add(Lei);

                    
                    Name.Value = textBox1.Text.Trim();
                    Number.Value = textBox2.Text.Trim();
                    Lei.Value = textBox3.Text.Trim();

                    mycon.Open();
                    int i = mycmd.ExecuteNonQuery();
                    mycon.Close();

                    if (i != 0)
                    {
                        MessageBox.Show("修改完成");
                        
                    }
                    else
                    {
                        MessageBox.Show("修改错误！");
                    }

                }
                catch
                {
                    MessageBox.Show("连接数据库出现问题");
                }
            }
            else
            {
                MessageBox.Show("修改错误！");
            }
            login_xiugai();

        }
        /// <summary>
        /// 修改用户信息日志
        /// </summary>
        private void login_xiugai()
        {
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                cmddd.CommandText = "insert into System_Login(管理员姓名,时间,事件) values('" + App_Code.ShareClass.Name.Trim() + "','" + DateTime.Now.ToShortDateString() + "  " + DateTime.Now.ToLongTimeString() + "','修改用户信息')";
                cmddd.ExecuteNonQuery();
                //MessageBox.Show("登录成功！");

                connn.Close();
            }
            catch
            {
                MessageBox.Show("修改用户信息日志出错");
            }    
        }
        /// <summary>
        /// 点击数据显示到文本
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void dataGridView1_CellClick(object sender, DataGridViewCellEventArgs e)
        {
            textBox1.Text = dataGridView1.SelectedCells[0].Value.ToString();
            textBox2.Text = dataGridView1.SelectedCells[1].Value.ToString();
            textBox3.Text = dataGridView1.SelectedCells[2].Value.ToString();
        }
        /// <summary>
        ///更新完毕点击刷新数据
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            conn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
            cmdd = new SqlCommand("select * from User_Management", conn);
            sda = new SqlDataAdapter();
            sda.SelectCommand = cmdd;
            ds = new DataSet();
            sda.Fill(ds, "m");
            dataGridView1.DataSource = ds.Tables[0];
        }
        /// <summary>
        /// 删除选中的数据项
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button3_Click(object sender, EventArgs e)
        {
            SqlConnection con;
            try
            {
                con = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmd = con.CreateCommand();
                con.Open();
                cmd.CommandText = "delete from User_Management where 姓名 = @xingming";
                SqlParameter Xingming = new SqlParameter("@xingming", SqlDbType.NVarChar);
                cmd.Parameters.Add(Xingming);
                Xingming.Value = textBox1.Text.Trim();
                cmd.ExecuteNonQuery();
                login_delete();
                MessageBox.Show("删除成功，请刷新数据！");

                con.Close();
            }
            catch
            {
                MessageBox.Show("删除出错");
            }
            
        }
        /// <summary>
        /// 删除用户信息日志
        /// </summary>
        private void login_delete()
        { 
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                cmddd.CommandText = "insert into System_Login(管理员姓名,时间,事件) values('" + App_Code.ShareClass.Name.Trim() + "','" + DateTime.Now.ToShortDateString() + "  " + DateTime.Now.ToLongTimeString() + "','删除用户信息')";
                cmddd.ExecuteNonQuery();
                //MessageBox.Show("登录成功！");

                connn.Close();
            }
            catch
            {
                MessageBox.Show("删除用户信息日志出错");
            }  
        }
        /// <summary>
        /// 添加新用户
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button4_Click(object sender, EventArgs e)
        {
            Form_yhgl_new frmnew = new Form_yhgl_new();
            //this.Hide();
            frmnew.Show();
        }
        /// <summary>
        /// 返回到用户管理
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button5_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            //
            //Form_yhgl_yhss frmss = new Form_yhgl_yhss();
            //frmss.Show();
            if (textBox4.Text != "")
            {
                conn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                cmdd = new SqlCommand("select * from User_Management where " + comboBox1.Text + "=@name", conn);
                SqlParameter TName = new SqlParameter("@name", SqlDbType.NVarChar);
                cmdd.Parameters.Add(TName);
                TName.Value = textBox4.Text.Trim();
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

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            comboBox1.Text = "";
            textBox4.Clear();
        }
    }
}
