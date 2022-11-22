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
        SqlDataAdapter dataAdapterLocation, dataAdapterCar, dataAdapterClient;
        DataSet dataSet;
        SqlCommandBuilder commandBuilder;
        BindingSource bindingSourceLocation, bindingSourceCar, bindingSourceClient;
        public Form1()
        {
            InitializeComponent();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            dataAdapterCar.Update(dataSet, "Car");

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'carServiceDataSet2.Client' table. You can move, or remove it, as needed.
            this.clientTableAdapter.Fill(this.carServiceDataSet2.Client);
            // TODO: This line of code loads data into the 'carServiceDataSet1.Car' table. You can move, or remove it, as needed.
            this.carTableAdapter.Fill(this.carServiceDataSet1.Car);
            // TODO: This line of code loads data into the 'carServiceDataSet.Location' table. You can move, or remove it, as needed.
            this.locationTableAdapter.Fill(this.carServiceDataSet.Location);

        }

        private void button1_Click(object sender, EventArgs e)
        {
            connection = new SqlConnection(@"Data Source=Desktop-p9hv7vf;Initial Catalog=CarService;Integrated Security=True");
            dataSet = new DataSet();
            dataAdapterCar = new SqlDataAdapter("SELECT * FROM Car", connection);
            dataAdapterLocation = new SqlDataAdapter("SELECT * FROM Location", connection);
            dataAdapterClient = new SqlDataAdapter("SELECT * FROM Client", connection);

            commandBuilder = new SqlCommandBuilder(dataAdapterCar);

            dataAdapterCar.Fill(dataSet, "Car");
            dataAdapterLocation.Fill(dataSet, "Location");
            dataAdapterClient.Fill(dataSet, "Client");

            DataRelation dataRelation = new DataRelation("FK_CarService", dataSet.Tables["Location"].Columns["Id"],
                dataSet.Tables["Car"].Columns["LocationId"]);
            DataRelation dataRelation2 = new DataRelation("FK_CarService", dataSet.Tables["Location"].Columns["Id"],
                dataSet.Tables["Car"].Columns["LocationId"]);
            dataSet.Relations.Add(dataRelation);

            bindingSourceLocation = new BindingSource();
            bindingSourceCar = new BindingSource();

            bindingSourceLocation.DataSource = dataSet;
            bindingSourceLocation.DataMember = "Location";

            bindingSourceCar.DataSource = bindingSourceLocation;
            bindingSourceCar.DataMember = "FK_CarService";

            GridLocation.DataSource = bindingSourceLocation;
            GridCar.DataSource = bindingSourceCar;
        }
    }
}
