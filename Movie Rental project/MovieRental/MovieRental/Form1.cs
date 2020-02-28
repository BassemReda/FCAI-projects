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
    public partial class Main : Form
    {
        public Main()
        {
          
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            AddingMovie adm = new AddingMovie();
            adm.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            UpdateMovie umd = new UpdateMovie();
            umd.Show();
        }
    }
}
