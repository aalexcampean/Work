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
        SqlDataAdapter dataAdapterContacts, dataAdapterEmailAddr;
        DataSet dataSet;
        SqlCommandBuilder commandBuilder;
        BindingSource bindingSourceContacts, bindingSourceEmailAddr;
        public Form1()
        {
            InitializeComponent();
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'planner2DataSet1.EmailAddress' table. You can move, or remove it, as needed.
            //this.emailAdressTableAdapter.Fill(this.planner2DataSet1.EmailAddress);
            // TODO: This line of code loads data into the 'planner2DataSet.Contact' table. You can move, or remove it, as needed.
            //this.contactTableAdapter.Fill(this.planner2DataSet.Contact);

        }


        private void button2_Click(object sender, EventArgs e)
        {
            dataAdapterEmailAddr.Update(dataSet, "EmailAddress");
        }

        private void dataGridView2_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            connection = new SqlConnection(@"Data Source=Desktop-p9hv7vf;Initial Catalog=Planner2;Integrated Security=True");
            dataSet = new DataSet();
            dataAdapterEmailAddr = new SqlDataAdapter("SELECT * FROM EmailAddress", connection);
            dataAdapterContacts = new SqlDataAdapter("SELECT * FROM Contact", connection);


            commandBuilder = new SqlCommandBuilder(dataAdapterEmailAddr);

            dataAdapterEmailAddr.Fill(dataSet, "EmailAddress");
            dataAdapterContacts.Fill(dataSet, "Contact");

            DataRelation dataRelation = new DataRelation("FK_EmailAddress", dataSet.Tables["Contact"].Columns["Id"],
                dataSet.Tables["EmailAddress"].Columns["ContactId"]);
            dataSet.Relations.Add(dataRelation);

            bindingSourceEmailAddr = new BindingSource();
            bindingSourceContacts = new BindingSource();

            bindingSourceContacts.DataSource = dataSet;
            bindingSourceContacts.DataMember = "Contact";

            bindingSourceEmailAddr.DataSource = bindingSourceContacts;
            bindingSourceEmailAddr.DataMember = "FK_EmailAddress";

            GridContact.DataSource = bindingSourceContacts;
            GridEmailAddr.DataSource = bindingSourceEmailAddr;

        }
    }
}
