using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data.Sql;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace MovieRental
{
    public partial class AddingMovie : Form
    {
        string[] AddList = new string[7];
        public AddingMovie()
        {
            InitializeComponent();
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        { 
            AddList[0] = textBox1.Text;
            AddList[1] = "199801";
            AddList[2] = textBox3.Text;
            AddList[3] = textBox4.Text;
            AddList[4] = textBox5.Text;
            AddList[5] = textBox6.Text;
            AddList[6] = textBox7.Text;
            string connection = "Data Source=ANDROOO;Initial Catalog=master;Integrated Security=True";
            SqlConnection con = new SqlConnection(connection);
            con.Open();
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText = "INSERT INTO MOVIE VALUES(" + Int32.Parse(AddList[0]) + "," + Int32.Parse(AddList[1]) + "," + Int32.Parse(AddList[2]) + ",'" + AddList[3] + "'," + float.Parse(AddList[4])
                + "," + Int32.Parse(AddList[5]) + "," + Int32.Parse(AddList[6]) + ")";
            cmd.Connection = con;
            cmd.CommandType = CommandType.Text;
            cmd.ExecuteNonQuery();
            cmd.CommandText = "insert into KIND values("+ Int32.Parse(AddList[0])+",(select TYPEID from TYPE where TYPENAME = '"+textBox2.Text+"' ))";
            cmd.Connection = con;
            cmd.CommandType = CommandType.Text;
            cmd.ExecuteNonQuery();
            con.Close();
            this.Close();
        }
    }
}
