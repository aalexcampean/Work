<?php
require '../Model/DocumentDTO.php';

class Repository
{
    private $connection;

    private string $servername;
    private string $username;
    private string $password;
    private string $dbname;
    private int $port;

    /**
     * @param string $servername
     * @param string $username
     * @param string $password
     * @param string $dbname
     */
    public function __construct()
    {
        $this->servername = "127.0.0.1";
        $this->username = "alex";
        $this->password = "1234";
        $this->dbname = "DocumentManager";
        $this->port = 2019;
    }

    // Connect to Database
    public function connect()
    {
        $this->connection = new mysqli($this->servername, $this->username, $this->password, $this->dbname, $this->port);
        if ($this->connection->connect_error) {
            die("Connection failed: " . $this->connection->connect_error);
        }
    }

    // Disconnect from Database
    public function disconnect()
    {
        $this->connection->close();
    }

    // Show all Documents from the database
    public function getAll()
    {
        $this->connect();
        $sqlCommand = "SELECT * FROM Documents";
        $result = $this->connection->query($sqlCommand);

        $this->disconnect();
        return $result;
    }

    // Show Document with given id from the database
    public function getById(int $documentId)
    {
        $this->connect();
        $sqlCommand = "SELECT * FROM Documents WHERE id=" . $documentId;
        $result = $this->connection->query($sqlCommand);

        $this->disconnect();
        return $result;
    }

    // Show all Documents of a given type from the database
    public function getByType(string $documentType)
    {
        $this->connect();
        $sqlCommand = "SELECT * FROM Documents WHERE type='" . $documentType . "'";
        $result = $this->connection->query($sqlCommand);

        $this->disconnect();
        return $result;
    }

    // Show all Documents of a given format from the database
    public function getByFormat(string $documentFormat)
    {
        $this->connect();
        $sqlCommand = "SELECT * FROM Documents WHERE format='" . $documentFormat . "'";
        $result = $this->connection->query($sqlCommand);

        $this->disconnect();
        return $result;
    }

    // Add a new Document to the Database
    public function add(DocumentDTO $document)
    {
        $this->connect();
        $sqlCommand = "INSERT INTO Documents (title, author, noPages, type, format) 
                                    VALUES ('" . $document->getTitle() . "', '" . $document->getAuthor() . "', "
            . $document->getNumberOfPages() . ", '" . $document->getType() . "', '" . $document->getFormat() . "');";

        $result = $this->connection->query($sqlCommand);
        if ($result === TRUE) {
            echo "Document added successfully";
        } else {
            echo "Error adding document: " . $this->connection->error;
        }

        $this->disconnect();
        return $result;
    }

    // Update an existing Document from the Database
    public function update(DocumentDTO $document)
    {
        $this->connect();

        $sqlCommand = "UPDATE Documents SET title='" . $document->getTitle()
            . "', author='" . $document->getAuthor()
            . "', noPages=" . $document->getNumberOfPages()
            . ", type='" . $document->getType()
            . "', format='" . $document->getFormat()
            . "' WHERE id=" . $document->getId() . ";";

        $result = $this->connection->query($sqlCommand);
        if ($result === TRUE) {
            echo "Document updated successfully";
        } else {
            echo "Error updating document: " . $this->connection->error;
        }

        $this->disconnect();
        return $result;
    }

    // Deleting an existing Document from the Database
    public function delete(int $documentId)
    {
        $this->connect();

        $sqlCommand = "DELETE FROM Documents WHERE id=" . $documentId;

        $result = $this->connection->query($sqlCommand);
        if ($result === TRUE) {
            echo "Document deleted successfully";
        } else {
            echo "Error deleted document: " . $this->connection->error;
        }

        $this->disconnect();
        return $result;
    }
}