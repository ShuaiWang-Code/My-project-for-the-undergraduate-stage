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
using System.IO;

namespace WindowsFormsApplication1
{
    public partial class Form_Interface : Form
    {
        public Form_Interface()
        {
            InitializeComponent();
        }
        /// <summary>
        /// 界面载入
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        int a_park, b_park, c_park, a_rest, b_rest, c_rest, a_sum = 5, b_sum = 5, c_sum = 5;
        private void Form_Interface_Load(object sender, EventArgs e)
        {
            //
            //this.skinEngine1.SkinFile = "Longhorn.ssk";
            //this.Text = "                                                                    停车场管理系统";
            //toolStripStatusLabel2.Text = App_Code.ShareClass.Name;
            //toolStripStatusLabel6.Text = App_Code.ShareClass.Type+"  :";
            //toolStripStatusLabel4.Text = DateTime.Now.ToShortDateString();
            //toolStripStatusLabel5.Text = DateTime.Now.ToLongTimeString();

            label12.Text = App_Code.ShareClass.Type+":";
            label13.Text = App_Code.ShareClass.Name;

            label15.Text = DateTime.Now.ToShortDateString();
            label16.Text = DateTime.Now.ToLongTimeString();

            shi = 12;
            fen = 0;
            miao = 0;

            App_Code.TimeClass.SHI = shi;
            App_Code.TimeClass.FEN = fen;
            App_Code.TimeClass.MIAO = miao;

            get_feilv();
            cwsl_tiqu();


            
        }
        /// <summary>
        /// 定时器更新时间
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        //DateTime dingshi ; //设置每天定时时间。
        int shi, fen, miao;
        private void timer1_Tick(object sender, EventArgs e)
        {
            //toolStripStatusLabel4.Text = DateTime.Now.ToShortDateString();
            //toolStripStatusLabel5.Text = DateTime.Now.ToLongTimeString();
            string str = File.ReadAllText("C:\\Users\\W\\Desktop\\驶入车辆.txt", Encoding.Default);
            string str1 = File.ReadAllText("C:\\Users\\W\\Desktop\\驶出车辆.txt", Encoding.Default);

            if (str != "")
            button1.PerformClick();

            if (str1 != "")
            button2.PerformClick();

            label15.Text = DateTime.Now.ToShortDateString();
            label16.Text = DateTime.Now.ToLongTimeString();

            get_feilv();
            cwsl_tiqu();

            shi = App_Code.TimeClass.SHI;
            fen = App_Code.TimeClass.FEN;
            miao = App_Code.TimeClass.MIAO;


            //string date = "12:00:00"; //设置每天定时时间。
            string date1 = DateTime.Now.Hour + ":" + DateTime.Now.Minute + ":" + DateTime.Now.Second;
            if (DateTime.Now.Hour == shi && DateTime.Now.Minute == fen && DateTime.Now.Second == miao)
            {
                beifensjk();
            }
        }
        /// <summary>
        /// 自动备份数据库
        /// </summary>
        
        
        private void beifensjk()
        {
            string Str_dar1 = "";
            string Str_dar = "自动备份";
            string houzhui = ".bak";
            string SaveFileName = DateTime.Now.Date.ToString("yyyy", DateTimeFormatInfo.InvariantInfo) + "年" + DateTime.Now.Date.ToString("MM", DateTimeFormatInfo.InvariantInfo) + "月";
            SaveFileName += DateTime.Now.Date.ToString("dd", DateTimeFormatInfo.InvariantInfo) + "日" + DateTime.Now.ToString("HH", DateTimeFormatInfo.InvariantInfo);
            SaveFileName += "点" + DateTime.Now.ToString("mm", DateTimeFormatInfo.InvariantInfo) + "分" + DateTime.Now.ToString("ss", DateTimeFormatInfo.InvariantInfo) + "秒";


           
            Str_dar1 = "C:\\Users\\W\\Desktop\\自动备份\\";
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                //cmddd.CommandText = "backup database CarSystemDB to disk='"+"C:\\Users\\W\\Desktop"+Str_dar+".bat"+"'";
                //cmddd.CommandText = "backup database CarSystemDB to disk='C:\\Users\\W\\Desktop\\Test2.bak'";
                //cmddd.CommandText = "backup database CarSystemDB to disk='"+Str_dar+"'";

                cmddd.CommandText = "backup database CarSystemDB to disk= '" + Str_dar1 + Str_dar + SaveFileName + houzhui + "'";


                cmddd.ExecuteNonQuery();

                MessageBox.Show("自动备份成功！");

                connn.Close();
                //login_beifen();
            }
            catch
            {
                MessageBox.Show("自动备份失败！");
            }
        }
        /// 
        
        /// <summary>
        /// 修改密码界面
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void toolStripLabel4_Click(object sender, EventArgs e)
        {
            Form_xgmm frmmm = new Form_xgmm();
            this.Hide();
            frmmm.Show();
        }
        /// <summary>
        /// 退出返回到登录界面
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void toolStripLabel5_Click(object sender, EventArgs e)
        {
            Form1 frm1 = new Form1();
            this.Close();
            frm1.Show();
        }
        /// <summary>
        /// 用户管理界面
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void toolStripLabel1_Click(object sender, EventArgs e)
        {
            Form_yhgl frmyhgl = new Form_yhgl();
            frmyhgl.Show();

        }
        /// <summary>
        /// 驶入
        /// </summary>
        private void shiru_read()
        {
            /*openFileDialog1.Filter = "文本文件(*.txt)|*.txt";

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                textBox1.Text = string.Empty;
                StreamReader sr = new StreamReader(openFileDialog1.FileName);
                textBox1.Text = sr.ReadToEnd();
                sr.Close();
                     
            }*/
            string str = File.ReadAllText("C:\\Users\\W\\Desktop\\驶入车辆.txt", Encoding.Default);
            textBox1.Text = str;
            string str1 = "";

            if (textBox1.Text != "")
            {
                File.WriteAllText("C:\\Users\\W\\Desktop\\驶入车辆.txt", str1, Encoding.Default);
            }

        }
        /// <summary>
        /// 驶入
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            //delete_login();
            shiru_read();
            if (textBox1.Text != "")
            {
                SqlConnection mycon;

                try
                {
                    mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                    SqlCommand mycmd = mycon.CreateCommand();
                    SqlDataReader mydr;
                    mycon.Open();
                    mycmd.CommandText = "select * from User_Management where 车牌号 = @name";
                    SqlParameter TName = new SqlParameter("@name", SqlDbType.NVarChar);
                    mycmd.Parameters.Add(TName);
                    TName.Value = textBox1.Text.Trim();
                    mydr = mycmd.ExecuteReader();

                    if (mydr.HasRows)
                    {
                        //MessageBox.Show("用户存在");
                        add_login_input();
                    }
                    else
                    {
                        MessageBox.Show("用户不存在,正在注册临时用户！");
                        add_new();
                        add_login_input();
                    }
                    mycon.Close();

                    cwsl_change1();

                    login_in();
                }
                catch
                {
                    MessageBox.Show("连接问题！！！");
                }
            }
            else
            {
                MessageBox.Show("驶入车牌号为空！");
            }

            add_cwgl();
        }
        ///
        ///
        ///驶出
        private void shichu_read()
        {
            /*openFileDialog1.Filter = "文本文件(*.txt)|*.txt";

            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                textBox1.Text = string.Empty;
                StreamReader sr = new StreamReader(openFileDialog1.FileName);
                textBox1.Text = sr.ReadToEnd();
                sr.Close();
                     
            }*/
            string str = File.ReadAllText("C:\\Users\\W\\Desktop\\驶出车辆.txt", Encoding.Default);
            textBox2.Text = str;
            string str1 = "";
            if (textBox2.Text != "")
            {
                File.WriteAllText("C:\\Users\\W\\Desktop\\驶出车辆.txt",str1, Encoding.Default); 
            }
        }

        /// <summary>
        /// 驶出
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        TimeSpan st1;
        private void button2_Click(object sender, EventArgs e)
        {
            shichu_read();
            cwsl_change2();
           
            add_login_output();
            add_flag_chuku();
            delete_cwgl();

            login_out();
            
        }
        /// <summary>
        /// 添加临时用户
        /// </summary>
        private void add_new()
        {
            SqlConnection con;
            try
            {
                con = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmd = con.CreateCommand();
                con.Open();
                cmd.CommandText = "insert into User_Management(姓名,车牌号,用户类别) values('临时','" + textBox1.Text.Trim() + "','临时')";
                cmd.ExecuteNonQuery();
                MessageBox.Show("注册临时用户成功");

                con.Close();
            }
            catch
            {
                MessageBox.Show("注册临时用户出错");
            }
        }
        /// <summary>
        /// 入库日志
        /// </summary>
        private void add_login_input()
        {
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                cmddd.CommandText = "insert into Price_Login(车牌号,入库时间,出库时间,是否出库) values('" + textBox1.Text.Trim() + "','"+DateTime.Now.ToShortDateString()+"  "+DateTime.Now.ToLongTimeString()+"','1','0')";
                cmddd.ExecuteNonQuery();
                //MessageBox.Show("添加入库日志成功");

                connn.Close();
            }
            catch
            {
                MessageBox.Show("添加入库日志出错");
            }
        }
        /// <summary>
        /// 出库添加日志
        /// </summary>
        private void add_login_output()
        {
            try
            {
                SqlConnection mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand mycmd = mycon.CreateCommand();
                mycon.Open();
                string sqlstr = "update Price_Login";
                mycmd.CommandText = sqlstr + " set 出库时间 =@pwd where 车牌号 =@ID and 出库时间 = '1'";
                SqlParameter Id = new SqlParameter("@ID", SqlDbType.NVarChar);
                SqlParameter Pwd = new SqlParameter("@pwd", SqlDbType.NVarChar);

                mycmd.Parameters.Add(Pwd);
                mycmd.Parameters.Add(Id);
                Id.Value = textBox2.Text.Trim();
                Pwd.Value = DateTime.Now.ToShortDateString() + "  " + DateTime.Now.ToLongTimeString();

                
                int i = mycmd.ExecuteNonQuery();
                mycon.Close();

                if (i != 0)
                {
                    //MessageBox.Show("出库日志成功");
                    price();
                    
                }
                else
                {
                    MessageBox.Show("出库车辆不存在！");
                }

            }
            catch
            {
                MessageBox.Show("出库时，连接数据库出现问题");
            }
            
        }
        /// <summary>
        /// 出库时修改出库标志
        /// </summary>
        private void add_flag_chuku()
        {
            SqlConnection mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
            SqlCommand mycmd = mycon.CreateCommand();
            mycon.Open();
            string sqlstr = "update Price_Login";
            mycmd.CommandText = sqlstr + " set 是否出库='1' where 车牌号 =@ID";
            SqlParameter Id = new SqlParameter("@ID", SqlDbType.NVarChar);          
            mycmd.Parameters.Add(Id);
            Id.Value = textBox2.Text.Trim();           
            mycmd.ExecuteNonQuery();
            mycon.Close();
            
        }
        /// <summary>
        /// 提取出库入库时间，并计算时间间隔
        /// </summary>
        private void time_span()
        {
            SqlConnection mycon;
            string index1,index2;
            DateTime chuku, ruku;
            TimeSpan st;

            try
            {
                mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand mycmd = mycon.CreateCommand();
                SqlDataReader mydr;
                mycon.Open();
                mycmd.CommandText = "select 入库时间,出库时间 from Price_Login where 车牌号 = @name and 是否出库 = '0'";
                SqlParameter TName = new SqlParameter("@name", SqlDbType.NVarChar);
                mycmd.Parameters.Add(TName);
                TName.Value = textBox2.Text.Trim();

                mydr = mycmd.ExecuteReader();

                if (mydr.Read())
                {
                    index1 = mydr.GetString(0);
                    index2 = mydr.GetString(1);
                    chuku = Convert.ToDateTime(index2);
                    ruku = Convert.ToDateTime(index1);
                    st = chuku - ruku;
                    st1 = st;
                    
                }
                else
                {
                    MessageBox.Show("出库入库时间出错");
                }
                mycon.Close();
            }
            catch
            {
                MessageBox.Show("计算价格问题！！！");
            }        
        }
        /// <summary>
        /// 计算价格
        /// </summary>
        int ls, yz;
        private void price()
        {
            time_span();
            
            SqlConnection mycon;
            string index;

            try
            {
                mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand mycmd = mycon.CreateCommand();
                SqlDataReader mydr;
                mycon.Open();
                mycmd.CommandText = "select 用户类别 from User_Management where 车牌号 = @name";
                SqlParameter TName = new SqlParameter("@name", SqlDbType.NVarChar);
                mycmd.Parameters.Add(TName);
                TName.Value = textBox2.Text.Trim();

                mydr = mycmd.ExecuteReader();

                if (mydr.Read())
                {
                    index = mydr.GetString(0);
                    if (index == "临时")
                    {
                        if (Convert.ToInt32(st1.Hours*60+st1.Minutes) >= 20)
                        {
                            textBox3.Text = Convert.ToString((st1.Minutes+st1.Hours*60) / 30 * ls + ls);
                        }
                        else
                        {
                            textBox3.Text = "0";    
                        }

                        /*演示效果*/
                        //textBox3.Text = Convert.ToString(st1.Seconds * ls + st1.Minutes * ls * 60);
                        
                        
                    }
                    else if (index == "月租")
                    {
                        if (Convert.ToInt32(st1.Hours * 60 + st1.Minutes) >= 20)
                        {
                            textBox3.Text = Convert.ToString((st1.Minutes + st1.Hours * 60) / 30 * yz + yz);
                        }
                        else
                        {
                            textBox3.Text = "0";  
                        }
                        
                         /*演示效果*/
                        //textBox3.Text = Convert.ToString(st1.Seconds * yz + st1.Minutes * yz * 60); 
                    }
                    else if (index == "长租")
                    {
                        textBox3.Text = "0";
                    }
                    else
                    {
                        MessageBox.Show("index返回错误");
                    }
                    add_price();
                }
                else
                {
                   
                }
                mycon.Close();
            }
            catch
            {
                MessageBox.Show("计算价格问题！！！");
            } 
        }
        /// <summary>
        /// 停车价格写入
        /// </summary>
        private void add_price()
        {
            try
            {
                SqlConnection mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand mycmd = mycon.CreateCommand();
                mycon.Open();
                string sqlstr = "update Price_Login";
                mycmd.CommandText = sqlstr + " set 收费金额 =@pwd where 车牌号 =@ID and 是否出库 = '0'";
                SqlParameter Id = new SqlParameter("@ID", SqlDbType.NVarChar);
                SqlParameter Pwd = new SqlParameter("@pwd", SqlDbType.NVarChar);

                mycmd.Parameters.Add(Pwd);
                mycmd.Parameters.Add(Id);
                Id.Value = textBox2.Text.Trim();
                Pwd.Value = textBox3.Text.Trim();


                int i = mycmd.ExecuteNonQuery();
                mycon.Close();

                if (i != 0)
                {
                    MessageBox.Show("车辆驶出，请收费！");
                    

                }
                else
                {
                    MessageBox.Show("价格写入错误！");
                }

            }
            catch
            {
                MessageBox.Show("写入价格时，连接数据库出现问题");
            }
        }
        /// <summary>
        /// 出入场记录
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void toolStripLabel3_Click(object sender, EventArgs e)
        {
            Form_crc_login frm1 = new Form_crc_login();
            frm1.Show();
        }
        /// <summary>
        /// 提取载入初...车位数量
        /// </summary>
        private void cwsl_tiqu()
        {
            SqlConnection mycon;
            string index1, index2, index3, index4, index5, index6;
            


            try
            {
                mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand mycmd = mycon.CreateCommand();
                SqlDataReader mydr;
                mycon.Open();
                mycmd.CommandText = "select 停车数量A,剩余车位A,停车数量B,剩余车位B,停车数量C,剩余车位C from Parking_Management";
                //SqlParameter TName = new SqlParameter("@name", SqlDbType.NVarChar);
                //mycmd.Parameters.Add(TName);
                //TName.Value = textBox2.Text.Trim();

                mydr = mycmd.ExecuteReader();

                if (mydr.Read())
                {
                    index1 = mydr.GetString(0);
                    index2 = mydr.GetString(1);
                    index3 = mydr.GetString(2);
                    index4 = mydr.GetString(3);
                    index5 = mydr.GetString(4);
                    index6 = mydr.GetString(5);

                    textBox4.Text = index1.Trim();
                    textBox5.Text = index2.Trim();
                    textBox6.Text = index3.Trim();
                    textBox7.Text = index4.Trim();
                    textBox8.Text = index5.Trim();
                    textBox9.Text = index6.Trim();

                    a_park = Convert.ToInt32(index1);
                    a_rest = Convert.ToInt32(index2);
                    b_park = Convert.ToInt32(index3);
                    b_rest = Convert.ToInt32(index4);
                    c_park = Convert.ToInt32(index5);
                    c_rest = Convert.ToInt32(index6);

                   



   

                }
                else
                {
                    MessageBox.Show("停车管理信息出错！");
                }
                mycon.Close();
            }
            catch
            {
                MessageBox.Show("停车管理中...数据库出问题！！！");
            }            
        }
        /// <summary>
        /// 入场数量变化
        /// </summary>
        string carleibie;
        private void cwsl_change1()
        {
            SqlConnection mycon;
            string index;

            try
            {
                mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand mycmd = mycon.CreateCommand();
                SqlDataReader mydr;
                mycon.Open();
                mycmd.CommandText = "select 用户类别 from User_Management where 车牌号 = @name";
                SqlParameter TName = new SqlParameter("@name", SqlDbType.NVarChar);
                mycmd.Parameters.Add(TName);
                TName.Value = textBox1.Text.Trim();

                mydr = mycmd.ExecuteReader();

                if (mydr.Read())
                {
                    index = mydr.GetString(0);
                    if (index == "临时")
                    {
                        c_park++;
                        c_rest = c_sum - c_park;
                        carleibie = "临时";
                        if (c_rest == 0)
                        {
                            MessageBox.Show("临时车位已满，禁止停入");
                        }
                        

                    }
                    else if (index == "月租")
                    {
                        b_park++;
                        b_rest = b_sum - b_park;
                        carleibie = "月租";
                        if (b_rest == 0)
                        {
                            MessageBox.Show("月租车位已满，禁止停入");
                        }

                    }
                    else if (index == "长租")
                    {
                        a_park++;
                        a_rest = a_sum - a_park;
                        carleibie = "长租";
                        if (a_rest == 0)
                        {
                            MessageBox.Show("长租车位已满，禁止停入");
                        }
                    }
                    else
                    {
                        MessageBox.Show("index车位数量返回错误");
                    }
                    update_sum();
                    
                        
                  
                }
                else
                {
                    MessageBox.Show("未查到数量变化");
                }
                mycon.Close();
            }
            catch
            {
                MessageBox.Show("计算车位数量...数据库出错问题！！！");
            }        
        }
        /// <summary>
        /// 出场数量变化
        /// </summary>
        private void cwsl_change2()
        {
            SqlConnection mycony;
            string index;

            try
            {
                mycony = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand mycmdy = mycony.CreateCommand();
                SqlDataReader mydr;
                mycony.Open();
                mycmdy.CommandText = "select 用户类别 from User_Management where 车牌号 = @name";
                SqlParameter TName = new SqlParameter("@name", SqlDbType.NVarChar);
                mycmdy.Parameters.Add(TName);
                TName.Value = textBox2.Text.Trim();

                mydr = mycmdy.ExecuteReader();

                if (mydr.Read())
                {
                    index = mydr.GetString(0);
                    if (index == "临时")
                    {
                        c_park--;
                        c_rest = c_sum - c_park;
                        update_sum();
                        if (c_park == 0)
                        {
                            MessageBox.Show("临时车位目前全空");
                        }


                    }
                    else if (index == "月租")
                    {
                        b_park--;
                        b_rest = b_sum - b_park;
                        update_sum();
                        if (b_park == 0)
                        {
                            MessageBox.Show("月租车位目前全空");
                        }

                    }
                    else if (index == "长租")
                    {
                        a_park--;
                        a_rest = a_sum - a_park;
                        update_sum();
                        if (a_park == 0)
                        {
                            MessageBox.Show("长租车位目前全空");
                        }
                    }
                    else
                    {
                        MessageBox.Show("index出场车位数量返回错误");
                    }
                    


                }
                else
                {
                    MessageBox.Show("出场未查到数量变化");
                }
                mycony.Close();
                
            }
            catch
            {
                MessageBox.Show("计算车位数量...数据库出错问题！！！");
            }      
        }
        /// <summary>
        /// 停车管理数量更新至数据库
        /// </summary>
        private void update_sum()
        {
            try
            {
                SqlConnection mycon = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand mycmd = mycon.CreateCommand();

                string sqlstr = "update Parking_Management";
                mycmd.CommandText = sqlstr + " set 停车数量A=@index11,剩余车位A=@index22,停车数量B=@index33,剩余车位B=@index44,停车数量C=@index55,剩余车位C=@index66";

                SqlParameter Index11 = new SqlParameter("@index11", SqlDbType.NVarChar);
                SqlParameter Index22 = new SqlParameter("@index22", SqlDbType.NVarChar);
                SqlParameter Index33 = new SqlParameter("@index33", SqlDbType.NVarChar);
                SqlParameter Index44 = new SqlParameter("@index44", SqlDbType.NVarChar);
                SqlParameter Index55 = new SqlParameter("@index55", SqlDbType.NVarChar);
                SqlParameter Index66 = new SqlParameter("@index66", SqlDbType.NVarChar);

                mycmd.Parameters.Add(Index11);
                mycmd.Parameters.Add(Index22);
                mycmd.Parameters.Add(Index33);
                mycmd.Parameters.Add(Index44);
                mycmd.Parameters.Add(Index55);
                mycmd.Parameters.Add(Index66);


                Index11.Value = a_park.ToString();
                Index22.Value = a_rest.ToString();
                Index33.Value = b_park.ToString();
                Index44.Value = b_rest.ToString();
                Index55.Value = c_park.ToString();
                Index66.Value = c_rest.ToString();

                mycon.Open();
                int i = mycmd.ExecuteNonQuery();
                mycon.Close();

                /*if (i != 0)
                {
                    MessageBox.Show("停车管理更新成功");

                }
                else
                {
                    MessageBox.Show("停车管理更新错误！");
                }*/

            }
            catch
            {
                MessageBox.Show("停车管理...连接数据库出现问题");
            }
        }
        /// <summary>
        /// 自动删除同一车牌号的历史信息
        /// </summary>
        private void delete_login()
        {
            SqlConnection con;
            try
            {
                con = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmd = con.CreateCommand();
                con.Open();
                cmd.CommandText = "delete from Price_Login where 车牌号 = @xingming";
                SqlParameter Xingming = new SqlParameter("@xingming", SqlDbType.NVarChar);
                cmd.Parameters.Add(Xingming);
                Xingming.Value = textBox1.Text.Trim();
                cmd.ExecuteNonQuery();
                //MessageBox.Show("删除成功，请刷新数据！");

                con.Close();
            }
            catch
            {
                //MessageBox.Show("删除出错");
            }     
        }
        /// <summary>
        /// 车位管理
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void toolStripLabel2_Click(object sender, EventArgs e)
        {
            Form_cwgl frm1 = new Form_cwgl();
            frm1.Show();
        }
        /// <summary>
        /// clear 刷新
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pictureBox1_Click(object sender, EventArgs e)
        {
            textBox1.Clear();
            textBox2.Clear();
            textBox3.Clear();
        }
        /// <summary>
        /// 入库时，添加车位信息
        /// </summary>
        private void add_cwgl()
        {
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                cmddd.CommandText = "insert into Space_Info(时间,车位,使用情况,停入车辆车牌号) values('" + DateTime.Now.ToShortDateString() + "  " + DateTime.Now.ToLongTimeString() + "','"+carleibie+"','1','"+textBox1.Text.Trim()+"')";
                cmddd.ExecuteNonQuery();
                //MessageBox.Show("驶入成功");

                connn.Close();
            }
            catch
            {
                MessageBox.Show("添加车位信息出错");
            }       
        }
        /// <summary>
        /// 出库时，删除车位信息
        /// </summary>
        private void delete_cwgl()
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
                Xingming.Value = textBox2.Text.Trim();
                cmd.ExecuteNonQuery();
                //MessageBox.Show("删除成功，请刷新数据！");

                con.Close();
            }
            catch
            {
                MessageBox.Show("删除出错");
            }
        }


        /// <summary>
        /// 管理员操作日志
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void 管理员操作日志ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form_system_login frm1 = new Form_system_login();
            frm1.Show();
        }
        /// <summary>
        /// 停车用户日志
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void 停车用户日志ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form_car_login frm2 = new Form_car_login();
            frm2.Show();
        }
        /// <summary>
        /// 驶入车辆日志
        /// </summary>
        private void login_in()
        {
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                cmddd.CommandText = "insert into Car_Login(车牌号,时间,事件) values('"+textBox1.Text.Trim()+"','" + DateTime.Now.ToShortDateString() + "  " + DateTime.Now.ToLongTimeString() + "','驶入车辆')";
                cmddd.ExecuteNonQuery();
                //MessageBox.Show("注册成功！");

                connn.Close();
            }
            catch
            {
                MessageBox.Show("驶入日志出错");
            } 
        }
        /// <summary>
        /// 驶出车辆日志
        /// </summary>
        private void login_out()
        {
            SqlConnection connn;
            try
            {
                connn = new SqlConnection(App_Code.ConnectionClass.GetConStr);
                SqlCommand cmddd = connn.CreateCommand();
                connn.Open();
                cmddd.CommandText = "insert into Car_Login(车牌号,时间,事件) values('" + textBox2.Text.Trim() + "','" + DateTime.Now.ToShortDateString() + "  " + DateTime.Now.ToLongTimeString() + "','驶出车辆')";
                cmddd.ExecuteNonQuery();
                //MessageBox.Show("注册成功！");

                connn.Close();
            }
            catch
            {
                MessageBox.Show("驶出日志出错");
            }
        }
        /// <summary>
        /// 费率界面
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void toolStripLabel7_Click(object sender, EventArgs e)
        {
            Form_price frm1 = new Form_price();
            frm1.Show();
        }
        /// <summary>
        /// 得到费率
        /// </summary>
        private void get_feilv()
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
                //SqlParameter TName = new SqlParameter("@name", SqlDbType.NVarChar);
                //mycmd.Parameters.Add(TName);
                //TName.Value = textBox2.Text.Trim();

                mydr = mycmd.ExecuteReader();

                if (mydr.Read())
                {
                    index1 = mydr.GetString(0);
                    index2 = mydr.GetString(1);
                    index3 = mydr.GetString(2);


                    //textBox1.Text = index1.Trim();
                    //textBox2.Text = index2.Trim();
                    //textBox3.Text = index3.Trim();

                    ls = Convert.ToInt32(index1);
                    yz = Convert.ToInt32(index2);
                    








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
        }
        /// <summary>
        /// 备份
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void 数据备份ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form_beifen frm1 = new Form_beifen();
            frm1.Show();
        }
        /// <summary>
        /// 还原
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void 数据还原ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form_huanyuan frm2 = new Form_huanyuan();
            frm2.Show();
        }

        private void label10_Click(object sender, EventArgs e)
        {

        }

        private void 自动备份时间ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("自动定时时间为12：00：00");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            Form_yhgl frmyhgl = new Form_yhgl();
            frmyhgl.Show();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Form_cwgl frm1 = new Form_cwgl();
            frm1.Show();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            Form_crc_login frm1 = new Form_crc_login();
            frm1.Show();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            Form_price frm1 = new Form_price();
            frm1.Show();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            Form_xgmm frmmm = new Form_xgmm();
            this.Hide();
            frmmm.Show();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            Form1 frm1 = new Form1();
            this.Close();
            frm1.Show();
        }

        private void button6_Click(object sender, EventArgs e)
        {
            Form_rzjl frm1 = new Form_rzjl();
            frm1.Show();
        }

        private void label12_Click(object sender, EventArgs e)
        {

        }

        private void label13_Click(object sender, EventArgs e)
        {

        }
    }
}
