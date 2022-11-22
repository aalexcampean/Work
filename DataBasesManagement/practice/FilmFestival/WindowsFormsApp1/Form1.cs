using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        SqlConnection connection;
        SqlDataAdapter dataAdapterProducer, dataAdapterMovie;
        DataSet dataSet;
        SqlCommandBuilder commandBuilder;
        BindingSource bindingSourceProducer, bindingSourceMovie;

        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            dataAdapterMovie.Update(dataSet, "Movie");

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'filmFestivalDataSet1.Movie' table. You can move, or remove it, as needed.
            this.movieTableAdapter.Fill(this.filmFestivalDataSet1.Movie);
            // TODO: This line of code loads data into the 'filmFestivalDataSet.Producer' table. You can move, or remove it, as needed.
            this.producerTableAdapter.Fill(this.filmFestivalDataSet.Producer);

        }

        private void button1_Click(object sender, EventArgs e)
        {
            connection = new SqlConnection(@"Data Source=Desktop-p9hv7vf;Initial Catalog=FilmFestival;Integrated Security=True");
            dataSet = new DataSet();
            dataAdapterMovie = new SqlDataAdapter("SELECT * FROM Movie", connection);
            dataAdapterProducer = new SqlDataAdapter("SELECT * FROM Producer", connection);


            commandBuilder = new SqlCommandBuilder(dataAdapterMovie);

            dataAdapterMovie.Fill(dataSet, "Movie");
            dataAdapterProducer.Fill(dataSet, "Producer");

            DataRelation dataRelation = new DataRelation("FK_Producer", dataSet.Tables["Producer"].Columns["Id"],
                dataSet.Tables["Movie"].Columns["ProducerId"]);
            dataSet.Relations.Add(dataRelation);

            bindingSourceMovie= new BindingSource();
            bindingSourceProducer= new BindingSource();

            bindingSourceProducer.DataSource = dataSet;
            bindingSourceProducer.DataMember = "Producer";

            bindingSourceMovie.DataSource = bindingSourceProducer;
            bindingSourceMovie.DataMember = "FK_Producer";

            GridProducer.DataSource = bindingSourceProducer;
            GridMovie.DataSource = bindingSourceMovie;
        }
    }
}
