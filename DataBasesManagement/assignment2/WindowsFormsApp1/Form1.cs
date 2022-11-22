using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
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
        DataSet dataSet = new DataSet();
        string connectionString = "Data Source=Desktop-p9hv7vf;Initial Catalog=Planner2;Integrated Security=True";

        SqlDataAdapter parentAdapter = new SqlDataAdapter();
        SqlDataAdapter childAdapter = new SqlDataAdapter();

        BindingSource bindingSourceParent = new BindingSource();
        BindingSource bindingSourceChild = new BindingSource();

        String parentTableName, childTableName, pkColumnString, fkColumnString, fk;


        //UPDATE
        private void button3_Click(object sender, EventArgs e)
        {
            try
            {
                int childIdFromTable = Int32.Parse(dataGridViewChild.SelectedRows[0].Cells[0].Value.ToString());

                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();

                    SqlCommand updateCommand = new SqlCommand(updateCommandString, connection);

                    for (int i = 0; i < panel1.Controls.Count; i++)
                    {
                        if (panel1.Controls[i] is TextBox)
                        {
                            TextBox textBox = (TextBox)panel1.Controls[i];

                            updateCommand.Parameters.AddWithValue("@" + textBox.Name, textBox.Text);
                        }
                    }

                    updateCommand.Parameters.AddWithValue("@" + childId, childIdFromTable);

                    updateCommand.ExecuteNonQuery();
                    RefreshTables();
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }


        //DELETE
        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                int deleteId = Int32.Parse(dataGridViewChild.SelectedRows[0].Cells[0].Value.ToString());

                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();

                    SqlCommand deleteCommand = new SqlCommand(deleteCommandString, connection);

                    deleteCommand.Parameters.AddWithValue("@" + childId, deleteId);

                    deleteCommand.ExecuteNonQuery();
                    RefreshTables();
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        String insertCommandString, updateCommandString, childId, deleteCommandString;

        private void Form1_Load_1(object sender, EventArgs e)
        {
            try
            {
                InitializeSettings();
                RefreshTables();
                InitializeGUI();

                dataGridViewParent.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
                dataGridViewChild.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }

        public Form1()
        {
            InitializeComponent();
        }


        //ADD
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                int parentId = Int32.Parse(dataGridViewParent.SelectedRows[0].Cells[0].Value.ToString());
                Console.WriteLine(parentId);

                using (SqlConnection connection = new SqlConnection(connectionString))
                {
                    connection.Open();

                    SqlCommand insertCommand = new SqlCommand(insertCommandString, connection);

                    for (int i = 0; i < panel1.Controls.Count; i++)
                    {
                        if (panel1.Controls[i] is TextBox)
                        {
                            TextBox textBox = (TextBox)panel1.Controls[i];

                            insertCommand.Parameters.AddWithValue("@" + textBox.Name, textBox.Text);
                            Console.WriteLine(textBox.Name);
                        }
                    }

                    insertCommand.Parameters.AddWithValue("@" + fkColumnString, parentId);

                    insertCommand.ExecuteNonQuery();
                    RefreshTables();
                }
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }
        private void InitializeSettings()
        {
            parentTableName = ConfigurationManager.AppSettings["parentTableName"];
            childTableName = ConfigurationManager.AppSettings["childTableName"];
            pkColumnString = ConfigurationManager.AppSettings["pkColumn"];
            fkColumnString = ConfigurationManager.AppSettings["fkColumn"];
            fk = ConfigurationManager.AppSettings["fk"];
            insertCommandString = ConfigurationManager.AppSettings["insertCommand"];
            updateCommandString = ConfigurationManager.AppSettings["updateCommand"];
            childId = ConfigurationManager.AppSettings["childId"];
            deleteCommandString = ConfigurationManager.AppSettings["deleteCommand"];
        }

        private void InitializeGUI()
        {
            int index = 0;
            for (int i = 1; i < dataSet.Tables[childTableName].Columns.Count - 1; i++)
            {
                DataColumn column = dataSet.Tables[childTableName].Columns[i];

                if (column.ColumnName != fkColumnString)
                {
                    TextBox textBox = new TextBox();
                    Label label = new Label();

                    label.Text = column.ColumnName;
                    textBox.Name = column.ColumnName;

                    textBox.Location = new Point(120 * index, 20);
                    label.Location = new Point(120 * index, 0);

                    panel1.Controls.Add(textBox);
                    panel1.Controls.Add(label);

                    index++;
                }
            }
        }

        private void RefreshTables()
        {
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                dataSet.Clear();
                dataSet.Relations.Clear();

                parentAdapter.SelectCommand = new SqlCommand("select * from " + parentTableName, connection);
                childAdapter.SelectCommand = new SqlCommand("select * from " + childTableName, connection);

                parentAdapter.Fill(dataSet, parentTableName);
                childAdapter.Fill(dataSet, childTableName);

                bindingSourceParent.DataSource = dataSet.Tables[parentTableName];
                bindingSourceChild.DataSource = dataSet.Tables[childTableName];

                dataGridViewParent.DataSource = bindingSourceParent;

                DataColumn pkColumn = dataSet.Tables[parentTableName].Columns[pkColumnString];
                DataColumn fkColumn = dataSet.Tables[childTableName].Columns[fkColumnString];
                DataRelation relation = new DataRelation(fk, pkColumn, fkColumn);

                dataSet.Relations.Add(relation);
                bindingSourceChild.DataSource = bindingSourceParent;
                bindingSourceChild.DataMember = fk;

                dataGridViewChild.DataSource = bindingSourceChild;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            try
            {
                InitializeSettings();
                RefreshTables();
                InitializeGUI();

                dataGridViewParent.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
                dataGridViewChild.SelectionMode = DataGridViewSelectionMode.FullRowSelect;
            }
            catch (Exception exception)
            {
                MessageBox.Show(exception.Message);
            }
        }
    }
}
