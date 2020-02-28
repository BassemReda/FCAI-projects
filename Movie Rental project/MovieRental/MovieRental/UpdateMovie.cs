using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.Sql;
using System.Data.SqlClient;

namespace MovieRental
{
    public partial class UpdateMovie : Form
    {
        public UpdateMovie()
        {
            InitializeComponent();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            string column =  listBox1.GetItemText(listBox1.SelectedItem);
            string connection = "Data Source=ANDROOO;Initial Catalog=master;Integrated Security=True";
            SqlConnection con = new SqlConnection(connection);
            con.Open();
            SqlCommand cmd = new SqlCommand();
            cmd.CommandText = "update MOVIE set "+column +"="+Int32.Parse(textBox2.Text) +" where MID = "+Int32.Parse(textBox1.Text);
            cmd.Connection = con;
            cmd.CommandType = CommandType.Text;
            cmd.ExecuteNonQuery();
            con.Close();
        }

        private void listBox1_MouseDown(object sender, MouseEventArgs e)
        {
            label2.Text = listBox1.GetItemText(listBox1.SelectedItem);
        }
    }
}
