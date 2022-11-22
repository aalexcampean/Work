namespace WindowsFormsApp1
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.planner2DataSet = new WindowsFormsApp1.Planner2DataSet();
            this.contactBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.contactTableAdapter = new WindowsFormsApp1.Planner2DataSetTableAdapters.ContactTableAdapter();
            this.GridEmailAddr = new System.Windows.Forms.DataGridView();
            this.planner2DataSet1 = new WindowsFormsApp1.Planner2DataSet1();
            this.emailAdressBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.emailAdressTableAdapter = new WindowsFormsApp1.Planner2DataSet1TableAdapters.EmailAdressTableAdapter();
            this.idDataGridViewTextBoxColumn1 = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.emailAdrDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.contactIdDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.GridContact = new System.Windows.Forms.DataGridView();
            this.idDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.lastNameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.firstNameDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.phoneNumberDataGridViewTextBoxColumn = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.planner2DataSet)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.contactBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GridEmailAddr)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.planner2DataSet1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.emailAdressBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.GridContact)).BeginInit();
            this.SuspendLayout();
            // 
            // planner2DataSet
            // 
            this.planner2DataSet.DataSetName = "Planner2DataSet";
            this.planner2DataSet.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // contactBindingSource
            // 
            this.contactBindingSource.DataMember = "Contact";
            this.contactBindingSource.DataSource = this.planner2DataSet;
            // 
            // contactTableAdapter
            // 
            this.contactTableAdapter.ClearBeforeFill = true;
            // 
            // GridEmailAddr
            // 
            this.GridEmailAddr.AutoGenerateColumns = false;
            this.GridEmailAddr.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.GridEmailAddr.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.idDataGridViewTextBoxColumn1,
            this.emailAdrDataGridViewTextBoxColumn,
            this.contactIdDataGridViewTextBoxColumn});
            this.GridEmailAddr.DataSource = this.emailAdressBindingSource;
            this.GridEmailAddr.Location = new System.Drawing.Point(12, 238);
            this.GridEmailAddr.Name = "GridEmailAddr";
            this.GridEmailAddr.RowHeadersWidth = 51;
            this.GridEmailAddr.RowTemplate.Height = 24;
            this.GridEmailAddr.Size = new System.Drawing.Size(431, 150);
            this.GridEmailAddr.TabIndex = 1;
            // 
            // planner2DataSet1
            // 
            this.planner2DataSet1.DataSetName = "Planner2DataSet1";
            this.planner2DataSet1.SchemaSerializationMode = System.Data.SchemaSerializationMode.IncludeSchema;
            // 
            // emailAdressBindingSource
            // 
            this.emailAdressBindingSource.DataMember = "EmailAdress";
            this.emailAdressBindingSource.DataSource = this.planner2DataSet1;
            // 
            // emailAdressTableAdapter
            // 
            this.emailAdressTableAdapter.ClearBeforeFill = true;
            // 
            // idDataGridViewTextBoxColumn1
            // 
            this.idDataGridViewTextBoxColumn1.DataPropertyName = "Id";
            this.idDataGridViewTextBoxColumn1.HeaderText = "Id";
            this.idDataGridViewTextBoxColumn1.MinimumWidth = 6;
            this.idDataGridViewTextBoxColumn1.Name = "idDataGridViewTextBoxColumn1";
            this.idDataGridViewTextBoxColumn1.ReadOnly = true;
            this.idDataGridViewTextBoxColumn1.Width = 125;
            // 
            // emailAdrDataGridViewTextBoxColumn
            // 
            this.emailAdrDataGridViewTextBoxColumn.DataPropertyName = "EmailAdr";
            this.emailAdrDataGridViewTextBoxColumn.HeaderText = "EmailAdr";
            this.emailAdrDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.emailAdrDataGridViewTextBoxColumn.Name = "emailAdrDataGridViewTextBoxColumn";
            this.emailAdrDataGridViewTextBoxColumn.Width = 125;
            // 
            // contactIdDataGridViewTextBoxColumn
            // 
            this.contactIdDataGridViewTextBoxColumn.DataPropertyName = "ContactId";
            this.contactIdDataGridViewTextBoxColumn.HeaderText = "ContactId";
            this.contactIdDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.contactIdDataGridViewTextBoxColumn.Name = "contactIdDataGridViewTextBoxColumn";
            this.contactIdDataGridViewTextBoxColumn.Width = 125;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(649, 67);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(112, 64);
            this.button1.TabIndex = 2;
            this.button1.Text = "Connect to DB";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(649, 263);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(112, 61);
            this.button2.TabIndex = 3;
            this.button2.Text = "Update DB";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // GridContact
            // 
            this.GridContact.AutoGenerateColumns = false;
            this.GridContact.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.GridContact.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.idDataGridViewTextBoxColumn,
            this.lastNameDataGridViewTextBoxColumn,
            this.firstNameDataGridViewTextBoxColumn,
            this.phoneNumberDataGridViewTextBoxColumn});
            this.GridContact.DataSource = this.contactBindingSource;
            this.GridContact.Location = new System.Drawing.Point(12, 30);
            this.GridContact.Name = "GridContact";
            this.GridContact.RowHeadersWidth = 51;
            this.GridContact.RowTemplate.Height = 24;
            this.GridContact.Size = new System.Drawing.Size(562, 150);
            this.GridContact.TabIndex = 4;
            // 
            // idDataGridViewTextBoxColumn
            // 
            this.idDataGridViewTextBoxColumn.DataPropertyName = "Id";
            this.idDataGridViewTextBoxColumn.HeaderText = "Id";
            this.idDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.idDataGridViewTextBoxColumn.Name = "idDataGridViewTextBoxColumn";
            this.idDataGridViewTextBoxColumn.ReadOnly = true;
            this.idDataGridViewTextBoxColumn.Width = 125;
            // 
            // lastNameDataGridViewTextBoxColumn
            // 
            this.lastNameDataGridViewTextBoxColumn.DataPropertyName = "LastName";
            this.lastNameDataGridViewTextBoxColumn.HeaderText = "LastName";
            this.lastNameDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.lastNameDataGridViewTextBoxColumn.Name = "lastNameDataGridViewTextBoxColumn";
            this.lastNameDataGridViewTextBoxColumn.Width = 125;
            // 
            // firstNameDataGridViewTextBoxColumn
            // 
            this.firstNameDataGridViewTextBoxColumn.DataPropertyName = "FirstName";
            this.firstNameDataGridViewTextBoxColumn.HeaderText = "FirstName";
            this.firstNameDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.firstNameDataGridViewTextBoxColumn.Name = "firstNameDataGridViewTextBoxColumn";
            this.firstNameDataGridViewTextBoxColumn.Width = 125;
            // 
            // phoneNumberDataGridViewTextBoxColumn
            // 
            this.phoneNumberDataGridViewTextBoxColumn.DataPropertyName = "PhoneNumber";
            this.phoneNumberDataGridViewTextBoxColumn.HeaderText = "PhoneNumber";
            this.phoneNumberDataGridViewTextBoxColumn.MinimumWidth = 6;
            this.phoneNumberDataGridViewTextBoxColumn.Name = "phoneNumberDataGridViewTextBoxColumn";
            this.phoneNumberDataGridViewTextBoxColumn.Width = 125;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.GridContact);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.GridEmailAddr);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.planner2DataSet)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.contactBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.GridEmailAddr)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.planner2DataSet1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.emailAdressBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.GridContact)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion
        private Planner2DataSet planner2DataSet;
        private System.Windows.Forms.BindingSource contactBindingSource;
        private Planner2DataSetTableAdapters.ContactTableAdapter contactTableAdapter;
        private System.Windows.Forms.DataGridView GridEmailAddr;
        private Planner2DataSet1 planner2DataSet1;
        private System.Windows.Forms.BindingSource emailAdressBindingSource;
        private Planner2DataSet1TableAdapters.EmailAdressTableAdapter emailAdressTableAdapter;
        private System.Windows.Forms.DataGridViewTextBoxColumn idDataGridViewTextBoxColumn1;
        private System.Windows.Forms.DataGridViewTextBoxColumn emailAdrDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn contactIdDataGridViewTextBoxColumn;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.DataGridView GridContact;
        private System.Windows.Forms.DataGridViewTextBoxColumn idDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn lastNameDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn firstNameDataGridViewTextBoxColumn;
        private System.Windows.Forms.DataGridViewTextBoxColumn phoneNumberDataGridViewTextBoxColumn;
    }
}

